#!/usr/bin/env bash

SKETCH_NAME='screentest.ino'
PROGRAM_PATH='/home/ryuji/Developer/Projects/ArduinoGLib/screentest'
BUILD_PATH='/tmp/arduino_build_424625'

ARD_BIN='/nix/store/zyvnpr4hwr67lhv4wm5brrh9mc7z062b-arduino-1.8.19/share/arduino'
ARD_LIB='/home/ryuji/Arduino/libraries'

AVR_PATH="${ARD_BIN}/hardware/tools/avr"
AVR_BIN="${AVR_PATH}/bin"
HARDW_AVR="${ARD_BIN}/hardware/arduino/avr"

GCC_FLAGS='-c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR'
GPP_FLAGS='-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR'
AVR_GPP_FLAGS='-c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR'

BUILDER_FLAGS="-logger=machine -hardware ${ARD_BIN}/hardware -tools ${ARD_BIN}/tools-builder -tools ${AVR_PATH} -built-in-libraries ${ARD_BIN}/libraries -libraries ${ARD_LIB} -fqbn=arduino:avr:uno -vid-pid=2341_0043 -ide-version=10819 -build-path ${BUILD_PATH} -warnings=all -build-cache /tmp/arduino_cache_614865 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avr-gcc.path=${AVR_PATH} -prefs=runtime.tools.avr-gcc-7.3.0-atmel3.6.1-arduino7.path=${AVR_PATH} -prefs=runtime.tools.avrdude.path=${AVR_PATH} -prefs=runtime.tools.avrdude-6.3.0-arduino17.path=${AVR_PATH} -prefs=runtime.tools.arduinoOTA.path=${AVR_PATH} -prefs=runtime.tools.arduinoOTA-1.3.0.path=${AVR_PATH} -verbose ${PROGRAM_PATH}/${SKETCH_NAME}"
${ARD_BIN}/arduino-builder -dump-prefs ${BUILDER_FLAGS}
${ARD_BIN}/arduino-builder -compile    ${BUILDER_FLAGS}

echo 'Detecting libraries used...'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o /dev/null

echo '-> [MCUFRIEND_kbv@3.0.0-Release]'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o /dev/null

echo '-> [Adafruit_GFX_Library@1.11.10]'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o /dev/null

echo '-> [Adafruit_BusIO@1.16.1]'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o /dev/null

echo '-> [Wire@1.0]'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o /dev/null

echo '-> [SPI@1.0]'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src -I${ARD_LIB}/MCUFRIEND_kbv/utility ${ARD_LIB}/MCUFRIEND_kbv/MCUFRIEND_kbv.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/Adafruit_GFX.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/Adafruit_GrayOLED.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/Adafruit_SPITFT.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/glcdfont.c -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_BusIO/Adafruit_BusIO_Register.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_BusIO/Adafruit_I2CDevice.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_BusIO/Adafruit_SPIDevice.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${HARDW_AVR}/libraries/Wire/src/Wire.cpp -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${HARDW_AVR}/libraries/Wire/src/utility/twi.c -o /dev/null
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${HARDW_AVR}/libraries/SPI/src/SPI.cpp -o /dev/null

