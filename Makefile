OBJ_DIR= ./build
SRC_DIR = ./src

CC = i686-elf-gcc
CFLAGS = -std=c2x -ffreestanding -nostdlib -I '$(SRC_DIR)/kernel/library' -I '$(SRC_DIR)/libc' -I '$(SRC_DIR)/boot/multiboot' -Wall -Wextra -Wpedantic -Wvla -Wimplicit-fallthrough -fanalyzer -ggdb
LDFLAGS = -ffreestanding -nostdlib  -lgcc -ggdb
SRC_C := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ_C := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_C))

NASM_FLAGS := -gdwarf -f elf32
SRC_NASM := $(shell find $(SRC_DIR) -type f -name '*.nasm.asm')
OBJ_NASM := $(patsubst $(SRC_DIR)/%.nasm.asm, $(OBJ_DIR)/%.nasm.o, $(SRC_NASM))

SRC_GAS := $(shell find $(SRC_DIR) -type f -name '*.S')
OBJ_GAS := $(patsubst $(SRC_DIR)%.S, $(OBJ_DIR)%.S.o, $(SRC_GAS))

# Name is hardcoded in /isodir/grub/grub.cfg
OS = $(SRC_DIR)/isodir/boot/os.bin
OS_ISO = $(OBJ_DIR)/os.iso

.PHONY: clean run debug

all: $(OS_ISO)

$(OS_ISO): $(OBJ_C) $(OBJ_NASM) $(OBJ_GAS)
	@printf "\n"
	$(CC) -T linker.ld $(OBJ_C) $(OBJ_NASM) $(OBJ_GAS) -o $(OS) $(LDFLAGS)
	@printf "\n"
	grub-file --is-x86-multiboot $(OS)
	grub-mkrescue -o $(OS_ISO) $(SRC_DIR)/isodir

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.nasm.o: $(SRC_DIR)/%.nasm.asm
	@mkdir -p $(shell dirname $@)
	nasm $< -o $@ $(NASM_FLAGS)

$(OBJ_DIR)/%.S.o: $(SRC_DIR)/%.S
	@mkdir -p $(shell dirname $@)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	rm $(OS)

run: all
	qemu-system-i386 -cdrom $(OS_ISO)

debug: all
	!(pgrep gf2) && setsid -f gf2 &
	qemu-system-i386 -cdrom $(OS_ISO) -S -gdb tcp::26000 -no-shutdown -no-reboot -d int

