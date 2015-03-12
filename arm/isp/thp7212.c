#include <linux/thp7212.h>
#include <linux/ioctl.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/sysfs.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/i2c.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/kobject.h>
#include <linux/firmware.h>
#include <linux/dma-mapping.h>
#include <linux/spi/spi.h>
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>
#include <mach/mt_spi.h>
#include <mach/mt_clkmgr.h>
#include <mach/camera_isp.h>
#include <inc/kd_imgsensor_define.h>

enum {
	SINGLE_AF = 0x00,
	CONTINOUS_AF=0x01,
	SIG_CON_AF = 0x02,
};
static int reg_log = 0;
static int af_debug = 0;
static int Af_mode = 0;
static int zoom = 0;
static int first_focus = 1; // for fisrt focus
static dev_t thp7212_dev = MKDEV(250,0);
static struct cdev * thp7212_chardrv = NULL;
static struct class *thp7212_class = NULL;
struct thp7212_private_data thp7212_data;
static const struct i2c_device_id thp7212_i2c_id[] = {{THP7212_I2C_DEV, 0},{}};
static struct i2c_board_info thp7212_i2c_info = {I2C_BOARD_INFO(THP7212_I2C_DEV,THP7212_I2C_ADDR)};
//spi
static struct spi_board_info thp7212_spi_info = {
	.modalias = THP7212_SPI_DEV,
	.bus_num  = 0,
	.chip_select = 0,
};

static void thp7212_spi_complete(void *arg)
{
	complete(arg);
}

static int thp7212_spi_transfer(char *buf,size_t sz) 
{
	struct spi_transfer transfer;
	struct spi_message msg;
	int offset = 0,szt=SPI_DATA_SIZE;
	DECLARE_COMPLETION_ONSTACK(done);

	transfer.rx_buf = NULL;
	spi_message_init(&msg);
	msg.complete = thp7212_spi_complete;
	msg.context = &done;
	spi_message_add_tail(&transfer,&msg);
	while(offset < sz){
		INIT_COMPLETION(done);
		if(sz - offset < SPI_DATA_SIZE)
			szt = sz - offset;
		transfer.len = szt;
		transfer.tx_buf = buf+offset;

		offset += szt;

		spi_async(thp7212_data.spi_device, &msg);
		wait_for_completion(&done);
	}   
	return 0;
}

// i2c write and read
static int thp7212_i2c_write(int addr,char data)
{
	if(reg_log)
		dev_err(thp7212_data.dev,"I2c write:0x%04X=0x%02X\n",addr,data);
	return iWriteReg(addr,data,1,THP7212_I2C_ADDR << 1);
}

static int thp7212_i2c_read(int addr)
{
	int err;
	char _buf[2];
	err = iReadReg(addr , _buf , THP7212_I2C_ADDR << 1);
	if(err < 0){
		dev_err(thp7212_data.dev,"i2c recv error!\n");
		return -EFAULT;
	}
	if(reg_log)
		dev_warn(thp7212_data.dev,"I2c read:ADDR=0x%04X,value=0x%02X\n",addr,_buf[0]); 
	return _buf[0]&0xFF;
}

void register_dump(void)
{
	thp7212_i2c_write(0xF008,0x01);
	thp7212_i2c_read(0xF008);
	int i;
	for(i=0xF000;i<0xF030;i++)
	{
		thp7212_i2c_read(i);
	}
}

// firmware 
static int fw_request(int index, char *name, int *size)
{
	const struct firmware *fw;
	char *data;
	if(request_firmware(&fw,name,thp7212_data.dev)){
		return -1;
	}
	*size = fw->size;
	if(index) {
		thp7212_data.rear_fw = kmalloc(fw->size,GFP_KERNEL);
		if(thp7212_data.rear_fw == NULL){
			release_firmware(fw);
			dev_err(thp7212_data.dev,"Don't get enough area\n");
			return -1;
		}
		memcpy(thp7212_data.rear_fw,fw->data,fw->size);
	}
	else {
		thp7212_data.sub_fw = kmalloc(fw->size,GFP_KERNEL);
		if(thp7212_data.sub_fw == NULL){
			release_firmware(fw);
			dev_err(thp7212_data.dev,"Don't get enough area\n");
			return -1;
		}
		memcpy(thp7212_data.sub_fw,fw->data,fw->size);
	}

	release_firmware(fw);
	return 0;
}

static void fw_dwork(struct work_struct *p)
{
	thp7212_data.fw_readly = 1;
	if(fw_request(1, THP7212_REAR_FW, &thp7212_data.rear_fw_size)){
		dev_err(thp7212_data.dev,"Don't get rear firmware:%s\n",THP7212_REAR_FW);
		thp7212_data.fw_readly = 0;
	}

	if(fw_request(0, THP7212_SUB_FW, &thp7212_data.sub_fw_size)){
		dev_err(thp7212_data.dev,"Don't get sub firmware:%s\n",THP7212_SUB_FW);
		thp7212_data.fw_readly = 0;
	}

	dev_warn(thp7212_data.dev,"Rear:fw size:%d\n",thp7212_data.rear_fw_size);
	dev_warn(thp7212_data.dev,"Sub:fw size:%d\n",thp7212_data.sub_fw_size);
}

int thp7212_get_module_id(void)
{
	return thp7212_i2c_read(THP7212_MODULE_ID);
}

int thp7212_set_filp_mirror(char value)
{
	return thp7212_i2c_write(THP7212_MIRROR_FLIP,value&0x03);
}

