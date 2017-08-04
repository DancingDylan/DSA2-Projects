################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../calculations.c \
../customer.c \
../fifoqueue.c \
../main.c \
../prioqueue.c \
../server.c 

OBJS += \
./calculations.o \
./customer.o \
./fifoqueue.o \
./main.o \
./prioqueue.o \
./server.o 

C_DEPS += \
./calculations.d \
./customer.d \
./fifoqueue.d \
./main.d \
./prioqueue.d \
./server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


