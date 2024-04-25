# General Makefile for C projects
# to set flags use $(flag_name) and make flag_name=10

# Run file with
# $ make PROGRAM_NAME="001_Multiples_of_3_or_5"

# Raylib doesn't like clang, use gcc instead!

PROGRAM_NAME=main

#-fcolor-diagnostics \
FLAGS=-xc -std=c99 -Wall -Wextra -Werror -Wpedantic \
	  -pedantic-errors -pedantic  -g \
	  -Wno-unused-variable -Wno-unused-const-variable \
	  -Wno-unused-value -Wno-unused-function \
	  -Wno-unused-parameter -Wno-unused-but-set-variable \
	  -I./lib -L./lib/raylib \
	  -lraylib -lGL -lm -lpthread -ldl -lX11 \
	  -lXrandr -lXinerama -lXi -lXcursor

SRC_FILES=$(wildcard *.c)

local: clean build run
clean:
	@echo "Cleaning..."
	@rm -f ./bin/${PROGRAM_NAME}

build: clean
	@echo "Compiling... "
	@mkdir -p bin
	gcc ${FLAGS} ${SRC_FILES} -o bin/${PROGRAM_NAME}

run:
	@echo "Running... "
	@chmod +x bin/${PROGRAM_NAME}
	@cd bin && ./${PROGRAM_NAME}

# raylib: ray_clean ray_build
# ray_clean:
# 	cd lib/sources/raylib/src && make clean

# ray_build:
# 	cd lib/sources/raylib/src && make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=OFF

# ray_build_shared:
# 	cd lib/sources/raylib/src && make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED GLFW_LINUX_ENABLE_WAYLAND=OFF