int thp7212_set_preview_size(int index)
{
	if(index){
		thp7212_i2c_write(THP7212_PREVIEW_SIZE,0x0B);//1920x1280
	}
	thp7212_i2c_write(THP7212_PREVIEW_SIZE,0x10);//2048x1536
	thp7212_i2c_write(THP7212_OUTCONTROL,0x00); //disable out from isp
	return thp7212_i2c_write(THP7212_CAPTURE_MODE,0x01);
}

int thp7212_set_still_size(int index)
{
	if(index) {
		return thp7212_i2c_write(THP7212_STLIMG_SIZE,0x13);//4160x2336(9.7M)
	}
	return thp7212_i2c_write(THP7212_STLIMG_SIZE,0x14);//4160x3120(13M)
}

bool isp_lock = false;
int thp7212_start_preview(int size)
{
	int count = 0;
	thp7212_data.video_mode = false;
	while(isp_lock)udelay(5);
	thp7212_set_preview_size(0);
	thp7212_i2c_write(THP7212_BURST_NUM,0);
	thp7212_i2c_write(THP7212_AE_AREA,0x10);
	while(thp7212_i2c_read(THP7212_CAPTURE_OK) != 0x01){
		mdelay(3);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"preview:%02x read error\n",THP7212_CAPTURE_OK);
			break;
		}
	}
	count = 0;
	thp7212_i2c_write(THP7212_HOSTLED_STATUS,0x00);
	while(thp7212_i2c_read(THP7212_MIPI_STATE) != 0x81){
		mdelay(3);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"preview:%02x read error\n",THP7212_MIPI_STATE);
			break;
		}
	}
	thp7212_i2c_write(THP7212_OUTCONTROL,0x01); //enable out from isp
	thp7212_data.torch_lamp = false;
	return 0;
}
static int reg[32]= {
	0xF000,0xF005,0xF00D,0xF010,0xF018,0xF019,0xF022,0xF039,0xF061,
	0xF025,0xF042,0xF065,0xF046,0xF047,0xF048,0xF049,0xF04A,0xF04B,
	0xF04C,0xF04D,0xF066,0xF067,0xF069,0xF069,0xF06A,0xF06B,0xF06C,
	0xF06D,0xF026,0xF027,0xF028,0xF029};

int thp7212_isp_info(char *info)
{
	int i,size=0;
	char value;
	if(thp7212_data.multi_shot_mode)
		return snprintf(info,1,"\0");
	snprintf(info,2048,"%s","ISP register list:\n");
	isp_lock = true;
	for (i=0;i<32;i++) {
		value = thp7212_i2c_read(reg[i]);
		snprintf(info,2048,"%s%04x=%02x\n",info,reg[i],value&0xFF);
	}

	for(i=0xFC80;i<0xFD00;i++) {
		value = thp7212_i2c_read(i);
		snprintf(info,2048,"%s%04x=%02x\n",info,i,value&0xFF);
	};

	isp_lock = false;
	return size;
}

int thp7212_stop_preview(int size)
{
	thp7212_i2c_write(THP7212_OUTCONTROL,0x00);
	while(thp7212_i2c_read(THP7212_MIPI_STATE) != 0x81)udelay(3);
	return 0;
}

void thp7212_set_multi_shot(unsigned int uPara)
{
	thp7212_data.multi_shot_mode = uPara;
	if(!uPara)
		thp7212_i2c_write(THP7212_BURST_NUM,0x00);
}

int thp7212_capture(int index)
{
	int count = 0;
	if((index == 1) && thp7212_data.flash_on) {
		thp7212_i2c_write(THP7212_STROBE_LIGHT,0x01);
		while(thp7212_i2c_read(THP7212_STROBE_LIGHT) != 0x00){
			mdelay(10);
			if(count++ == 150){
				dev_err(thp7212_data.dev,"flash mode error");
				break;
			}
		}
	}
	else if ((index == 0) && ((thp7212_data.flash_mode == FLASHLIGHT_FORCE_ON) || 
				((thp7212_data.flash_mode == FLASHLIGHT_AUTO) && thp7212_data.sub_flash_status)))
	{
		thp7212_i2c_write(THP7212_HOSTLED_STATUS,0x02);
		count = 0;
		while(thp7212_i2c_read(THP7212_STROBE_HOST) != 0x00){
			mdelay(10);
			if(count++ == 150){
				dev_err(thp7212_data.dev,"host strobe error");
				break;
			}
		}
	}

	if(thp7212_data.multi_shot_mode)
		thp7212_i2c_write(THP7212_BURST_NUM,0xFF);
	else
		thp7212_i2c_write(THP7212_BURST_NUM,0x02);
	count = 0;
	thp7212_i2c_write(THP7212_CAPTURE_MODE,0x03);
	while(thp7212_i2c_read(THP7212_CAPTURE_MODE)!= 0x03){
		thp7212_i2c_write(THP7212_CAPTURE_MODE,0x03);
		mdelay(3);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"capture:%02x write error\n",THP7212_CAPTURE_MODE);
			break;
		}
	}

	count = 0;
	while(thp7212_i2c_read(THP7212_CAPTURE_OK) != 0x03){
		mdelay(10);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"capture:%02x read error\n",THP7212_CAPTURE_OK);
			break;
		}
	}
	count = 0;
	while(thp7212_i2c_read(THP7212_MIPI_STATE) != 0x83){
		mdelay(10);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"capture:%02x read error\n",THP7212_MIPI_STATE);
			break;
		}
	}
	// host AP is ready
	thp7212_i2c_write(THP7212_OUTCONTROL,0x01);
	return 0;
}

