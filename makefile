CC      = gcc
LD      = ld
AS      = nasm
OBJCOPY = objcopy

INCLUDE = -Iinclude

CFLAGS = -m32 -ffreestanding -fno-pic -fno-pie -fno-stack-protector -nostdlib -nostartfiles -c $(INCLUDE)

LDFLAGS = -m elf_i386 -T linker.ld

BUILD = build

BOOTLOADER = boot/bootloader.asm
KENTRY	   = boot/kernel_entry.asm
KERNEL	   = src/kernel.c

CFILES   := $(wildcard src/*/*.c)
ASMFILES := $(wildcard src/*/*.asm)

OBJS_C   := $(patsubst src/%.c,$(BUILD)/%.o,$(CFILES))
OBJS_ASM := $(patsubst src/%.asm,$(BUILD)/%.o,$(ASMFILES))

all: compile

compile: $(BUILD)/kernel.img

$(BUILD):
	mkdir -p $(BUILD)

# Boot
$(BUILD)/bootloader.bin: $(BOOTLOADER) | $(BUILD)
	$(AS) -f bin $< -o $@

$(BUILD)/kernel_entry.o: $(KENTRY) | $(BUILD)
	$(AS) -f elf32 $< -o $@

# Kernel
$(BUILD)/kernel.o: $(KERNEL) | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

# Other dependencies
$(BUILD)/%.o: src/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: src/%.asm | $(BUILD)
	@mkdir -p $(dir $@)
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