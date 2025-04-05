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
set(MCU_FLAGS "-mcpu=cortex-m3 -mthumb -DSTM32F10X_M -DUSE_STDPERIPH_DRIVER")
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103C6.ld")

# Compiler flags
set(CMAKE_C_FLAGS "${MCU_FLAGS} -O2 -Wall")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -O2 -Wall")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS}")

# Linker flags
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
    CMSIS/core_cm3.c
    CMSIS/system_stm32f10x.c
    Lib/src/misc.c
    Lib/src/stm32f10x_adc.c
    Lib/src/stm32f10x_bkp.c
    User/main.c
    User/stm32f10x_it.c
    Hardware/Bsp.c
    Hardware/sys.c
    Hardware/Motor.c
    Hardware/CH452.c
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