void thp7212_start_video(void)
{
	int count = 0;
	thp7212_data.video_mode = true;
	thp7212_set_preview_size(1);
	thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|0x10);
	thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
	while(thp7212_i2c_read(THP7212_CAPTURE_OK) != 0x01){
		mdelay(3);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"video:%02x read error\n",THP7212_CAPTURE_OK);
			break;
		}
	}

	count = 0;
	while(thp7212_i2c_read(THP7212_MIPI_STATE) != 0x81){
		mdelay(3);
		if(count++ == 50){
			dev_err(thp7212_data.dev,"video:%02x read error\n",THP7212_MIPI_STATE);
			break;
		}
	}
	thp7212_i2c_write(THP7212_OUTCONTROL,0x01); //enable out from isp
}

void thp7212_continuous_shot(void)
{
	thp7212_i2c_write(THP7212_BURST_NUM,99);
	thp7212_i2c_write(THP7212_CAPTURE_MODE,0x03);
	while(thp7212_i2c_read(THP7212_CAPTURE_OK) != 0x03)udelay(5);
	while(thp7212_i2c_read(THP7212_MIPI_STATE) != 0x83)udelay(5);
	// host AP is ready
	thp7212_i2c_write(THP7212_OUTCONTROL,0x01);
}

int thp7212_get_af_status(void)
{
	switch(thp7212_data.af_status){
		case SENSOR_AF_FOCUSING:
			if((thp7212_i2c_read(THP7212_AF_STATUS)&0x80) == 0)
				thp7212_data.af_status = SENSOR_AF_FOCUSED;
			break;
		case SENSOR_AF_FOCUSED:
			switch(thp7212_data.af_mode) {
				case SINGLE_AF:
					thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|0x33);
					thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
					thp7212_data.af_mode = SIG_CON_AF;
					break;
				case SIG_CON_AF:
					if((thp7212_i2c_read(THP7212_AF_STATUS)&0x20) == 0x20){
						thp7212_data.af_mode = CONTINOUS_AF;
						thp7212_data.af_status = SENSOR_AF_SCENE_DETECTING;
						if(Af_mode)
							thp7212_i2c_write(THP7212_FACE_DETECTION,0x01);
						thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|3<<4|Af_mode);
						thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
					}
					break;
				case CONTINOUS_AF:
					if((thp7212_i2c_read(THP7212_AF_STATUS)&0x20) == 0x20)
						thp7212_data.af_status = SENSOR_AF_SCENE_DETECTING;
					break;

			};
			break;
		case SENSOR_AF_SCENE_DETECTING:
			if((thp7212_i2c_read(THP7212_AF_STATUS)&0x20) == 0)
				thp7212_data.af_status = SENSOR_AF_FOCUSED;
			break;
	};
	return thp7212_data.af_status;
}

// one shot af
int thp7212_oneshot_af(void)
{
	thp7212_data.af_status = SENSOR_AF_FOCUSING;
	thp7212_data.af_mode = SINGLE_AF;
	thp7212_i2c_write(THP7212_AE_AREA,0x10);
	thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|0x03);
	thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
	return 0;
}

int thp7212_cancel_af(void)
{
	if(thp7212_data.video_mode)
		return 0;
	thp7212_i2c_write(THP7212_AF_CONTROL,0x80);
	thp7212_data.af_status = SENSOR_AF_IDLE;
	return 0;
}

int thp7212_set_af_window(unsigned int zone, unsigned int width, unsigned int height)
{
	unsigned int *value = (unsigned int*)zone;
	unsigned int l,r,b,t,w,h;
	char x0u,x0l,y0u,y0l,x1u,x1l,y1u,y1l;
	if (thp7212_data.af_status == SIG_CON_AF)
		return 0;
	l = *value++;
	t = *value++;
	r = *value++;
	b = *value++;
	w = *value++;
	h = *value++;
	l = l*width/w;
	t = t*height/h;
	r = r*width/w;
	b = b*height/h;
	x0u = (l>>8) & 0xFF;
	x0l = l&0xFF;
	y0u = (t>>8) & 0xFF;
	y0l = t&0xFF;
	x1u = (r>>8) & 0xFF;
	x1l = r&0xFF;
	y1u = (b>>8) & 0xFF;
	y1l = b&0xFF;

	dev_err(thp7212_data.dev,"l=%d,t=%d,r=%d,b=%d\n",x0u<<8|x0l,y0u<<8|y0l,x1u<<8|x1l,y1u<<8|y1l);
	thp7212_i2c_write(THP7212_AF_H_START_H,x0u);
	thp7212_i2c_write(THP7212_AF_H_START_L,x0l);
	thp7212_i2c_write(THP7212_AF_V_START_H,y0u);
	thp7212_i2c_write(THP7212_AF_V_START_L,y0l);
	thp7212_i2c_write(THP7212_AF_H_STOP_H,x1u);
	thp7212_i2c_write(THP7212_AF_H_STOP_L,x1l);
	thp7212_i2c_write(THP7212_AF_V_STOP_H,y1u);
	thp7212_i2c_write(THP7212_AF_V_STOP_L,y1l);
	return 0;
}

