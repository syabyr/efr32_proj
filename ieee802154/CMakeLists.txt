# Base EFM32 CMake file
#
# This can be used as is as a project base, or by adding the efm32-base
# repository as a submodule to another project, copying this CMakeLists file
# to the top level directory, and updating the BASE_LOCATION variable to reflect this
# change
#
## Copyright (c) 2016 Ryan Kurte
# This file is covered under the MIT license available at: https://opensource.org/licenses/MIT

###### Project Environment #####

# Set minimum CMake version
cmake_minimum_required(VERSION 2.8.4)

#set(COMPILER_PREFIX /Users/mybays/develop/efr32/toolchains/gnu_arm/7.2_2017q4/bin/)

if(NOT COMPILER_PREFIX)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_AR arm-none-eabi-ar)
else ()
    set(CMAKE_C_${COMPILER_PREFIX}/COMPILER arm-none-eabi-gcc)
    set(CMAKE_AR ${COMPILER_PREFIX}/arm-none-eabi-ar)
endif ()


# Optional verbose mode, uncomment or pass in -DCMAKE_VERBOSE_MAKEFILE=ON
set(CMAKE_VERBOSE_MAKEFILE ON)

set(BASE_LOCATION ../../efr32_base)
message ( STATUS "BASE_LOCATION = ${BASE_LOCATION}.")

set(BOARD TRADFRI)

# Set device
if (BOARD STREQUAL "TRADFRI" )
    set(DEVICE "EFR32MG1P132F256IM32")
    set(JLINK_TYPE "EFR32MG1PXXXF256")
elseif (BOARD STREQUAL "TYZS3")
    set(DEVICE "EFR32MG13P732F512GM48")
    set(JLINK_TYPE "EFR32MG13PXXXF512")
elseif (BOARD STREQUAL "ZS3L")
    set(DEVICE "EFR32MG21A010F768IM32")
    set(JLINK_TYPE "EFR32MG21PXXXF768")
else ()
    message("Unknown Board type:${BOARD}")
    exit()
endif ()

message("jlinkdevice: ${JLINK_TYPE}")

# Set the compiler (must be prior to project setup)
include(../toolchain/arm-gcc.cmake)

##### Project Setup #####

# Configure project and languages
project(ieee802154 C CXX ASM)


# Set build
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE DEBUG)
endif ()

##### Modules #####

# Libraries can be added to the LIBS variable
# or manually included here.

# Add base libs (emlib, CMSIS, device files)
include(../toolchain/efm32-base.cmake)

set(WORKING_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${BASE_LOCATION}/cmsis cmsis)
add_subdirectory(${BASE_LOCATION}/emlib emlib)
add_subdirectory(${BASE_LOCATION}/device device)
add_subdirectory(${BASE_LOCATION}/protocol protocol)
add_subdirectory(${BASE_LOCATION}/hardware hardware)
add_subdirectory(../extra extra)

# This is normally set in efm32-base.cmake, but libraries may modify it so set
# it after libraries/subdirectories have been added
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_DEFINITIONS} -Xlinker -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -Wl,-v -u _printf_float")

##### Files #####

# Add project headers
include_directories(${BASE_LOCATION}/include)
include_directories(${BASE_LOCATION}/extra/inc)
include_directories(../extra/rail)

include_directories(./inc)

AUX_SOURCE_DIRECTORY(./ SOURCE_FILES)
AUX_SOURCE_DIRECTORY(./src SOURCE_FILES)


link_directories(../extra/rail/TARGET_EFR32MG1)

# Generate executable and link
add_executable(${PROJECT_NAME} 
	${BASE_LOCATION}/hardware/kit/common/drivers/retargetserial.c
	${BASE_LOCATION}/hardware/kit/common/drivers/retargetio.c
	${SOURCE_FILES})

efm32_configure_linker_addresses(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${LIBS} extra rail_efr32xg1_gcc_release emlib cmsis device)

# Link optional libraries if available
if (${HAS_HARDWARE})
    target_link_libraries(${PROJECT_NAME} hardware)
endif ()

if (${HAS_PROTOCOL})
    target_link_libraries(${PROJECT_NAME} protocol)
endif ()

##### Post build #####

# Add post build commands
include(../toolchain/post-build.cmake)

# Add JLink commands
include(../toolchain/jlink.cmake)

##### CMake debug prints #####
if (CMAKE_VERBOSE_MAKEFILE)
    print_debug_info()
endif()
