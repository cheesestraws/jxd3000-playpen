ENTRY(_init_proc)

PHDRS
{
	code PT_LOAD;
	data PT_LOAD;
}

SECTIONS
{
	. = 0x51400000;
	/* . = 0x52000000; */
	.init : { *(.init) } :code
	.text :	{ *(.text) } :code
	.fini : { *(.fini) } :code
	. = ALIGN(4);
	.dlsym : { *(.dlsym) } :code
	.dlstr : { *(.dlstr) } :code
	. = ALIGN(0x20000);
	.ctors : { *(.ctors) } :code
	.dtors : { *(.dtors) } :code
	. = ALIGN(4);
	.data : { *(.data); *(.sdata); *(.rodata*) } :data
	. = ALIGN(4);
	.sbss : { KEEP(*(.sbss)); *(.scommon) } :data
	. = ALIGN(4);
	/* _bss_start = .; */
	.bss  : { KEEP(*(.bss))  } :data
	/* _bss_end = .; */
	end = .; _end = .; __end = .;
}