echo 'Generating function prototypes...'
${AVR_BIN}/avr-g++ ${GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o ${BUILD_PATH}/preproc/ctags_target_for_gcc_minus_e.cpp
${ARD_BIN}/tools-builder/ctags/5.8-arduino11/ctags -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives ${BUILD_PATH}/preproc/ctags_target_for_gcc_minus_e.cpp

echo 'Compiling sketch...'
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp -o ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp.o

echo 'Compiling libraries...'

echo '-> "MCUFRIEND_kbv"'
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src -I${ARD_LIB}/MCUFRIEND_kbv/utility ${ARD_LIB}/MCUFRIEND_kbv/MCUFRIEND_kbv.cpp -o ${BUILD_PATH}/libraries/MCUFRIEND_kbv/MCUFRIEND_kbv.cpp.o

echo '-> "Adafruit_GFX_Library"'
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/glcdfont.c -o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/glcdfont.c.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/Adafruit_GrayOLED.cpp -o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/Adafruit_GrayOLED.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/Adafruit_GFX.cpp -o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/Adafruit_GFX.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_GFX_Library/Adafruit_SPITFT.cpp -o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/Adafruit_SPITFT.cpp.o

echo '-> "Adafruit_BusIO"'
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_BusIO/Adafruit_BusIO_Register.cpp -o ${BUILD_PATH}/libraries/Adafruit_BusIO/Adafruit_BusIO_Register.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_BusIO/Adafruit_I2CDevice.cpp -o ${BUILD_PATH}/libraries/Adafruit_BusIO/Adafruit_I2CDevice.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${ARD_LIB}/Adafruit_BusIO/Adafruit_SPIDevice.cpp -o ${BUILD_PATH}/libraries/Adafruit_BusIO/Adafruit_SPIDevice.cpp.o

echo '-> "Wire"'
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${HARDW_AVR}/libraries/Wire/src/Wire.cpp -o ${BUILD_PATH}/libraries/Wire/Wire.cpp.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${HARDW_AVR}/libraries/Wire/src/utility/twi.c -o ${BUILD_PATH}/libraries/Wire/utility/twi.c.o

echo '-> "SPI"'
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard -I${ARD_LIB}/MCUFRIEND_kbv -I${ARD_LIB}/Adafruit_GFX_Library -I${ARD_LIB}/Adafruit_BusIO -I${HARDW_AVR}/libraries/Wire/src -I${HARDW_AVR}/libraries/SPI/src ${HARDW_AVR}/libraries/SPI/src/SPI.cpp -o ${BUILD_PATH}/libraries/SPI/SPI.cpp.o

echo 'Compiling core...'
${AVR_BIN}/avr-gcc -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10819 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/wiring_pulse.S -o ${BUILD_PATH}/core/wiring_pulse.S.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/hooks.c -o ${BUILD_PATH}/core/hooks.c.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/WInterrupts.c -o ${BUILD_PATH}/core/WInterrupts.c.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/wiring.c -o ${BUILD_PATH}/core/wiring.c.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/wiring_analog.c -o ${BUILD_PATH}/core/wiring_analog.c.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/wiring_pulse.c -o ${BUILD_PATH}/core/wiring_pulse.c.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/wiring_digital.c -o ${BUILD_PATH}/core/wiring_digital.c.o
${AVR_BIN}/avr-gcc ${GCC_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/wiring_shift.c -o ${BUILD_PATH}/core/wiring_shift.c.o

${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/CDC.cpp -o ${BUILD_PATH}/core/CDC.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/HardwareSerial.cpp -o ${BUILD_PATH}/core/HardwareSerial.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/HardwareSerial0.cpp -o ${BUILD_PATH}/core/HardwareSerial0.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/HardwareSerial1.cpp -o ${BUILD_PATH}/core/HardwareSerial1.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/HardwareSerial2.cpp -o ${BUILD_PATH}/core/HardwareSerial2.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/HardwareSerial3.cpp -o ${BUILD_PATH}/core/HardwareSerial3.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/IPAddress.cpp -o ${BUILD_PATH}/core/IPAddress.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/PluggableUSB.cpp -o ${BUILD_PATH}/core/PluggableUSB.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/Print.cpp -o ${BUILD_PATH}/core/Print.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/Stream.cpp -o ${BUILD_PATH}/core/Stream.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/Tone.cpp -o ${BUILD_PATH}/core/Tone.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/USBCore.cpp -o ${BUILD_PATH}/core/USBCore.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/WMath.cpp -o ${BUILD_PATH}/core/WMath.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/WString.cpp -o ${BUILD_PATH}/core/WString.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/abi.cpp -o ${BUILD_PATH}/core/abi.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/main.cpp -o ${BUILD_PATH}/core/main.cpp.o
${AVR_BIN}/avr-g++ ${AVR_GPP_FLAGS} -I${HARDW_AVR}/cores/arduino -I${HARDW_AVR}/variants/standard ${HARDW_AVR}/cores/arduino/new.cpp -o ${BUILD_PATH}/core/new.cpp.o

${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/wiring_pulse.S.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/WInterrupts.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/hooks.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/wiring.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/wiring_analog.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/wiring_digital.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/wiring_pulse.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/wiring_shift.c.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/CDC.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/HardwareSerial.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/HardwareSerial0.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/HardwareSerial1.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/HardwareSerial2.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/HardwareSerial3.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/IPAddress.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/PluggableUSB.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/Print.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/Stream.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/Tone.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/USBCore.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/WMath.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/WString.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/abi.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/main.cpp.o
${AVR_BIN}/avr-gcc-ar rcs ${BUILD_PATH}/core/core.a ${BUILD_PATH}/core/new.cpp.o

echo 'Linking everything together...'
${AVR_BIN}/avr-gcc -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o ${BUILD_PATH}/${SKETCH_NAME}.elf ${BUILD_PATH}/sketch/${SKETCH_NAME}.cpp.o ${BUILD_PATH}/libraries/MCUFRIEND_kbv/MCUFRIEND_kbv.cpp.o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/glcdfont.c.o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/Adafruit_GFX.cpp.o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/Adafruit_GrayOLED.cpp.o ${BUILD_PATH}/libraries/Adafruit_GFX_Library/Adafruit_SPITFT.cpp.o ${BUILD_PATH}/libraries/Adafruit_BusIO/Adafruit_BusIO_Register.cpp.o ${BUILD_PATH}/libraries/Adafruit_BusIO/Adafruit_I2CDevice.cpp.o ${BUILD_PATH}/libraries/Adafruit_BusIO/Adafruit_SPIDevice.cpp.o ${BUILD_PATH}/libraries/Wire/Wire.cpp.o ${BUILD_PATH}/libraries/Wire/utility/twi.c.o ${BUILD_PATH}/libraries/SPI/SPI.cpp.o ${BUILD_PATH}/core/core.a -L${BUILD_PATH} -lm
${AVR_BIN}/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 ${BUILD_PATH}/${SKETCH_NAME}.elf ${BUILD_PATH}/${SKETCH_NAME}.eep
${AVR_BIN}/avr-objcopy -O ihex -R .eeprom ${BUILD_PATH}/${SKETCH_NAME}.elf ${BUILD_PATH}/${SKETCH_NAME}.hex
${AVR_BIN}/avr-size -A ${BUILD_PATH}/${SKETCH_NAME}.elf

echo 'Flashing...'
${AVR_BIN}/avrdude -C${AVR_PATH}/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:${BUILD_PATH}/${SKETCH_NAME}.hex:i
