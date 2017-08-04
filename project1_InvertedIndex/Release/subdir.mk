################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chkgets.c \
../dictionary.c \
../document.c \
../main.c \
../word.c 

OBJS += \
./chkgets.o \
./dictionary.o \
./document.o \
./main.o \
./word.o 

C_DEPS += \
./chkgets.d \
./dictionary.d \
./document.d \
./main.d \
./word.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


