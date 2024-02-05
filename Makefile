# AVR-GCC compiler and flags
CC = avr-gcc
AR = avr-ar
MCU = atmega88pa

# Directories
SRC_DIR = src
OBJ_DIR = build
LIB_DIR = dist

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBS = $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/libavrhal-%.a, $(SRCS))

# Compiler flags
CFLAGS = -mmcu=$(MCU) -Wall -Os

# Build rules
all: $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/libavrhal-%.a: $(OBJ_DIR)/%.o
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $<

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

.PHONY: all clean
