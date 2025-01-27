# General Makefile for C projects
# to set flags use $(flag_name) and make flag_name=10

# Run file with
# $ make PROGRAM_NAME="001_Multiples_of_3_or_5"

# Raylib doesn't like clang, use gcc instead!
PROGRAM_NAME = arduino
# PROGRAM_NAME = test

# SRC_FILES = test.c
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,${SRC_FILES})

#-fcolor-diagnostics \
# DFLAGS = -DEMULATION_ENABLE=1 -DDEBUG_ENABLE=1
CC = gcc
CCFLAGS = -xc -std=c99 -Wall -Wextra -Werror -Wpedantic \
		-pedantic-errors -pedantic -g -Wno-unused

IFLAGS = -I. -I./lib -I./lib/Adafruit_BusIO \
		 -I./lib/MCUFRIEND_kbv -I./lib/MCUFRIEND_kbv/extras/unused/ -I./lib/Adafruit_GFX_Library

# -Wno-unused-variable -Wno-unused-const-variable \
# -Wno-unused-value -Wno-unused-function \
# -Wno-unused-parameter -Wno-unused-but-set-variable \

LDFLAGS = -Wl,-rpath=./lib/raylib/ -L./lib/raylib -lraylib -lGL -lm -lpthread -ldl -lX11
# -lXrandr -lXinerama -lXi -lXcursor

FLAGS = $(CCFLAGS) $(IFLAGS) $(LDFLAGS) $(DFLAGS)

local: build run
build:
	@echo "Compiling... "
	@mkdir -p bin
	$(CC) $(FLAGS) $(SRC_FILES) -o bin/${PROGRAM_NAME}

run:
	@echo "Running... "
	@chmod +x bin/$(PROGRAM_NAME)
	@cd bin && ./$(PROGRAM_NAME)

clean:
	@echo "Cleaning..."
	@rm -rf ./bin


# raylib: ray_clean ray_build
# ray_clean:
# 	cd lib/sources/raylib/src && make clean

# ray_build:
# 	cd lib/sources/raylib/src && make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=OFF

# ray_build_shared:
# 	cd lib/sources/raylib/src && make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED GLFW_LINUX_ENABLE_WAYLAND=OFF
