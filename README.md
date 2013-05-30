jxd3000-playpen
===============

Homebrew code for the JXD3000 handheld console.  Builds on @uli's actsemi project.

Before you do aything with this code at all, you should read and understand this article:

[Uli's WIP Emporium: Ewww, MIPS! (Spectrum emulator)](http://dingoowip.blogspot.com.es/2012/12/ewww-mips-spectrum-emulator.html)

All sorted?  Great.


italicdemo
----------

Another simple demo.  This displays a message in two ancient languages from Italy: Latin and Etruscan.  Both messages say "Rob made me."

![](images/italic.jpg?raw=true)


ldscript
--------

This folder contains a replacement actsemi.ld file, which you can try if:

* You have a big project
* Linking it gives you alarming errors about segmentation (about the small data
  section)
* The resulting .bin file makes the spinner thing freeze when you try to run it, 
  then the watchdog reboots the console.

To see if you need it, dump the program headers.  You can do this using the
'readelf' tool.  If your readelf output looks like this (note the *one* line
under 'Program Headers' with 'Read/write/execute' flags):

	[mipsel]$ mipsel-sde-elf-readelf -l ./a.out 
	
	Elf file type is EXEC (Executable file)
	Entry point 0x51400000
	There are 1 program headers, starting at offset 52
	
	Program Headers:
	  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
	  LOAD           0x000058 0x51400000 0x51400000 0x6ab08 0x6c706 RWE 0x8
	
	 Section to Segment mapping:
	  Segment Sections...
	   00     .init .text .fini .dlsym .dlstr .data .bss 

then you need to use this.

After you've linked using this link script, the output should look more like
this.  This has *two* lines under Program headers, the first having Read/Execute
and the second Read/Write, and the section to segment mapping shows that the data
segment is in the read/write segment.

	[mipsel]$ mipsel-sde-elf-readelf -l ./a.out 
	
	Elf file type is EXEC (Executable file)
	Entry point 0x51400000
	There are 2 program headers, starting at offset 52
	
	Program Headers:
	  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
	  LOAD           0x000074 0x51400000 0x51400000 0x5540b 0x5540b R E 0x4
	  LOAD           0x055480 0x51460000 0x51460000 0x0ab08 0x0c706 RW  0x8
	
	 Section to Segment mapping:
	  Segment Sections...
	   00     .init .text .fini .dlsym .dlstr 
	   01     .data .bss 
