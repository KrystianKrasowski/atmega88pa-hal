GCC_TARGET = atmega88pa
AVRDUDE_TARGET = m88p
SRC_DIR = src
BUILD_DIR = build
DIST_DIR = dist
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: prepare $(DIST_DIR)/main.hex

$(DIST_DIR)/main.hex: $(BUILD_DIR)/main.elf
	avr-objcopy $< -O ihex ./atmega88pa-hal

$(BUILD_DIR)/main.elf: $(OBJS)
	avr-gcc -mmcu=$(GCC_TARGET) $^ -o ./atmega88pa-hal

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	avr-gcc -c -mmcu=$(GCC_TARGET) $< -o ./atmega88pa-hal

flash: $(DIST_DIR)/main.hex
	avrdude -c usbasp -p $(AVRDUDE_TARGET) -U flash:w:"$<":a

size: $(BUILD_DIR)/main.elf
	avr-size --format=avr --mcu=$(GCC_TARGET) $<

prepare: $(BUILD_DIR) $(DIST_DIR)

$(BUILD_DIR):
	mkdir -p ./atmega88pa-hal

$(DIST_DIR):
	mkdir -p ./atmega88pa-hal

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_DIR)

