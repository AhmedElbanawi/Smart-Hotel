################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../CO_SCH.c \
../DIO.c \
../DIO_CFG.c \
../DISP.c \
../ECU_OD.c \
../ECU_RM.c \
../KEYPAD.c \
../LCD.c \
../SPI.c \
../TMP_SENSOR.c \
../TMR0.c \
../WDT.c \
../main.c 

OBJS += \
./ADC.o \
./CO_SCH.o \
./DIO.o \
./DIO_CFG.o \
./DISP.o \
./ECU_OD.o \
./ECU_RM.o \
./KEYPAD.o \
./LCD.o \
./SPI.o \
./TMP_SENSOR.o \
./TMR0.o \
./WDT.o \
./main.o 

C_DEPS += \
./ADC.d \
./CO_SCH.d \
./DIO.d \
./DIO_CFG.d \
./DISP.d \
./ECU_OD.d \
./ECU_RM.d \
./KEYPAD.d \
./LCD.d \
./SPI.d \
./TMP_SENSOR.d \
./TMR0.d \
./WDT.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


