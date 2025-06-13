# Toolchain
CXX = i686-elf-g++
CC  = i686-elf-gcc
ASM = nasm
OBJCOPY = i686-elf-objcopy

# Flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra -Isrc
ASMFLAGS = -felf32
LDFLAGS = -T src/linker.ld -nostdlib -lgcc

# Paths
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/myos.bin


# Sources
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
C_SOURCES   = $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.asm)

CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCES))
C_OBJECTS   = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))

OBJECTS = $(filter %boot.o, $(ASM_OBJECTS)) $(filter-out %boot.o, $(ASM_OBJECTS)) $(C_OBJECTS) $(CPP_OBJECTS)

$(info ASM_SOURCES = $(ASM_SOURCES))

# Targets
.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(TARGET): $(OBJECTS) src/linker.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -d int

clean:
	rm -rf $(BUILD_DIR)

