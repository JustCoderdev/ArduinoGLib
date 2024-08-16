# General Makefile for C projects
# to set flags use $(flag_name) and make flag_name=10

# Run file with
# $ make PROGRAM_NAME="001_Multiples_of_3_or_5"

# Raylib doesn't like clang, use gcc instead!
PROGRAM_NAME = arduino

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,${SRC_FILES})

#-fcolor-diagnostics \
# DFLAGS = -DEMULATION_ENABLE=1 -DDEBUG_ENABLE=1
CC = gcc
CCFLAGS = -xc -std=c99 -Wall -Wextra -Werror -Wpedantic \
		-pedantic-errors -pedantic -g -Wno-unused

# JustCoderdev Makefile for C projects v4 (no semv)

PROGRAM_NAME = executable

SRC_FILES = main.c GFX_Adafruit.c GFX_Raylib.c
OBJ_FILES = $(patsubst %.c,%.o,${SRC_FILES})
# CORE_FILES = lib/core/core_bit.c \
# 			 lib/core/core_buff.c \
# 			 lib/core/core_net.c \
# 			 lib/core/core_str.c \
# 			 lib/core/core_memdeb.c \
# 			 lib/core/core_logger.c

CC = gcc
DFLAGS = -DDEBUG_ENABLE=1
IFLAGS = -I. -I./lib/include -I./lib/Adafruit_BusIO \
		 -I./lib/MCUFRIEND_kbv -I./lib/MCUFRIEND_kbv/extras/unused/ \
		 -I./lib/Adafruit_GFX_Library
CCFLAGS = -xc -std=c89 -Wall -Wextra -Werror -Wno-pedantic \
		 -Wno-unused -g -pedantic-errors -pedantic
RAYFLAGS = -Wl,-rpath=./lib/raylib/ -L./lib/raylib -lraylib
LDFLAGS = -lGL -lm -lpthread -ldl -lX11
# -lXrandr -lXinerama -lXi -lXcursor

FLAGS =  $(DFLAGS) $(IFLAGS) $(CCFLAGS) $(RAYFLAGS) $(LDFLAGS)

local: build run
build:
	@echo "Compiling... "
	@mkdir -p bin
	@cp -f ./DTNS_* ./bin
	$(CC) $(FLAGS) $(SRC_FILES) $(CORE_FILES) -o bin/${PROGRAM_NAME}

run:
	@echo "Running... "
	@chmod +x bin/$(PROGRAM_NAME)
	@cd bin && ./$(PROGRAM_NAME)

.PHONY: clean
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
