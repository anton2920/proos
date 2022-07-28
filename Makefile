# Linker
LDFLAGS = -melf_i386 --oformat=binary

# C compiler
CC = gcc
CFLAGS = -Wall -Wextra -O2 -ffreestanding -m32

# Directories
BINDIR = ./bin
OBJDIR = ./obj

BOOTDIR = ./boot
KERNDIR = ./kernel
DRIVDIR = ./drivers

SUBDIRS = $(BOOTDIR) $(KERNDIR) $(DRIVDIR)

# Files
C_HDRS   = $(wildcard *.h $(foreach fd, $(SUBDIRS), $(fd)/*.h))
C_SRCS   = $(wildcard *.c $(foreach fd, $(SUBDIRS), $(fd)/*.c))
ASM_SRCS = $(wildcard $(BOOTDIR)/*.s)
OBJS = $(addprefix $(OBJDIR)/, $(C_SRCS:.c=.o))

all: os.img

# Build targets
os.img: $(BINDIR)/boot.bin $(BINDIR)/kernel.bin
	cat $^ > $@
	truncate -s 1M $@

# Bootloader
$(OBJDIR)/%.o: $(BOOTDIR)/%.s $(ASM_SRCS)
	mkdir -p $(@D)
	as --32 -I$(BOOTDIR) $< -o $@

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
	as --32 $< -o $@

# Phony targets
PHONY += run
run: os.img
	killall qemu-kvm || exit 0
	/usr/libexec/qemu-kvm -drive format=raw,file=$< &
	sleep 0.1
	vncviewer localhost:5900
	killall qemu-kvm || exit 0

dump: os.img
	hexdump $<

dumpboot: $(BINDIR)/boot.bin
	hexdump $<

objdumpboot: $(BINDIR)/boot.bin
	objdump -b binary --adjust-vma=0x7c00 -D -m i386 $<

dumpkern: $(BINDIR)/kernel.bin
	hexdump $<

objdumpkern: $(BINDIR)/kernel.bin
	objdump -b binary --adjust-vma=0x1000 -D -m i386 $<

PHONY += clean
clean:
	rm -rf ./bin ./obj os.img

.PHONY: $(PHONY)
