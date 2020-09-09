################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CIEventAction.cpp \
../src/CIEventActionMessenger.cpp \
../src/CIGenericHit.cpp \
../src/CIMaterials.cpp \
../src/CIModuleTable.cpp \
../src/CIOpticalPhotonHit.cpp \
../src/CIPhotoDetector.cpp \
../src/CIPhysicsList.cpp \
../src/CIPhysicsListMessenger.cpp \
../src/CIPrimaryGeneratorAction.cpp \
../src/CIPrimaryGeneratorMessenger.cpp \
../src/CIRunAction.cpp \
../src/CIRunActionMessenger.cpp \
../src/CIScintiHit.cpp \
../src/CISensitiveOpticalDetector.cpp \
../src/CISensitiveScintiDetector.cpp \
../src/SenSL60035SiPMArray.cpp \
../src/CISteppingAction.cpp \
../src/CISteppingVerbose.cpp \
../src/CellVolume.cpp \
../src/FullDetectorConstruction.cpp \
../src/FullDetectorConstructionMessenger.cpp \
../src/SimpleScintillator.cpp \
../src/CsSourceCapsule.cpp \
../src/CISensitiveMaterials.cpp \
../src/CIMaterialHit.cpp 

INCFLAGS := -I/home/mccann/local/geant4.10.01.p02-install/include/Geant4/

CC_SRCS += \

OBJS += \
./src/CIEventAction.o \
./src/CIEventActionMessenger.o \
./src/CIGenericHit.o \
./src/CIMaterials.o \
./src/CIModuleTable.o \
./src/CIOpticalPhotonHit.o \
./src/CIPhotoDetector.o \
./src/CIPhysicsList.o \
./src/CIPhysicsListMessenger.o \
./src/CIPrimaryGeneratorAction.o \
./src/CIPrimaryGeneratorMessenger.o \
./src/CIRunAction.o \
./src/CIRunActionMessenger.o \
./src/CIScintiHit.o \
./src/CISensitiveOpticalDetector.o \
./src/CISensitiveScintiDetector.o \
./src/SenSL60035SiPMArray.o \
./src/CISteppingAction.o \
./src/CISteppingVerbose.o \
./src/CellVolume.o \
./src/FullDetectorConstruction.o \
./src/FullDetectorConstructionMessenger.o \
./src/SimpleScintillator.o \
./src/CsSourceCapsule.o \
./src/CISensitiveMaterials.o \
./src/CIMaterialHit.o 

CC_DEPS += \

CPP_DEPS += \
./src/CIEventAction.d \
./src/CIEventActionMessenger.d \
./src/CIGenericHit.d \
./src/CIMaterials.d \
./src/CIModuleTable.d \
./src/CIOpticalPhotonHit.d \
./src/CIPhotoDetector.d \
./src/CIPhysicsList.d \
./src/CIPhysicsListMessenger.d \
./src/CIPrimaryGeneratorAction.d \
./src/CIPrimaryGeneratorMessenger.d \
./src/CIRunAction.d \
./src/CIRunActionMessenger.d \
./src/CIScintiHit.d \
./src/CISensitiveOpticalDetector.d \
./src/CISensitiveScintiDetector.d \
./src/SenSL60035SiPMArray.d \
./src/CISteppingAction.d \
./src/CISteppingVerbose.d \
./src/CellVolume.d \
./src/FullDetectorConstruction.d \
./src/FullDetectorConstructionMessenger.d \
./src/SimpleScintillator.d \
./src/CsSourceCapsule.d \
./src/CISensitiveMaterials.d \
./src/CIMaterialHit.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DG4ANALYSIS_USE -DMPICH_IGNORE_CXX_SEEK -Wunused-variable -I../include ${INCFLAGS} -I${ROOTSYS}/include  -I${G4INCLUDE} -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DG4ANALYSIS_USE -DMPICH_IGNORE_CXX_SEEK -Wunused-variable -I../include ${INCFLAGS} -I${ROOTSYS}/include  -I${G4INCLUDE} -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


