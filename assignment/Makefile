CC		:= bin/i686-elf-tools/bin/i686-elf-gcc
AS		:= bin/i686-elf-tools/bin/i686-elf-as
LD		:= bin/i686-elf-tools/bin/i686-elf-gcc

CFLAGS		:= -Wall -Wextra -ffreestanding -std=gnu99 -Wno-unused-parameter -Wno-return-type #-Os
ASFLAGS		:= -ffreestanding
LDFLAGS		:= -ffreestanding -nostdlib

MAKEFLAGS	:= -s --no-print-directory

kernel-o	= src/boot/boot.o \
		  src/boot/entry.o \
		  src/boot/idt.o \
		  src/boot/int.o \
		  src/boot/pic.o \
		  src/boot/print.o \
		  src/boot/ps2.o \
		  src/boot/string.o \
		  src/boot/vga.o \
		  src/alloc.o \
		  src/editor.o \
		  src/processes.o \
		  src/ramfs.o \
		  src/main.o

kernel-o-filter	= src/boot/alloc.o

all: kernel

%.o: %.c
	echo -e "  CC      $@"
	$(CC) $(CFLAGS) -c $< -I src/include -o $@

%.o: %.S
	echo -e "  AS      $@"
	$(CC) $(ASFLAGS) -c $< -o $@

kernel: src/boot/link.ld $(kernel-o)
	echo -e "  LD      $@"
	$(LD) $(LDFLAGS) -T src/boot/link.ld -o $@ $(kernel-o)

run: kernel
	echo -e "  QEMU    $@"
	qemu-system-i386 -m 32M -no-reboot -monitor none -kernel $<

clean:
	rm -f kernel $(filter-out $(kernel-o-filter),$(kernel-o))
