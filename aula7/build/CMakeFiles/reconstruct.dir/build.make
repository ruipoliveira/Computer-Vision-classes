# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/roliveira/Documents/CV/aula7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roliveira/Documents/CV/aula7/build

# Include any dependencies generated for this target.
include CMakeFiles/reconstruct.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/reconstruct.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/reconstruct.dir/flags.make

CMakeFiles/reconstruct.dir/reconstruct.cpp.o: CMakeFiles/reconstruct.dir/flags.make
CMakeFiles/reconstruct.dir/reconstruct.cpp.o: ../reconstruct.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roliveira/Documents/CV/aula7/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/reconstruct.dir/reconstruct.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/reconstruct.dir/reconstruct.cpp.o -c /home/roliveira/Documents/CV/aula7/reconstruct.cpp

CMakeFiles/reconstruct.dir/reconstruct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reconstruct.dir/reconstruct.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roliveira/Documents/CV/aula7/reconstruct.cpp > CMakeFiles/reconstruct.dir/reconstruct.cpp.i

CMakeFiles/reconstruct.dir/reconstruct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reconstruct.dir/reconstruct.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roliveira/Documents/CV/aula7/reconstruct.cpp -o CMakeFiles/reconstruct.dir/reconstruct.cpp.s

CMakeFiles/reconstruct.dir/reconstruct.cpp.o.requires:
.PHONY : CMakeFiles/reconstruct.dir/reconstruct.cpp.o.requires

CMakeFiles/reconstruct.dir/reconstruct.cpp.o.provides: CMakeFiles/reconstruct.dir/reconstruct.cpp.o.requires
	$(MAKE) -f CMakeFiles/reconstruct.dir/build.make CMakeFiles/reconstruct.dir/reconstruct.cpp.o.provides.build
.PHONY : CMakeFiles/reconstruct.dir/reconstruct.cpp.o.provides

CMakeFiles/reconstruct.dir/reconstruct.cpp.o.provides.build: CMakeFiles/reconstruct.dir/reconstruct.cpp.o

# Object files for target reconstruct
reconstruct_OBJECTS = \
"CMakeFiles/reconstruct.dir/reconstruct.cpp.o"

# External object files for target reconstruct
reconstruct_EXTERNAL_OBJECTS =

reconstruct: CMakeFiles/reconstruct.dir/reconstruct.cpp.o
reconstruct: CMakeFiles/reconstruct.dir/build.make
reconstruct: /usr/local/lib/libopencv_videostab.so.2.4.13
reconstruct: /usr/local/lib/libopencv_video.so.2.4.13
reconstruct: /usr/local/lib/libopencv_ts.a
reconstruct: /usr/local/lib/libopencv_superres.so.2.4.13
reconstruct: /usr/local/lib/libopencv_stitching.so.2.4.13
reconstruct: /usr/local/lib/libopencv_photo.so.2.4.13
reconstruct: /usr/local/lib/libopencv_ocl.so.2.4.13
reconstruct: /usr/local/lib/libopencv_objdetect.so.2.4.13
reconstruct: /usr/local/lib/libopencv_nonfree.so.2.4.13
reconstruct: /usr/local/lib/libopencv_ml.so.2.4.13
reconstruct: /usr/local/lib/libopencv_legacy.so.2.4.13
reconstruct: /usr/local/lib/libopencv_imgproc.so.2.4.13
reconstruct: /usr/local/lib/libopencv_highgui.so.2.4.13
reconstruct: /usr/local/lib/libopencv_gpu.so.2.4.13
reconstruct: /usr/local/lib/libopencv_flann.so.2.4.13
reconstruct: /usr/local/lib/libopencv_features2d.so.2.4.13
reconstruct: /usr/local/lib/libopencv_core.so.2.4.13
reconstruct: /usr/local/lib/libopencv_contrib.so.2.4.13
reconstruct: /usr/local/lib/libopencv_calib3d.so.2.4.13
reconstruct: /usr/lib/x86_64-linux-gnu/libGLU.so
reconstruct: /usr/lib/x86_64-linux-gnu/libGL.so
reconstruct: /usr/lib/x86_64-linux-gnu/libSM.so
reconstruct: /usr/lib/x86_64-linux-gnu/libICE.so
reconstruct: /usr/lib/x86_64-linux-gnu/libX11.so
reconstruct: /usr/lib/x86_64-linux-gnu/libXext.so
reconstruct: /usr/local/lib/libopencv_nonfree.so.2.4.13
reconstruct: /usr/local/lib/libopencv_ocl.so.2.4.13
reconstruct: /usr/local/lib/libopencv_gpu.so.2.4.13
reconstruct: /usr/local/lib/libopencv_photo.so.2.4.13
reconstruct: /usr/local/lib/libopencv_objdetect.so.2.4.13
reconstruct: /usr/local/lib/libopencv_legacy.so.2.4.13
reconstruct: /usr/local/lib/libopencv_video.so.2.4.13
reconstruct: /usr/local/lib/libopencv_ml.so.2.4.13
reconstruct: /usr/local/lib/libopencv_calib3d.so.2.4.13
reconstruct: /usr/local/lib/libopencv_features2d.so.2.4.13
reconstruct: /usr/local/lib/libopencv_highgui.so.2.4.13
reconstruct: /usr/local/lib/libopencv_imgproc.so.2.4.13
reconstruct: /usr/local/lib/libopencv_flann.so.2.4.13
reconstruct: /usr/local/lib/libopencv_core.so.2.4.13
reconstruct: CMakeFiles/reconstruct.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable reconstruct"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reconstruct.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/reconstruct.dir/build: reconstruct
.PHONY : CMakeFiles/reconstruct.dir/build

CMakeFiles/reconstruct.dir/requires: CMakeFiles/reconstruct.dir/reconstruct.cpp.o.requires
.PHONY : CMakeFiles/reconstruct.dir/requires

CMakeFiles/reconstruct.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/reconstruct.dir/cmake_clean.cmake
.PHONY : CMakeFiles/reconstruct.dir/clean

CMakeFiles/reconstruct.dir/depend:
	cd /home/roliveira/Documents/CV/aula7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roliveira/Documents/CV/aula7 /home/roliveira/Documents/CV/aula7 /home/roliveira/Documents/CV/aula7/build /home/roliveira/Documents/CV/aula7/build /home/roliveira/Documents/CV/aula7/build/CMakeFiles/reconstruct.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/reconstruct.dir/depend