int thp7212_continuous_focus(void)
{
	int light_status;
	if(first_focus)
	{
		light_status = thp7212_i2c_read(THP7212_STROBE_MODE);
		thp7212_i2c_write(THP7212_STROBE_MODE,0);
		thp7212_data.af_status = SENSOR_AF_FOCUSING;
		thp7212_data.af_mode = SINGLE_AF;
		thp7212_i2c_write(THP7212_AE_AREA,0x10);
		thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|3);
		thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
		thp7212_i2c_write(THP7212_STROBE_MODE,light_status);
	}
	else{
		if (thp7212_data.af_status == SIG_CON_AF)
			return 0;

		thp7212_data.af_status = SENSOR_AF_SCENE_DETECTING;
		thp7212_data.af_mode = CONTINOUS_AF;
		thp7212_i2c_write(THP7212_AE_AREA,0x00);
		if(Af_mode)
			thp7212_i2c_write(THP7212_FACE_DETECTION,0x01);
		thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|3<<4|Af_mode);
		thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
	}
	first_focus = 0;
	return 0;
}

static int zoom_table[11]={
	100,114,132,151,174,200,229,263,303,348,400
};
void thp7212_set_zoom(unsigned int zoom_factor)
{
	int i;
	if(zoom == zoom_factor)
		return;
	for(i=0;i<11;i++)
		if(zoom_factor == zoom_table[i]){
			thp7212_i2c_write(THP7212_ZOOM_FACTOR,i+1);
			zoom = zoom_factor;
			break;
		}
	dev_err(thp7212_data.dev,"ZOOM:%d.factor:%d\n",zoom_factor,i+1);
}

void thp7212_face_detection(int index)
{
	if(index==1){
		Af_mode = 2;
		if(thp7212_data.af_status == SENSOR_AF_SCENE_DETECTING){
			thp7212_i2c_write(THP7212_AF_SETTING,af_debug<<7|3<<4|Af_mode);
			thp7212_i2c_write(THP7212_AF_CONTROL,0x01);
		}
	}
	else {
		Af_mode = 0;
	}
	thp7212_i2c_write(THP7212_FACE_DETECTION,!!Af_mode);
}
void thp7212_set_rotation(int index)
{
	char cmd;
	switch(index) {
		case 0:
			cmd = 0x2;
			break;
		case 90:
			cmd = 0x3;
			break;
		case 180:
			cmd = 0x0;
			break;
		case 270:
			cmd = 0x1;
			break;
		default:
			cmd = 0x4;
			break;
	}
	thp7212_i2c_write(THP7212_DIR_OF_PHONE,cmd);
}

void thp7212_set_image_size(int index)
{
	char cmd;
	if(index<15) cmd = 0x00;
	else cmd = 0x01;
	thp7212_i2c_write(THP7212_IMAGE_SIZE,cmd);
}
int thp7212_set_ae_window(unsigned int *value)
{
	return 0;
}

void thp7212_get_delay_frame(unsigned int *d)
{
	sensor_delay_info_struct *psdis = (sensor_delay_info_struct*)d;
	psdis->af_switch_delay_frame = 20; 
}

void thp7212_set_ae_iso(unsigned int value)
{
	char cmd;
	switch(value)
	{
		case AE_ISO_AUTO:
			cmd = 0x00;
			break;
		case AE_ISO_100: 
			cmd = 0x01;
			break;
		case AE_ISO_200: 
			cmd = 0x02;
			break;
		case AE_ISO_400: 
			cmd = 0x03;
			break;
		case AE_ISO_800: 
			cmd = 0x04;
			break;
		case AE_ISO_1600:
			cmd = 0x05;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_STILL_CAP_MODE,cmd);
}

void thp7212_set_scene_mode(unsigned int value)
{
	char cmd;
	switch(value)
	{
		case SCENE_MODE_NORMAL:                          
			cmd = 0x00;
			break;
		case SCENE_MODE_PORTRAIT:                        
			cmd = 0x01;
			break;
		case SCENE_MODE_LANDSCAPE:                       
			cmd = 0x04;
			break;
		case SCENE_MODE_NIGHTSCENE:                      
			cmd = 0x05;
			break;
		case SCENE_MODE_NIGHTPORTRAIT:                   
			cmd = 0x0A;
			break;
		case SCENE_MODE_THEATRE:                         
			cmd = 0x0B;
			break;
		case SCENE_MODE_BEACH:                           
			cmd = 0x0c;
			break;
		case SCENE_MODE_SNOW:                            
			cmd = 0x0D;
			break;
		case SCENE_MODE_SUNSET:                          
			cmd = 0x08;
			break;
		case SCENE_MODE_STEADYPHOTO:                     
			cmd = 0x0E;
			break;
		case SCENE_MODE_FIREWORKS:                       
			cmd = 0x0F;
			break;
		case SCENE_MODE_SPORTS:                          
			cmd = 0x03;
			break;
		case SCENE_MODE_PARTY:                           
			cmd =0x09;
			break;
		case SCENE_MODE_CANDLELIGHT:                     
			cmd = 0x10;
			break;
		case SCENE_MODE_BRACKET_AE:                      
			cmd = 0x06;
			break;
		case SCENE_MODE_OFF:
		default:
			cmd = 0xFF;
			break;

	};
	thp7212_i2c_write(THP7212_SCENE_MODE,cmd);
}

void thp7212_set_ae_metering(unsigned int uPara)
{
	char cmd;
	switch (uPara) {
		case AE_METERING_MODE_CENTER_WEIGHT:
			cmd = 0x00;
			break;
		case AE_METERING_MODE_SOPT:
			cmd = 0x10;
			break;
		case AE_METERING_MODE_AVERAGE:
			cmd = 0x20;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_AE_AREA,cmd);
}

