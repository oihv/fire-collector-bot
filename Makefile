# Makefile for proj1

# Compiler and tools
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Project name
PROJECT = proj1

# Target MCU and flags
MCU = -mcpu=cortex-m3 -mthumb
CFLAGS = $(MCU) -g -O2 -Wall -DSTM32F10X_M -DUSE_STDPERIPH_DRIVER
LDFLAGS = $(MCU) -Tstm32f103c6.ld

# Include directories
INCLUDES = -I./CMSIS -I./Lib/inc -I./Startup -I./User -I./Hardware

# Source files
SRCS = \
    ./CMSIS/core_cm3.c \
    ./CMSIS/system_stm32f10x.c \
    ./Lib/src/misc.c \
    ./Lib/src/stm32f10x_adc.c \
    ./Lib/src/stm32f10x_bkp.c \
    ./Lib/src/stm32f10x_can.c \
    ./Lib/src/stm32f10x_cec.c \
    ./Lib/src/stm32f10x_crc.c \
    ./Lib/src/stm32f10x_dac.c \
    ./Lib/src/stm32f10x_dbgmcu.c \
    ./Lib/src/stm32f10x_dma.c \
    ./Lib/src/stm32f10x_exti.c \
    ./Lib/src/stm32f10x_flash.c \
    ./Lib/src/stm32f10x_fsmc.c \
    ./Lib/src/stm32f10x_gpio.c \
    ./Lib/src/stm32f10x_i2c.c \
    ./Lib/src/stm32f10x_iwdg.c \
    ./Lib/src/stm32f10x_pwr.c \
    ./Lib/src/stm32f10x_rcc.c \
    ./Lib/src/stm32f10x_rtc.c \
    ./Lib/src/stm32f10x_sdio.c \
    ./Lib/src/stm32f10x_spi.c \
    ./Lib/src/stm32f10x_tim.c \
    ./Lib/src/stm32f10x_usart.c \
    ./Lib/src/stm32f10x_wwdg.c \
    ./Startup/startup_stm32f10x_md.s \
    ./User/main.c \
    ./User/stm32f10x_it.c \
    ./Hardware/Bsp.c \
    ./Hardware/sys.c \
    ./Hardware/Motor.c \
    ./Hardware/CH452.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output files
ELF = $(PROJECT).elf
HEX = $(PROJECT).hex

# Rules
all: $(HEX)

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: %.s
	$(CC) $(CFLAGS) -c -o $@ $<

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f $(OBJS) $(ELF) $(HEX)

.PHONY: all clean
