################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BioBricks.cpp \
../src/admixture_genome.cpp \
../src/parental_genomes.cpp 

OBJS += \
./src/BioBricks.o \
./src/admixture_genome.o \
./src/parental_genomes.o 

CPP_DEPS += \
./src/BioBricks.d \
./src/admixture_genome.d \
./src/parental_genomes.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