void thp7212_flash_init(void)
{
	thp7212_data.flash_on = true;
}

void thp7212_set_flashlight_mode(unsigned int uPara)
{
	char cmd[2];
	switch (uPara)
	{
		case FLASHLIGHT_FORCE_ON:
			cmd[0] = 0x02;
			cmd[1] = 0x00;
			thp7212_data.flash_on = true;
			break;
		case FLASHLIGHT_FORCE_OFF:
			cmd[0] = 0x00;
			cmd[1] = 0x00;
			thp7212_data.flash_on = false;
			break;
		case FLASHLIGHT_TORCH:
			cmd[0] = 0x00;
			cmd[1] = 0x03;
			thp7212_data.flash_on = false;
			if(thp7212_data.torch_lamp){
				cmd[1] = 0x04;
			}
			break;
		case FLASHLIGHT_AUTO:
		default:
			cmd[0] = 0x01;
			cmd[1] = 0x00;
			thp7212_data.flash_on = true;
			break;
	}
	thp7212_i2c_write(THP7212_STROBE_MODE,cmd[0]);
	thp7212_i2c_write(THP7212_TORCH_MODE,cmd[1]);
}

void thp7212_get_flashlight_mode(unsigned int uPara)
{
	thp7212_data.flash_mode = uPara;
}

void thp7212_set_ev_param(unsigned int value)
{
	char cmd;
	switch(value){
		case AE_EV_COMP_03:
		case AE_EV_COMP_05:
		case AE_EV_COMP_07:
		case AE_EV_COMP_10:
			cmd = 0x08;
			break;
		case AE_EV_COMP_13:
		case AE_EV_COMP_15:
		case AE_EV_COMP_17:
		case AE_EV_COMP_20:
			cmd = 0x0A;
			break;
		case AE_EV_COMP_23:
		case AE_EV_COMP_25:
		case AE_EV_COMP_27:
		case AE_EV_COMP_30:
			cmd = 0x0C;
			break;
		case AE_EV_COMP_n03:
		case AE_EV_COMP_n05:
		case AE_EV_COMP_n07:
		case AE_EV_COMP_n10:
			cmd = 0x04;
			break;
		case AE_EV_COMP_n13:
		case AE_EV_COMP_n15:
		case AE_EV_COMP_n17:
		case AE_EV_COMP_n20:
			cmd = 0x02;
			break;
		case AE_EV_COMP_n23:
		case AE_EV_COMP_n25:
		case AE_EV_COMP_n27:
		case AE_EV_COMP_n30:
			cmd = 0x00;
			break;
		case AE_EV_COMP_00:
		default:
			cmd = 0x06;
			break;
	};
	thp7212_i2c_write(THP7212_EXP_COMPRESS,cmd);
}

void thp7212_set_awb_mode(unsigned int value)
{
	char cmd;
	switch(value){
		case AWB_MODE_AUTO:
			cmd=0x00;
			break;
		case AWB_MODE_TUNGSTEN:
			cmd=0x01;
			break;
		case AWB_MODE_DAYLIGHT:
			cmd=0x02;
			break;
		case AWB_MODE_CLOUDY_DAYLIGHT:
			cmd=0x03;
			break;
		case AWB_MODE_FLUORESCENT:
			cmd=0x04;
			break;
		case AWB_MODE_WARM_FLUORESCENT:
			cmd=0x05;
			break;
		default:
			cmd=0x00;
			break;
	}
	thp7212_i2c_write(THP7212_AWB_MODE,cmd);
}

void thp7212_set_effect(unsigned int value)
{
	char cmd;
	switch(value) {
		case MEFFECT_OFF:
			cmd=0x00;
			break;
		case MEFFECT_MONO: 
			cmd=0x01;
			break;
		case MEFFECT_SEPIA: 
			cmd=0x02;
			break;
		case MEFFECT_NEGATIVE: 
			cmd=0x03;
			break;
		case MEFFECT_AQUA: 
			cmd=0x04;
			break;
		case MEFFECT_BLACKBOARD: 
			cmd=0x05;
			break;
		case MEFFECT_WHITEBOARD: 
			cmd=0x06;
			break;
		default:
			cmd=0x00;
			break;
	};
	thp7212_i2c_write(THP7212_COLOR_MODE,cmd);
}

void thp7212_set_fliker_mode(unsigned int value)
{
	char cmd;
	switch(value) {
		case AE_FLICKER_MODE_50HZ: 
			cmd = 0x00;
			break;
		case AE_FLICKER_MODE_60HZ:
			cmd = 0x01;
			break;
		case AE_FLICKER_MODE_OFF: 
			cmd = 0x80;
			break;
		case AE_FLICKER_MODE_AUTO: 
		default:
			cmd = 0x10;
			break;
	};
	thp7212_i2c_write(THP7212_FLICKER_MODE,cmd);
}

void thp7212_set_contrast(unsigned int value)
{
	char cmd;
	switch(value) {
		case ISP_CONTRAST_LOW:
			cmd = 0x00;
			break;
		case ISP_CONTRAST_MIDDLE:
			cmd = 0x02;
			break;
		case ISP_CONTRAST_HIGH:
			cmd = 0x04;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_CONTRAST,cmd);
}

