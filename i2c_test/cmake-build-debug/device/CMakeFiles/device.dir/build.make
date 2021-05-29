# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/mybays/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/mybays/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mybays/develop/efr32/efr32_proj/i2c_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug

# Include any dependencies generated for this target.
include device/CMakeFiles/device.dir/depend.make

# Include the progress variables for this target.
include device/CMakeFiles/device.dir/progress.make

# Include the compile flags for this target's objects.
include device/CMakeFiles/device.dir/flags.make

device/CMakeFiles/device.dir/EFR32MG1P/Source/GCC/startup_efr32mg1p.S.obj: device/CMakeFiles/device.dir/flags.make
device/CMakeFiles/device.dir/EFR32MG1P/Source/GCC/startup_efr32mg1p.S.obj: /Users/mybays/develop/efr32/efr32_base/device/EFR32MG1P/Source/GCC/startup_efr32mg1p.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object device/CMakeFiles/device.dir/EFR32MG1P/Source/GCC/startup_efr32mg1p.S.obj"
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && /Users/mybays/develop/efr32/toolchains/gnu_arm/7.2_2017q4/bin/arm-none-eabi-g++ $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/device.dir/EFR32MG1P/Source/GCC/startup_efr32mg1p.S.obj -c /Users/mybays/develop/efr32/efr32_base/device/EFR32MG1P/Source/GCC/startup_efr32mg1p.S

device/CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.obj: device/CMakeFiles/device.dir/flags.make
device/CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.obj: /Users/mybays/develop/efr32/efr32_base/device/EFR32MG1P/Source/system_efr32mg1p.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object device/CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.obj"
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && /Users/mybays/develop/efr32/toolchains/gnu_arm/7.2_2017q4/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.obj -c /Users/mybays/develop/efr32/efr32_base/device/EFR32MG1P/Source/system_efr32mg1p.c

device/CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.i"
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && /Users/mybays/develop/efr32/toolchains/gnu_arm/7.2_2017q4/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mybays/develop/efr32/efr32_base/device/EFR32MG1P/Source/system_efr32mg1p.c > CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.i

device/CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.s"
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && /Users/mybays/develop/efr32/toolchains/gnu_arm/7.2_2017q4/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mybays/develop/efr32/efr32_base/device/EFR32MG1P/Source/system_efr32mg1p.c -o CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.s

# Object files for target device
device_OBJECTS = \
"CMakeFiles/device.dir/EFR32MG1P/Source/GCC/startup_efr32mg1p.S.obj" \
"CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.obj"

# External object files for target device
device_EXTERNAL_OBJECTS =

device/libdevice.a: device/CMakeFiles/device.dir/EFR32MG1P/Source/GCC/startup_efr32mg1p.S.obj
device/libdevice.a: device/CMakeFiles/device.dir/EFR32MG1P/Source/system_efr32mg1p.c.obj
device/libdevice.a: device/CMakeFiles/device.dir/build.make
device/libdevice.a: device/CMakeFiles/device.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libdevice.a"
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && $(CMAKE_COMMAND) -P CMakeFiles/device.dir/cmake_clean_target.cmake
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/device.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
device/CMakeFiles/device.dir/build: device/libdevice.a

.PHONY : device/CMakeFiles/device.dir/build

device/CMakeFiles/device.dir/clean:
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device && $(CMAKE_COMMAND) -P CMakeFiles/device.dir/cmake_clean.cmake
.PHONY : device/CMakeFiles/device.dir/clean

device/CMakeFiles/device.dir/depend:
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mybays/develop/efr32/efr32_proj/i2c_test /Users/mybays/develop/efr32/efr32_base/device /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/device/CMakeFiles/device.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : device/CMakeFiles/device.dir/depend

