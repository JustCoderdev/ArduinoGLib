{ pkgs ? import <nixpkgs> {
#config.allowUnsupportedSystem = true;
} }:

let
	Leka-Arduino-Makefile = pkgs.stdenv.mkDerivation {
		name = "Leka-Arduino-Makefile";
		src = pkgs.fetchFromGitHub {
			owner = "leka";
			repo = "Arduino-Makefile";
			rev = "12b5bc0";
			hash = "sha256-OilIPJThtmIMINuI8NMRHYQBNs3VjJDYQu48IIX6ErI=";
		};

		sourceRoot = ".";
		installPhase = ''
			runHook preInstall
			mkdir -p $out
			cp -r * $out

			# Patch issues
			sed --in-place 's/\\#/#/' $out/source/*.mk
			sed --in-place 's/\\#/#/'  $out/source/bin/lib-detection
			sed --in-place 's/\\s/\\\\s/' $out/source/bin/lib-detection
			sed --in-place 's/\\\./\\\\\./' $out/source/bin/lib-detection
			sed --in-place 's/gcc-ar/ar/' $out/source/Arduino.mk

			runHook postInstall
		'';
	};

	Bare-Arduino-Project = pkgs.stdenv.mkDerivation {
		name = "Bare-Arduino-Project";
		src = pkgs.fetchFromGitHub {
			owner = "ladislas";
			repo = "Bare-Arduino-Project";
			rev = "2.0.0";
			hash = "sha256-0gD2jY8xHIE+9RLQ1YVUEvp67SgWLN/KsZgDVcuv4oE=";
		};

		sourceRoot = ".";
		installPhase = ''
			runHook preInstall
			mkdir -p $out
			cp -r * $out
			runHook postInstall
		'';
	};
in

pkgs.mkShell {
	nativeBuildInputs = let
		avrpkgs = pkgs.pkgsCross.avr.buildPackages;
		pypkgs = pkgs.python312Packages;
	in [
		Leka-Arduino-Makefile
		Bare-Arduino-Project

		pkgs.git
		pkgs.arduino
		pkgs.arduino-core-unwrapped

		avrpkgs.gcc
		avrpkgs.binutils
		avrpkgs.avrdude

		pypkgs.pyserial
	];

	#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.glib.out}/lib"
	shellHook = ''
rm -f ./Makefile
cat >Makefile <<EOL
### DISCLAIMER
### This is an example Makefile and it MUST be configured to suit your needs.
### For detailed explanations about all the available options,
### please refer to https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md

### DOUBLE DISCLAIMER (aha, you didn't expect that!)
### This file has been autogenerated by a nix-shell, in short, if you need to change
### Something do it there

### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR       = \$(shell pwd)

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR         = ${Leka-Arduino-Makefile}/source

### ARDUINO_DIR
### Path to the Arduino application and resources directory.
ARDUINO_DIR       = ${pkgs.arduino-core-unwrapped}/share/arduino

### USER_LIB_PATH
### Path to where the your project's libraries are stored.
USER_LIB_PATH     :=  \$(realpath \$(PROJECT_DIR)/lib)

### BOARD_TAG & BOARD_SUB
### For Arduino IDE 1.0.x
### Only BOARD_TAG is needed. It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
# BOARD_TAG         = mega2560
### For Arduino IDE 1.6.x
### Both BOARD_TAG and BOARD_SUB are needed. They must be set to the board you are currently using. (i.e BOARD_TAG = uno, mega, etc. & BOARD_SUB = atmega2560, etc.)
### Note: for the Arduino Uno, only BOARD_TAG is mandatory and BOARD_SUB can be equal to anything
BOARD_TAG         = uno
#BOARD_SUB         = atmega2560

### MONITOR_PORT
### The port your board is connected to. Using an '*' tries all the ports and finds the right one. Choose one of the two.
# MONITOR_PORT      = /dev/ttyUSB*
MONITOR_PORT      = /dev/ttyACM*

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 9600

### AVR_TOOLS_DIR
### Path to the AVR tools directory such as avr-gcc, avr-g++, etc.
AVR_TOOLS_DIR     = ${pkgs.pkgsCross.avr.buildPackages.gcc}
AR_NAME = avr-ar

### AVRDUDE
### Path to avrdude directory.
AVRDUDE           = ${pkgs.pkgsCross.avr.buildPackages.avrdude}

### CFLAGS_STD
CFLAGS_STD        = -std=gnu11

### CXXFLAGS_STD
### You can choose wich ever you like
# CXXFLAGS_STD      = -std=gnu++11
CXXFLAGS_STD      = -std=gnu++17

### OBJDIR
### Don't touch this!
### This is were you put the binaries you just compile using 'make'
CURRENT_DIR       = \$(shell basename \$(CURDIR))
OBJDIR            = \$(PROJECT_DIR)/build/\$(CURRENT_DIR)/\$(BOARD_TAG)



## Extra LIBs

ARDUINO_LIBS = \
	Adafruit_BusIO Adafruit_GFX_Library MCUFRIEND_kbv MCUFRIEND_kbv/utility \
	Wire SPI

# Custom libs
CUS_GRAPHICS_ARCHIVE = build-\$(BOARD_TAG)/libcus_graphics.a

CFLAGS += -I\$(PROJECT_DIR)/lib/CUS_graphics
CXXFLAGS += -I\$(PROJECT_DIR)/lib/CUS_graphics
OTHER_OBJS = lib/CUS_graphics/\$(CUS_GRAPHICS_ARCHIVE)



### path to Arduino.mk, inside the ARDMK_DIR, don't touch.
#                              #
include \$(ARDMK_DIR)/Arduino.mk
#                              #
################################


CUS_graphics/\$(CUS_GRAPHICS_ARCHIVE):
	\$(MAKE) -C lib/CUS_graphics \$(CUS_GRAPHICS_ARCHIVE)

clean::
	\$(MAKE) -C lib/CUS_graphics clean
EOL

echo ${Leka-Arduino-Makefile}
chmod a-w Makefile
zsh
'';
}

