#ifndef __THP7212_H__
#define __THP7212_H__

#include <linux/workqueue.h>
//main
#define THP7212_DEV_NAME		"thp7212"
#define THP7212_I2C_DEV			"thp7212-i2c"
#define THP7212_SPI_DEV			"thp7212-spi"
#define THP7212_REAR_FW			"thp7212_rear_fw.bin"
#define THP7212_SUB_FW			"thp7212_sub_fw.bin"
#define THP7212_I2C_NUM			1
#define THP7212_I2C_ADDR		0x60
#define SPI_FIFO_SIZE 32
#define SPI_DMA_SIZE 2048*20
#ifdef SPI_FIFO_MODE
#define SPI_DATA_SIZE SPI_FIFO_SIZE
#else
#define SPI_DATA_SIZE SPI_DMA_SIZE
#endif
//gpio
#define SPI_CS_PIN	(GPIO80 | 0x80000000)
#define SPI_DATA_PIN	(GPIO83 | 0x80000000)

#if defined(K551)
#define ISP_CORE_GPIO_EN_PIN (GPIO11 | 0x80000000)
#else
#define ISP_CORE_GPIO_EN_PIN (GPIO58 | 0x80000000)
#endif

#define ISP_RESET_GPIO_PIN (GPIO9 | 0x80000000)
#ifndef GPIO_VCAM_MCLOCK_PIN
#define GPIO_VCAM_MCLOCK_PIN (GPIO122 |0x80000000)
#endif

//regiter
//info
#define THP7212_FW_VER			0xF000			 
#define THP7212_CAMERA_STATE	0xF001  // firmware download  for Main Camera or Sub Camera according to Camera ID
#define THP7212_MIPI_STATE		0xF002
#define THP7212_WORK_NUM		0xF005
#define THP7212_MODULE_ID		0xF006  //Rear Camera:0x40 Sub Camera:0xC0
#define THP7212_CUSTOM_ID		0xF007	//ID: 0x14
//setting
#define THP7212_OUTCONTROL		0xF008  // Write 0x00 to Output Control Register (0xF008) to disable output from ISP.
#define THP7212_OUTMODE			0xF009  //bit0:Preview output 0:YUV 1:JPEG
#define THP7212_YUV_FORMAT		0xF00A
#define THP7212_MIRROR_FLIP		0xF00C	//bit0: 0:normal 1:flip bit1: 0:normal 1:mirror
#define THP7212_PREVIEW_SIZE	0xF00D  // Set Preview Image Size Register (0xF00D), (if size is changed from previous size).
#define THP7212_STLIMG_SIZE		0xF00E
#define THP7212_IMAGE_SIZE		0xF00F
//capture
#define THP7212_CAPTURE_MODE	0xF010	 
#define THP7212_CAPTURE_OK		0xF011
#define THP7212_BURST_NUM		0xF012
#define THP7212_STILL_CAP_MODE	0xF013
#define THP7212_EXPOSURE_POS	0xF014 //0xF014 - 0xF017
#define THP7212_SCENE_MODE		0xF018
#define THP7212_DETECTED_SCENE	0xF019
#define THP7212_JPEG_COMPRESS	0xF01B
#define THP7212_JPEG_SIZE		0xF01C //0xF01C - 0xF01F
//AE
#define THP7212_AE_CONTROL		0xF020
#define THP7212_AE_AREA			0xF021
#define THP7212_EXP_COMPRESS	0xF022
#define THP7212_FLICKER_MODE	0xF023
#define THP7212_FLICKER_STATUS  0xF024
#define THP7212_DIR_OF_PHONE	0xF025
#define THP7212_SHUTTER_SPH		0xF026
#define THP7212_SHUTTER_SPL		0xF027
#define THP7212_GAIN_H			0xF028
#define THP7212_GAIN_L			0xF029
#define THP7212_ISO_H			0xF02A
#define THP7212_ISO_L			0xF02B
#define THP7212_ESTIMATE		0xF02C //TBD
#define THP7212_STROBE_MODE		0xF030
#define THP7212_TORCH_MODE		0xF031
#define THP7212_STROBE_STATUS	0xF032
#define THP7212_STROBE_LIGHT	0xF035
#define THP7212_HOSTLED_STATUS	0xF036
#define THP7212_STROBE_HOST		0xF037
//AWB
#define THP7212_AWB_CONCTRL		0xF038
#define THP7212_AWB_MODE		0xF039
//AF
#define THP7212_AF_CONTROL		0xF040
#define THP7212_AF_SETTING		0xF041
#define THP7212_AF_STATUS		0xF042
#define THP7212_AF_LENS			0xF044
#define THP7212_AF_H_START_H	0xF046
#define THP7212_AF_H_START_L	0xF047
#define THP7212_AF_V_START_H	0xF048
#define THP7212_AF_V_START_L	0xF049
#define THP7212_AF_H_STOP_H		0xF04A
#define THP7212_AF_H_STOP_L		0xF04B
#define THP7212_AF_V_STOP_H		0xF04C
#define THP7212_AF_V_STOP_L		0xF04D
//image
#define THP7212_COLOR_MODE		0xF051
#define THP7212_SATURATION		0xF052
#define THP7212_SHARPNESS		0xF053
#define THP7212_HUE				0xF055
#define THP7212_BRIGHTNESS		0xF056
#define THP7212_CONTRAST		0xF057
#define THP7212_LUMA_NR			0xF058
#define THP7212_CHROMA_NR		0xF059
#define THP7212_RM_SPIKE_NOISE	0xF05A
#define THP7212_FACE1_H_START_U	0xF066
#define THP7212_FACE1_H_START_L	0xF067
#define THP7212_FACE1_V_START_U	0xF068
#define THP7212_FACE1_V_START_L	0xF069
#define THP7212_FACE1_H_STOP_U	0xF06A
#define THP7212_FACE1_H_STOP_L	0xF06B
#define THP7212_FACE1_V_STOP_U	0xF06C
#define THP7212_FACE1_V_STOP_L	0xF06D //0xF06E - 0xF08E face2 to face 5
#define THP7212_ZOOM_FACTOR		0xF061
// face detection
#define THP7212_FACE_DETECTION	0xF064
#define THP7212_FACE_COUNT		0xF065
#define THP7212_FACE_POSTION	0xF066 //0xF066 - 0xF08D