void thp7212_set_bright(unsigned int value)
{
	char cmd;
	switch(value) {
		case ISP_BRIGHT_LOW:
			cmd = 0x00;
			break;
		case ISP_BRIGHT_MIDDLE:
			cmd = 0x02;
			break;
		case ISP_BRIGHT_HIGH:
			cmd = 0x04;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_BRIGHTNESS,cmd);
}

void thp7212_set_saturation(unsigned int value)
{
	char cmd;
	switch(value) {
		case ISP_CONTRAST_LOW:
			cmd = 0x00;
			break;
		case ISP_CONTRAST_MIDDLE:
			cmd = 0x02;
			break;
		case ISP_BRIGHT_HIGH:
			cmd = 0x04;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_SATURATION,cmd);
}

void thp7212_set_hue(unsigned int value)
{
	char cmd;
	switch(value) {
		case ISP_HUE_LOW:
			cmd = 0x00;
			break;
		case ISP_HUE_MIDDLE:
			cmd = 0x02;
			break;
		case ISP_HUE_HIGH:
			cmd = 0x04;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_HUE,cmd);
}

void thp7212_set_edge(unsigned int value)
{
	char cmd;
	switch(value) {
		case ISP_EDGE_LOW:
			cmd = 0x00;
			break;
		case ISP_EDGE_MIDDLE:
			cmd = 0x02;
			break;
		case ISP_EDGE_HIGH:
			cmd = 0x04;
			break;
		default:
			return ;
	};
	thp7212_i2c_write(THP7212_SHARPNESS,cmd);
}
int thp7212_get_isospeed(void)
{
	return (thp7212_i2c_read(THP7212_ISO_H)<<8) |thp7212_i2c_read(THP7212_ISO_L);
}

int thp7212_get_extime(void)
{
	return (thp7212_i2c_read(THP7212_SHUTTER_SPH)<<8)|(thp7212_i2c_read(THP7212_SHUTTER_SPL));
}

int thp7212_get_gain(void)
{
	return (thp7212_i2c_read(THP7212_GAIN_H)<<8)|(thp7212_i2c_read(THP7212_GAIN_H));
}

void thp7212_flashtriggercheck(unsigned int *value)
{
	*value = thp7212_i2c_read(THP7212_ESTIMATE) ? 0 : 1; 
	thp7212_data.sub_flash_status = *value;
}

int thp7212_get_flash_status(void)
{
	return thp7212_i2c_read(THP7212_STROBE_STATUS);
}

