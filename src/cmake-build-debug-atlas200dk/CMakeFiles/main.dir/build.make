# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/pc/software/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/pc/software/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/test_main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/test_main.cpp.o: ../test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/test_main.cpp.o"
	/usr/bin/aarch64-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/test_main.cpp.o -c /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/test_main.cpp

CMakeFiles/main.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/test_main.cpp.i"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/test_main.cpp > CMakeFiles/main.dir/test_main.cpp.i

CMakeFiles/main.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/test_main.cpp.s"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/test_main.cpp -o CMakeFiles/main.dir/test_main.cpp.s

CMakeFiles/main.dir/Main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/Main.cpp.o"
	/usr/bin/aarch64-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/Main.cpp.o -c /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/Main.cpp

CMakeFiles/main.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/Main.cpp.i"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/Main.cpp > CMakeFiles/main.dir/Main.cpp.i

CMakeFiles/main.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/Main.cpp.s"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/Main.cpp -o CMakeFiles/main.dir/Main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/test_main.cpp.o" \
"CMakeFiles/main.dir/Main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/outputs/main: CMakeFiles/main.dir/test_main.cpp.o
/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/outputs/main: CMakeFiles/main.dir/Main.cpp.o
/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/outputs/main: CMakeFiles/main.dir/build.make
/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/outputs/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/outputs/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/outputs/main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk /home/pc/work/code_view/whayer_work/sample-objectdetectionbyyolov3/src/cmake-build-debug-atlas200dk/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

