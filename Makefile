# General Makefile for C projects
# to set flags use $(flag_name) and make flag_name=10

# Run file with
# $ make FILE_ENTRY="001_Multiples_of_3_or_5"

# Raylib doesn't like clang, use gcc instead!

FILE_ENTRY=main.c
FLAGS=-xc -Wall -Wextra -Werror -Wpedantic \
	  -Wno-unused-variable \
	  -Wno-unused-const-variable  -Wno-unused-value \
	  -Wno-unused-function -Wno-unused-parameter -Wno-unused-but-set-variable \
	  -pedantic -pedantic-errors -std=c99 -g \
	  -I./lib -L./lib/raylib \
	  -lraylib -lGL -lm -lpthread -ldl -lX11 -lXrandr -lXinerama -lXi -lXcursor
#-fcolor-diagnostics \

SRC_FILES=${FILE_ENTRY} ListView.c
#$(wildcard *.c)

local: clean build run
clean:
	@echo "Cleaning..."
	@rm -f ./bin/${FILE_ENTRY:.c=}

build: clean
	@echo "Compiling... "
	@mkdir -p bin
	@gcc ${FLAGS} ${SRC_FILES} -o bin/${FILE_ENTRY:.c=}

run:
	@echo "Running... "
	@chmod +x bin/${FILE_ENTRY:.c=}
	@cd bin && ./${FILE_ENTRY:.c=}

raylib: ray_clean ray_build
ray_clean:
	cd raylib/src && make clean

ray_build:
	cd raylib/src && make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=OFF

ray_build_shared:
	cd raylib/src && make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED GLFW_LINUX_ENABLE_WAYLAND=OFF

