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

# Utility rule file for d.

# Include the progress variables for this target.
include CMakeFiles/d.dir/progress.make

CMakeFiles/d: i2c_test
	/Users/mybays/develop/efr32/toolchains/gnu_arm/7.2_2017q4/bin/arm-none-eabi-gdb -command /Users/mybays/develop/efr32/efr32_proj/toolchain/remote.gdbconf /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/i2c_test

d : CMakeFiles/d
d : CMakeFiles/d.dir/build.make

.PHONY : d

# Rule to build all files generated by this target.
CMakeFiles/d.dir/build: d

.PHONY : CMakeFiles/d.dir/build

CMakeFiles/d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/d.dir/clean

CMakeFiles/d.dir/depend:
	cd /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mybays/develop/efr32/efr32_proj/i2c_test /Users/mybays/develop/efr32/efr32_proj/i2c_test /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug /Users/mybays/develop/efr32/efr32_proj/i2c_test/cmake-build-debug/CMakeFiles/d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/d.dir/depend