struct thp7212_private_data {
	struct platform_device  *pdevice;
	struct device			 *dev;
	struct i2c_client       *i2c_client;
	struct spi_device       *spi_device;
	struct work_struct      irq_worker;
	struct delayed_work     fw_dworker;
	char					*rear_fw;
	char					*sub_fw;
	int						fw_readly;
	int						rear_fw_size;
	int						sub_fw_size;
	bool					power_on;
	bool					flash_on;
	bool					sub_flash_status;
	bool					multi_shot_mode;
	bool					video_mode;
	bool					torch_lamp;
	int						flash_mode;
	int						af_status;
	int						af_mode;
};

typedef struct
{
	unsigned int  init_delay;
	unsigned int  effect_delay;
	unsigned int  awb_delay;
	unsigned int  af_switch_delay_frame;
}sensor_delay_info_struct;
//functions
extern int iReadReg(u16 a_u2Addr , u8 * a_puBuff , u16 i2cId);
extern int iWriteReg(u16 a_u2Addr , u32 a_u4Data , u32 a_u4Bytes , u16 i2cId);
extern int thp7212_get_module_id(void);
extern int thp7212_set_filp_mirror(char value);
extern int thp7212_set_preview_size(int index);
extern int thp7212_set_still_size(int index);
extern int thp7212_start_preview(int size);
extern int thp7212_stop_preview(int size);
extern int thp7212_cancel_af(void);
extern int thp7212_oneshot_af(void);
extern int thp7212_get_af_status(void);
extern int thp7212_set_focus_areas(void);
extern void thp7212_face_detection(int index);
extern void thp7212_set_rotation(int index);
extern void thp7212_set_image_size(int index);
extern int thp7212_power_on_reset(void);
extern int thp7212_power_off(void);
extern int thp7212_fw_download(int index);
extern int thp7212_capture(int burst_num);
extern int thp7212_set_af_window(unsigned int value, unsigned int width, unsigned int height);
extern int thp7212_continuous_focus(void);
extern int thp7212_set_ae_window(unsigned int *value);
extern void thp7212_get_delay_frame(unsigned int *d);
extern void thp7212_set_ae_iso(unsigned int value);
extern void thp7212_set_scene_mode(unsigned int value);
extern void thp7212_set_flashlight_mode(unsigned int value);
extern void thp7212_get_flashlight_mode(unsigned int value);
extern void thp7212_set_multi_shot(unsigned int value);
extern void thp7212_set_ev_param(unsigned int value);
extern void thp7212_set_awb_mode(unsigned int value);
extern void thp7212_set_fliker_mode(unsigned int value);
extern void thp7212_set_effect(unsigned int value);
extern void thp7212_start_video(void);
extern void thp7212_continuous_shot(void);
extern int thp7212_isp_info(char *info);
extern void thp7212_set_zoom(unsigned int zoom);
extern int thp7212_get_isospeed(void);
extern int thp7212_get_extime(void);
extern int thp7212_get_gain(void);
extern int thp7212_get_flash_status(void);
extern void thp7212_set_contrast(unsigned int value);
extern void thp7212_set_bright(unsigned int value);
extern void thp7212_set_saturation(unsigned int value);
extern void thp7212_set_hue(unsigned int value);
extern void thp7212_set_edge(unsigned int value);
extern void thp7212_set_ae_metering(unsigned int value);
extern void thp7212_flashtriggercheck(unsigned int *value);
extern void thp7212_flash_init(void);
#endif
