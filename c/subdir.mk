################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./chashstr.c \
./logger.c \
./main.c \
./util.c 

OBJS += \
./chashstr.o \
./logger.o \
./main.o \
./util.o 

C_DEPS += \
./chashstr.d \
./logger.d \
./main.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ./%.c
	gcc -DLINUX -D__LIBMISC__ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"


