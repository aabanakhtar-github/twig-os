CXX = i686-elf-g++
CC  = i686-elf-gcc
ASM = nasm
OBJCOPY = i686-elf-objcopy

CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-rtti -fno-exceptions -Isrc
ASMFLAGS = -felf32
LDFLAGS = -T src/linker.ld -nostdlib -lgcc

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/myos.bin

CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.asm)

CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))

OBJECTS = $(filter %boot.o, $(ASM_OBJECTS)) $(filter-out %boot.o, $(ASM_OBJECTS) $(CPP_OBJECTS))

.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(TARGET): $(OBJECTS) src/linker.ld
	$(CC) -ffreestanding -O2 -nostdlib -T src/linker.ld -o $@ $(OBJECTS) -lgcc

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
