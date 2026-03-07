CC      = gcc
LD      = ld
AS      = nasm
OBJCOPY = objcopy

CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -fno-stack-protector -nostdlib -nostartfiles -c -Iinclude

LDFLAGS = -m elf_i386 -T linker.ld

BUILD = build
INCLUDE = include

BOOTLOADER = core/bootloader.asm
KENTRY	   = core/kernel_entry.asm
KERNEL	   = kernel.c

CFILES   := $(wildcard include/*.c)
ASMFILES := $(wildcard include/*.asm)

OBJS_C   := $(patsubst include/%.c,$(BUILD)/%.o,$(CFILES))
OBJS_ASM := $(patsubst include/%.asm,$(BUILD)/%.o,$(ASMFILES))

all: compile

compile: $(BUILD)/kernel.img

$(BUILD):
	mkdir -p $(BUILD)

# Core
$(BUILD)/bootloader.bin: $(BOOTLOADER) | $(BUILD)
	$(AS) -f bin $< -o $@

$(BUILD)/kernel_entry.o: $(KENTRY) | $(BUILD)
	$(AS) -f elf32 $< -o $@

# Kernel
$(BUILD)/kernel.o: $(KERNEL) | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@


# Other dependencies
$(BUILD)/%.o: include/%.c | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: include/%.asm | $(BUILD)
	$(AS) -f elf32 $< -o $@

# Mounting IMG
$(BUILD)/kernel.elf: $(BUILD)/kernel_entry.o $(BUILD)/kernel.o $(OBJS_C) $(OBJS_ASM)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD)/kernel.bin: $(BUILD)/kernel.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD)/kernel.img: $(BUILD)/bootloader.bin $(BUILD)/kernel.bin
	cat $^ > $@


run: $(BUILD)/kernel.img
	qemu-system-i386 $<

clean:
	rm -rf $(BUILD)