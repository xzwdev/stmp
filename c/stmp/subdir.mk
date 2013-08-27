################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./stmp/stmp.c \
./stmp/stmpdec.c \
./stmp/stmpenc.c 

OBJS += \
./stmp/stmp.o \
./stmp/stmpdec.o \
./stmp/stmpenc.o 

C_DEPS += \
./stmp/stmp.d \
./stmp/stmpdec.d \
./stmp/stmpenc.d 


# Each subdirectory must supply rules for building sources it contributes
stmp/%.o: ./stmp/%.c
	gcc -DLINUX -D__LIBMISC__ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"