extern ISP_MCLK1_EN(bool);
int thp7212_power_on_reset(void)
{
	mt_set_gpio_mode(ISP_RESET_GPIO_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(ISP_RESET_GPIO_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(ISP_RESET_GPIO_PIN, GPIO_OUT_ZERO);

	mt_set_gpio_mode(GPIO_VCAM_MCLOCK_PIN,GPIO_MODE_01);
	mt_set_gpio_dir(GPIO_VCAM_MCLOCK_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_VCAM_MCLOCK_PIN, GPIO_OUT_ZERO);
	ISP_MCLK1_EN(false);

	mdelay(10);
	//gpio ldo 1.2v
	mt_set_gpio_mode(ISP_CORE_GPIO_EN_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(ISP_CORE_GPIO_EN_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(ISP_CORE_GPIO_EN_PIN, GPIO_OUT_ONE);
	//isp clk
	ISP_MCLK1_EN(true);
	mdelay(2);

	mt_set_gpio_out(ISP_RESET_GPIO_PIN, GPIO_OUT_ONE);
	//	mdelay(2);
	dev_warn(thp7212_data.dev,"Power On OK\n");
	thp7212_data.power_on = true;
	first_focus= 1;
	return 0;
} 
int thp7212_power_off(void)
{
	mt_set_gpio_out(ISP_RESET_GPIO_PIN, GPIO_OUT_ZERO);
	mt_set_gpio_mode(GPIO_VCAM_MCLOCK_PIN,GPIO_MODE_01);
	mt_set_gpio_dir(GPIO_VCAM_MCLOCK_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_VCAM_MCLOCK_PIN, GPIO_OUT_ZERO);
	mt_set_gpio_out(GPIO_VCAM_MCLOCK_PIN, GPIO_OUT_ZERO);
	ISP_MCLK1_EN(false);
	mt_set_gpio_out(ISP_CORE_GPIO_EN_PIN, GPIO_OUT_ZERO);
	thp7212_data.power_on = false;
	thp7212_data.video_mode = false;
	zoom = 0;
	thp7212_data.af_status = SENSOR_AF_IDLE;
	thp7212_data.torch_lamp =  true;
	return 0;
}

int thp7212_fw_download(int index)
{
	int count = 0;
	if(thp7212_data.fw_readly) {
		dev_warn(thp7212_data.dev,"Enter %s fw download\n",index?"Rear":"Sub");
		mt_set_gpio_mode(SPI_CS_PIN, GPIO_MODE_00);
		mt_set_gpio_dir(SPI_CS_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(SPI_CS_PIN, GPIO_OUT_ONE);
		mdelay(2);
		mt_set_gpio_mode(SPI_DATA_PIN, GPIO_MODE_01);
		mt_set_gpio_out(SPI_CS_PIN, GPIO_OUT_ZERO);
		udelay(100);
		if (index>1){
			dev_err(thp7212_data.dev,"Didn't find the the firmware for %d\n",index);
			return -1;
		}
		if(index)
			thp7212_spi_transfer(thp7212_data.rear_fw,thp7212_data.rear_fw_size);
		else 
			thp7212_spi_transfer(thp7212_data.sub_fw,thp7212_data.sub_fw_size);

		mt_set_gpio_mode(SPI_DATA_PIN, GPIO_MODE_00);
		mt_set_gpio_dir(SPI_DATA_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(SPI_DATA_PIN, GPIO_OUT_ZERO);
		dev_err(thp7212_data.dev, "fw update OK");
#if 0
		mdelay(200);
		register_dump();
#endif
		mdelay(60);//wait for the isp ready
		while((thp7212_i2c_read(THP7212_CAMERA_STATE)&0x80) != 0x80){
			mdelay(1);
			if(count++ == 20) {
				dev_err(thp7212_data.dev, "fw error!\n");
				return -1;
			}

		}
		return 0;
	}
	return -1;
}

static ssize_t sensor_show(struct device_driver *driver, const char *buf) 
{
	return sprintf(buf,"Sensor ID = %02x",thp7212_i2c_read(THP7212_MODULE_ID));
}

static ssize_t log_store(struct device_driver *driver, const char *buf, size_t count)
{
	reg_log = 1;
	return count;	
}
static ssize_t	log_show(struct device_driver *driver, const char *buf)
{
	reg_log = 0;
	return 1;
}

static ssize_t reg_show(struct device_driver *driver, char *buf)
{
	int i,size=0;
	int value;

	buf[0] ='\n';
	for(i=0xF000; i<0xF08F; i++) {
		value = thp7212_i2c_read(i);
		size = sprintf(buf,"%sreg[0x%04x]=%02x\n",buf,i,value);
	}
	return size;
}

static ssize_t reg1_show(struct device_driver *driver, char *buf)
{
	int i,size=0;
	int value;
	buf[0] ='\n';
	for(i=0xF090; i<0xF0A0; i++) {
		value = thp7212_i2c_read(i);
		size = sprintf(buf,"%s reg[0x%04x] = %02x\n",buf,i,value);
	}
	return size;
}

static int temp_reg = 0xF000;
static ssize_t regn_show(struct device_driver *driver, char *buf)
{
	int value;
	value = thp7212_i2c_read(temp_reg);
	return sprintf(buf,"reg[0x%04x] = %02x\n",temp_reg,value);
}

static ssize_t regn_store(struct device_driver *driver, const char *buf, size_t count)
{
	char _buf[10],*r;
	strncpy(_buf,buf,10);
	r = strchr(_buf,'\n');
	*r = 0;
	temp_reg = simple_strtol(_buf,NULL,16)&0xFFFF;
	return count;
}

static ssize_t reg_store(struct device_driver *driver, const char *buf, size_t count)
{
	int reg,value;
	char _buf[20],*r,*v;
	strncpy(_buf,buf,20);
	r = strchr(_buf,'=');
	if( r == NULL)
		dev_err(thp7212_data.dev,"Command Error!\n");
	*r = 0;
	v = strchr(r+1,'\n');
	if( v == NULL)
		dev_err(thp7212_data.dev,"Command Error!\n");
	*v = 0;

	reg = simple_strtol(_buf,NULL,16)&0xFFFF;
	value = simple_strtol(r+1,NULL,16)&0xFF;
	if(reg == THP7212_AF_SETTING){
		if((value & 0x80) == 0x80)
			af_debug = 1;
		else 
			af_debug = 0;
	}
	thp7212_i2c_write(reg,value);
	dev_err(thp7212_data.dev,"%s,%02x\n",buf,value);
	return count;
}

static DRIVER_ATTR(id,0666,sensor_show,NULL);
static DRIVER_ATTR(log,0666,log_show,log_store);
static DRIVER_ATTR(reg0,0666,reg_show,reg_store);
static DRIVER_ATTR(reg1,0666,reg1_show,reg_store);
static DRIVER_ATTR(regn,0666,regn_show,regn_store);

static struct attribute *_thp7212_attrs[] = {
	&driver_attr_reg0.attr,
	&driver_attr_reg1.attr,
	&driver_attr_regn.attr,
	&driver_attr_id.attr,
	&driver_attr_log.attr,
	NULL,
};

const struct attribute_group  thp7212_attrs = {
	.attrs = _thp7212_attrs,
};

const struct attribute_group  *thp7212_groups[] = {
	&thp7212_attrs,
	NULL,
};

static int thp7212_i2c_probe(struct i2c_client *client, const struct i2c_device_id *device_id)
{
	client->timing = 400;
	thp7212_data.i2c_client = client;
	client->dev.parent = thp7212_data.dev;
	dev_warn(thp7212_data.dev,"i2c probe OK\n");
	return 0;
}
static int thp7212_i2c_remove(struct i2c_client *client)
{
	thp7212_data.i2c_client = NULL;
	return 0;
}

static struct i2c_driver thp7212_i2c_driver = {
	.probe = thp7212_i2c_probe,
	.remove = thp7212_i2c_remove,
	.id_table = thp7212_i2c_id,
	.driver = {
		.name = THP7212_I2C_DEV,
	},
};

static int thp7212_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int thp7212_release(struct inode *inode, struct file *file)
{
	return 0;
}

#define THP7212_I2C_READ  _IOR('x',1,int)
#define THP7212_I2C_WRITE _IOW('x',2,int)
struct thp7212_i2c_op {
	unsigned int addr;
	unsigned char value; 
};

static long thp7212_ioctl( struct file *file, unsigned int cmd, unsigned long arg)
{
	struct thp7212_i2c_op buf;	
	int ret = 0;
	if(copy_from_user((void *)&buf, (void __user *)arg, sizeof(struct thp7212_i2c_op))) {
		dev_err(thp7212_data.dev,"copy from user error\n");
		ret = -1;
	}
	switch (cmd) {
		case THP7212_I2C_READ:
			buf.value = thp7212_i2c_read(buf.addr);
			if(copy_to_user((void __user *)arg, (void *)&buf, sizeof(struct thp7212_i2c_op))) {
				dev_err(thp7212_data.dev,"copy to user error\n");
				ret = -1;
			}	
			break;
		case THP7212_I2C_WRITE:
			ret = thp7212_i2c_write(buf.addr, buf.value);
			break;
	}
	return ret;
}

static const struct file_operations thp7212_fops = {
	.owner = THIS_MODULE,
	.open = thp7212_open,
	.release = thp7212_release,
	.unlocked_ioctl = thp7212_ioctl
};

static int thp7212_spi_probe(struct spi_device *device)
{
	struct mt_chip_conf *chip_config;
	chip_config = (struct mt_chip_conf *) device->controller_data;
	// speed = 134.3mHz/(1+2) = 44.7mHz, Under 50mHz
	chip_config->high_time = 1;
	chip_config->low_time = 2;
#ifdef SPI_FIFO_MODE 
	chip_config->com_mod = FIFO_TRANSFER;
#else
	chip_config->com_mod = DMA_TRANSFER;
	chip_config->tx_endian = 0; 
	chip_config->rx_endian = 0; 
#endif
	chip_config->cpol = 0; 
	chip_config->cpha = 0;
	spi_setup(device);
	thp7212_data.spi_device= device;
	dev_warn(thp7212_data.dev,"spi probe OK\n");
	return 0;
}

static int thp7212_spi_remove(struct spi_device *device)
{
	thp7212_data.spi_device= NULL;
	return 0;
}
static struct spi_driver thp7212_spi_driver = {
	.probe = thp7212_spi_probe,
	.remove = thp7212_spi_remove,
	.driver = {
		.name  = THP7212_SPI_DEV,
	},
};

static int thp7212_probe(struct platform_device *device)
{
	int err;
	spi_register_board_info(&thp7212_spi_info, 1);
	thp7212_data.pdevice = device;
	thp7212_data.dev = &device->dev;
	thp7212_data.flash_on = false;
	thp7212_data.sub_flash_status = false;
	thp7212_data.multi_shot_mode = false;

	if((err = spi_register_driver(&thp7212_spi_driver))) {
		goto spi_err;
	}

	thp7212_data.fw_readly = 0;
	INIT_DELAYED_WORK(&thp7212_data.fw_dworker,fw_dwork);
	schedule_delayed_work(&thp7212_data.fw_dworker,1000);
	dev_warn(thp7212_data.dev,"probe OK\n");
	thp7212_data.torch_lamp =  true;

	if(alloc_chrdev_region(&thp7212_dev, 0, 1, "thp7212")) {
		dev_err(thp7212_data.dev,"alloc_chrdev error");	
		goto spi_err;
	}

	thp7212_chardrv = cdev_alloc();
	if(thp7212_chardrv == NULL)
	{
		dev_err(thp7212_data.dev,"alloc mem for kobject failed\n");
		goto alloc_err;
	}

	cdev_init(thp7212_chardrv, &thp7212_fops);
	thp7212_chardrv->owner = THIS_MODULE;

	if(cdev_add(thp7212_chardrv, thp7212_dev, 1))
	{
		dev_err(thp7212_data.dev,"cdev_add failed\n");
		goto alloc_err;
	}

	thp7212_class = class_create(THIS_MODULE, "thp7212");
	if (IS_ERR(thp7212_class)) {
		int ret = PTR_ERR(thp7212_class);
		dev_err(thp7212_data.dev,"unable to create class, err = %d\n", ret);
		goto alloc_err;
	}
	device_create(thp7212_class, NULL, thp7212_dev, NULL, "thp7212");
	return 0;
alloc_err:
	unregister_chrdev_region(thp7212_dev, 1);
spi_err:
	i2c_del_driver(&thp7212_i2c_driver);
	thp7212_data.pdevice = NULL;
	thp7212_data.dev = NULL; 
	return err;
}

static int thp7212_remove(struct platform_device *device)
{
	thp7212_data.pdevice = NULL;
	thp7212_data.dev = NULL; 
	return 0;
}

static int thp7212_resume(struct platform_device *device)
{
	return 0;
}

static int thp7212_suspend(struct platform_device *device, pm_message_t state)
{
	return 0;
}

static struct platform_driver thp7212_platform_driver = {
	.probe	= thp7212_probe,
	.remove = thp7212_remove,
	.suspend = thp7212_suspend,
	.resume = thp7212_resume,
	.driver	= {
		.name = THP7212_DEV_NAME,
		.groups = thp7212_groups,
	},
};
static struct platform_device thp7212_platform_device = {
	.name = THP7212_DEV_NAME,
	.id	  = -1,
};

static int __init thp7212_init(void)
{
	thp7212_data.power_on = false;
	platform_driver_register(&thp7212_platform_driver);
	return platform_device_register(&thp7212_platform_device);
}

static void __exit thp7212_exit(void)
{
	platform_device_unregister(&thp7212_platform_device);
	platform_driver_unregister(&thp7212_platform_driver);
}

module_init(thp7212_init);
module_exit(thp7212_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping@tydtech.com");
MODULE_DESCRIPTION("Camera ISP driver for thp7212");

