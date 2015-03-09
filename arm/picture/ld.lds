SECTIONS
{
	. = 0x57000000;
	.text : {*(.text);}

	. = ALIGN(4);
	.data : {*(.data);}

	. = ALIGN(4);
	.bss : {*(.bss);}
}
