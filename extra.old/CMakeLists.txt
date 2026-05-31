# EFM32 extralib CMake file
project(extra)

#find ./src -name '*.c' | sort -u

AUX_SOURCE_DIRECTORY(./src SOURCE_FILES)
add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC 
		inc
		rail
		${BASE_LOCATION}/cmsis/Include
		${BASE_LOCATION}/emlib/inc
		${BASE_LOCATION}/hardware/kit/common/drivers/
		${BASE_LOCATION}/hardware/kit/${CPU_FAMILY_U}_${BOARD}/config/
		${BASE_LOCATION}/hardware/kit/common/bsp/
		${BASE_LOCATION}/device/${CPU_FAMILY_U}/Include)
