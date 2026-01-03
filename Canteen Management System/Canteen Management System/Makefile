# ==============================
# Makefile for Canteen Management System
# ==============================

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall

# Source files
SRC = src/menuitem.c src/consumer.c src/order.c src/undo.c src/user.c canteenmanagement.c

# Output executable
OUT = CanteenApp.exe

# Default target
all: $(OUT)

# Build executable
$(OUT): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

# Clean build files
clean:
	del $(OUT)
