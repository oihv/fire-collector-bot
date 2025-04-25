cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(proj1 C CXX ASM)

# Set the target MCU and toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Cortex-M3)

# Specify the compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

# Set the target properties
# Flags for C/C++/Assembly compilation steps (defines, architecture)
set(COMMON_FLAGS "-g -mcpu=cortex-m3 -mthumb")

# Flags specifically for C/C++ preprocessor (defines)
set(PREPROCESSOR_DEFINES "-DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER")

# Compiler flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS} ${PREPROCESSOR_DEFINES} -O2 -Wall")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${PREPROCESSOR_DEFINES} -O2 -Wall")

# Assembly flags - ONLY include architecture flags, NOT preprocessor defines for .s files
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS}") # <-- Corrected line

# Linker flags (already looked good)
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/stm32f103c6tx_flash.ld")
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map")
# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/CMSIS
    ${CMAKE_SOURCE_DIR}/Lib/inc
    ${CMAKE_SOURCE_DIR}/Startup
    ${CMAKE_SOURCE_DIR}/User
    ${CMAKE_SOURCE_DIR}/Hardware
    /usr/lib/gcc/arm-none-eabi/14.2.0/include
    /usr/arm-none-eabi/include
)

# Source files
set(SOURCES
    CMSIS/core_cm3_linux.c
    CMSIS/system_stm32f10x.c
    Lib/src/misc.c
    Lib/src/stm32f10x_adc.c
    Lib/src/stm32f10x_bkp.c
    Lib/src/stm32f10x_can.c
    Lib/src/stm32f10x_cec.c
    Lib/src/stm32f10x_crc.c
    Lib/src/stm32f10x_dac.c
    Lib/src/stm32f10x_dbgmcu.c
    Lib/src/stm32f10x_dma.c
    Lib/src/stm32f10x_exti.c
    Lib/src/stm32f10x_flash.c
    Lib/src/stm32f10x_fsmc.c
    Lib/src/stm32f10x_gpio.c
    Lib/src/stm32f10x_i2c.c
    Lib/src/stm32f10x_iwdg.c
    Lib/src/stm32f10x_pwr.c
    Lib/src/stm32f10x_rcc.c
    Lib/src/stm32f10x_rtc.c
    Lib/src/stm32f10x_sdio.c
    Lib/src/stm32f10x_spi.c
    Lib/src/stm32f10x_tim.c
    Lib/src/stm32f10x_usart.c
    Lib/src/stm32f10x_wwdg.c
    User/main.c
    User/movement.c
    User/algo.c
    User/stm32f10x_it.c
    User/utils.c
    Hardware/Bsp.c
    Hardware/CH452.c
    Hardware/Motor.c
    Hardware/pid.c
    Hardware/sys.c
    Startup/startup_stm32f103x6.s
)

# Add executable target
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Optional: Generate HEX and BIN files
add_custom_target(${PROJECT_NAME}.hex ALL
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}.elf
)

add_custom_target(${PROJECT_NAME}.bin ALL
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}.elf
)
