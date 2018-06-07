OBJECTS = loader.o kmain.o io.o IDT.o GDT.o  
CC = gcc
AS = nasm
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra  -c -std=c99 \
		 -Ikernel/include
LDFLAGS = -T link.ld -melf_i386
ASFLAGS = -f elf
QEMU_FLAGS = -serial file:serial.log
ISODIR = iso
KERNEL_DIR = kernel
ASM_DIR = $(KERNEL_DIR)/asm
NAME=mumin

include version.mk


all: kernel.elf

.SILENT:

# Compile kernel
kernel.elf: $(OBJECTS)
		ld $(LDFLAGS) $(OBJECTS) -o mumin_kernel.elf


# Echo the version numbers into version.h 
update_version: 
	echo "#pragma once" > $(KERNEL_DIR)/include/version.h
	echo "#define VERSION_MAJOR $(VERSION_MAJOR)" >> $(KERNEL_DIR)/include/version.h
	echo "#define VERSION_MINOR $(VERSION_MINOR)" >> $(KERNEL_DIR)/include/version.h
	echo "#define VERSION_PATCH $(VERSION_PATCH)" >> $(KERNEL_DIR)/include/version.h
	echo 'static const char* VERSION_STRING = "$(VERSION_STRING)";' >> $(KERNEL_DIR)/include/version.h
	
	echo 'menuentry "MuminOS $(VERSION_STRING)" { ' > $(ISODIR)/boot/grub/grub.cfg
	echo '	multiboot /boot/mumin_kernel.elf ' >> $(ISODIR)/boot/grub/grub.cfg
	echo '}' >> $(ISODIR)/boot/grub/grub.cfg

os.iso: kernel.elf
	cp mumin_kernel.elf $(ISODIR)/boot/mumin_kernel.elf 
	grub2-mkrescue -o $(NAME)-$(VERSION_STRING).iso $(ISODIR)

run: os.iso
	qemu-system-i386 -cdrom $(NAME)-$(VERSION_STRING).iso $(QEMU_FLAGS)

%.o: $(KERNEL_DIR)/%.c 
	$(CC) $(CFLAGS) $< -o $@
%.o: $(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# Clean the directory
clean:
	rm -rf *.o *.elf *.iso
