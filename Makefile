CC      = gcc
LD      = ld
AS      = nasm
OBJCOPY = objcopy

SRC        = src
CINCLUDE   = include
CFLAGS     = -m32 -O2 -ffreestanding -fno-pic -fno-pie -fno-stack-protector \
             -nostdlib -nostdinc -nostartfiles -I$(CINCLUDE) -c
LDFLAGS    = -m elf_i386 -T linker.ld

BUILD      = build
BOOTLOADER = $(SRC)/boot/bootloader.asm
KENTRY     = $(SRC)/boot/kernel_entry.asm
KERNEL_C   = $(SRC)/kernel.c

CORE_C_OBJ   := $(patsubst $(SRC)/core/%.c,   $(BUILD)/%.o, $(wildcard $(SRC)/core/*.c))
CORE_ASM_OBJ := $(patsubst $(SRC)/core/%.asm, $(BUILD)/%.o, \
                  $(filter-out $(BOOTLOADER) $(KENTRY), $(wildcard $(SRC)/core/*.asm)))

OBJ := \
	$(BUILD)/kernel_entry.o \
	$(BUILD)/kernel.o \
	$(CORE_C_OBJ) \
	$(CORE_ASM_OBJ)

.PHONY: all run clean

all: $(BUILD)/kernel.img

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/bootloader.bin: $(BOOTLOADER) | $(BUILD)
	$(AS) -f bin $< -o $@

$(BUILD)/kernel_entry.o: $(KENTRY) | $(BUILD)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel.o: $(KERNEL_C) | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: $(SRC)/core/%.c | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: $(SRC)/core/%.asm | $(BUILD)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD)/kernel.bin: $(BUILD)/kernel.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD)/kernel.img: $(BUILD)/bootloader.bin $(BUILD)/kernel.bin
	cat $^ > $@
	truncate -s 1M $@

run: $(BUILD)/kernel.img
	qemu-system-i386 -drive format=raw,file=$<,index=0,media=disk

debug: $(BUILD)/kernel.img
	qemu-system-i386 -drive format=raw,file=build/kernel.img,index=0,media=disk -serial stdio

clean:
	rm -rf $(BUILD)