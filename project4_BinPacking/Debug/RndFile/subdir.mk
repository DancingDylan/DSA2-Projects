################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RndFile/fileIO.c \
../RndFile/rndgen.c 

OBJS += \
./RndFile/fileIO.o \
./RndFile/rndgen.o 

C_DEPS += \
./RndFile/fileIO.d \
./RndFile/rndgen.d 


# Each subdirectory must supply rules for building sources it contributes
RndFile/%.o: ../RndFile/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


