VERSION = $(shell echo "`git describe --tags --abbrev=0`.`git rev-list --count HEAD`")

# Assembler
ASMFLAGS = --32

ifdef TEST
ASMFLAGS += --defsym TEST=1
endif

# Linker
LDFLAGS = -melf_i386 --oformat=binary

# C compiler
CC = gcc
CFLAGS = -Wall -Wextra -O2 -ffreestanding -m32 -DVERSION='"$(VERSION)"'

# Directories
BINDIR = ./bin
OBJDIR = ./obj

BOOTDIR = ./boot
KERNDIR = ./kernel
DRIVDIR = ./drivers
TESTDIR = ./test

SUBDIRS = $(BOOTDIR) $(KERNDIR) $(DRIVDIR)

# TEST
ifdef TEST
SUBDIRS += $(TESTDIR)
endif

# Files
C_HDRS   = $(wildcard *.h $(foreach fd, $(SUBDIRS), $(fd)/*.h))
C_SRCS   = $(wildcard *.c $(foreach fd, $(SUBDIRS), $(fd)/*.c))
ASM_SRCS = $(wildcard $(BOOTDIR)/*.s)
OBJS     = $(addprefix $(OBJDIR)/, $(C_SRCS:.c=.o))

all: os.img

# Build targets
os.img: $(BINDIR)/boot.bin $(BINDIR)/kernel.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BINDIR)/boot.bin of=$@ bs=512 seek=0 conv=notrunc
	dd if=$(BINDIR)/kernel.bin of=$@ bs=512 seek=1 conv=notrunc

# Bootloader
$(OBJDIR)/%.o: $(BOOTDIR)/%.s $(ASM_SRCS)
	mkdir -p $(@D)
	as $(ASMFLAGS) -I$(BOOTDIR) $< -o $@

$(BINDIR)/%.bin: $(OBJDIR)/%.o
	mkdir -p $(@D)
	ld $(LDFLAGS) -Ttext 0x7c00 -o $@ $<

# Kernel
$(BINDIR)/kernel.bin: $(OBJDIR)/kernel_entry.o $(OBJS)
	mkdir -p $(@D)
	ld $(LDFLAGS) -Ttext 0x1000 -o $@ $^

$(OBJDIR)/%.o: %.c $(C_HDRS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(KERNDIR)/%.s
	mkdir -p $(@D)
	as $(ASMFLAGS) $< -o $@

# Phony targets
PHONY += run
run: os.img
	killall qemu-kvm || exit 0
	/usr/libexec/qemu-kvm -drive if=floppy,file=$< &
	sleep 0.1
	vncviewer localhost:5900
	killall qemu-kvm || exit 0

PHONY += burn
burn: os.img
	sudo dd if=$< of=/dev/sde status=progress

burncheck: burn
	sudo dd if=/dev/sde of=os.img.chk status=progress
	diff os.img os.img.chk
	rm -f os.img.chk

PHONY += dump
dump: os.img
	hexdump $<

PHONY += dumpboot
dumpboot: $(BINDIR)/boot.bin
	hexdump $<

PHONY += objdumpboot
objdumpboot: $(BINDIR)/boot.bin
	objdump -b binary --adjust-vma=0x7c00 -D -m i386 $<

PHONY += dumpkern
dumpkern: $(BINDIR)/kernel.bin
	hexdump $<

PHONY += objdumpkern
objdumpkern: $(BINDIR)/kernel.bin
	objdump -b binary --adjust-vma=0x1000 -D -m i386 $<

PHONY += clean
clean:
	rm -rf ./bin ./obj os.img

.PHONY: $(PHONY)
