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
include CMakeFiles/viewOpenni.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/viewOpenni.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/viewOpenni.dir/flags.make

CMakeFiles/viewOpenni.dir/pcl_io.cpp.o: CMakeFiles/viewOpenni.dir/flags.make
CMakeFiles/viewOpenni.dir/pcl_io.cpp.o: ../pcl_io.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roliveira/Documents/CV/aula7/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/viewOpenni.dir/pcl_io.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/viewOpenni.dir/pcl_io.cpp.o -c /home/roliveira/Documents/CV/aula7/pcl_io.cpp

CMakeFiles/viewOpenni.dir/pcl_io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewOpenni.dir/pcl_io.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roliveira/Documents/CV/aula7/pcl_io.cpp > CMakeFiles/viewOpenni.dir/pcl_io.cpp.i

CMakeFiles/viewOpenni.dir/pcl_io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewOpenni.dir/pcl_io.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roliveira/Documents/CV/aula7/pcl_io.cpp -o CMakeFiles/viewOpenni.dir/pcl_io.cpp.s

CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.requires:
.PHONY : CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.requires

CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.provides: CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.requires
	$(MAKE) -f CMakeFiles/viewOpenni.dir/build.make CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.provides.build
.PHONY : CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.provides

CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.provides.build: CMakeFiles/viewOpenni.dir/pcl_io.cpp.o

# Object files for target viewOpenni
viewOpenni_OBJECTS = \
"CMakeFiles/viewOpenni.dir/pcl_io.cpp.o"

# External object files for target viewOpenni
viewOpenni_EXTERNAL_OBJECTS =

viewOpenni: CMakeFiles/viewOpenni.dir/pcl_io.cpp.o
viewOpenni: CMakeFiles/viewOpenni.dir/build.make
viewOpenni: /usr/local/lib/libopencv_videostab.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_video.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_ts.a
viewOpenni: /usr/local/lib/libopencv_superres.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_stitching.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_photo.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_ocl.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_objdetect.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_nonfree.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_ml.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_legacy.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_imgproc.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_highgui.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_gpu.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_flann.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_features2d.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_core.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_contrib.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_calib3d.so.2.4.13
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_system.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_thread.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libpthread.so
viewOpenni: /usr/lib/libpcl_common.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
viewOpenni: /usr/lib/libpcl_kdtree.so
viewOpenni: /usr/lib/libpcl_octree.so
viewOpenni: /usr/lib/libpcl_search.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libqhull.so
viewOpenni: /usr/lib/libpcl_surface.so
viewOpenni: /usr/lib/libpcl_sample_consensus.so
viewOpenni: /usr/lib/libOpenNI.so
viewOpenni: /usr/lib/libOpenNI2.so
viewOpenni: /usr/lib/libvtkCommon.so.5.8.0
viewOpenni: /usr/lib/libvtkFiltering.so.5.8.0
viewOpenni: /usr/lib/libvtkImaging.so.5.8.0
viewOpenni: /usr/lib/libvtkGraphics.so.5.8.0
viewOpenni: /usr/lib/libvtkGenericFiltering.so.5.8.0
viewOpenni: /usr/lib/libvtkIO.so.5.8.0
viewOpenni: /usr/lib/libvtkRendering.so.5.8.0
viewOpenni: /usr/lib/libvtkVolumeRendering.so.5.8.0
viewOpenni: /usr/lib/libvtkHybrid.so.5.8.0
viewOpenni: /usr/lib/libvtkWidgets.so.5.8.0
viewOpenni: /usr/lib/libvtkParallel.so.5.8.0
viewOpenni: /usr/lib/libvtkInfovis.so.5.8.0
viewOpenni: /usr/lib/libvtkGeovis.so.5.8.0
viewOpenni: /usr/lib/libvtkViews.so.5.8.0
viewOpenni: /usr/lib/libvtkCharts.so.5.8.0
viewOpenni: /usr/lib/libpcl_io.so
viewOpenni: /usr/lib/libpcl_filters.so
viewOpenni: /usr/lib/libpcl_features.so
viewOpenni: /usr/lib/libpcl_keypoints.so
viewOpenni: /usr/lib/libpcl_registration.so
viewOpenni: /usr/lib/libpcl_segmentation.so
viewOpenni: /usr/lib/libpcl_recognition.so
viewOpenni: /usr/lib/libpcl_visualization.so
viewOpenni: /usr/lib/libpcl_people.so
viewOpenni: /usr/lib/libpcl_outofcore.so
viewOpenni: /usr/lib/libpcl_tracking.so
viewOpenni: /usr/lib/libpcl_apps.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_system.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_thread.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libpthread.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libqhull.so
viewOpenni: /usr/lib/libOpenNI.so
viewOpenni: /usr/lib/libOpenNI2.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
viewOpenni: /usr/lib/libvtkCommon.so.5.8.0
viewOpenni: /usr/lib/libvtkFiltering.so.5.8.0
viewOpenni: /usr/lib/libvtkImaging.so.5.8.0
viewOpenni: /usr/lib/libvtkGraphics.so.5.8.0
viewOpenni: /usr/lib/libvtkGenericFiltering.so.5.8.0
viewOpenni: /usr/lib/libvtkIO.so.5.8.0
viewOpenni: /usr/lib/libvtkRendering.so.5.8.0
viewOpenni: /usr/lib/libvtkVolumeRendering.so.5.8.0
viewOpenni: /usr/lib/libvtkHybrid.so.5.8.0
viewOpenni: /usr/lib/libvtkWidgets.so.5.8.0
viewOpenni: /usr/lib/libvtkParallel.so.5.8.0
viewOpenni: /usr/lib/libvtkInfovis.so.5.8.0
viewOpenni: /usr/lib/libvtkGeovis.so.5.8.0
viewOpenni: /usr/lib/libvtkViews.so.5.8.0
viewOpenni: /usr/lib/libvtkCharts.so.5.8.0
viewOpenni: /usr/lib/x86_64-linux-gnu/libGLU.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libGL.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libSM.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libICE.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libX11.so
viewOpenni: /usr/lib/x86_64-linux-gnu/libXext.so
viewOpenni: /usr/local/lib/libopencv_nonfree.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_ocl.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_gpu.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_photo.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_objdetect.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_legacy.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_video.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_ml.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_calib3d.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_features2d.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_highgui.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_imgproc.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_flann.so.2.4.13
viewOpenni: /usr/local/lib/libopencv_core.so.2.4.13
viewOpenni: /usr/lib/libpcl_common.so
viewOpenni: /usr/lib/libpcl_kdtree.so
viewOpenni: /usr/lib/libpcl_octree.so
viewOpenni: /usr/lib/libpcl_search.so
viewOpenni: /usr/lib/libpcl_surface.so
viewOpenni: /usr/lib/libpcl_sample_consensus.so
viewOpenni: /usr/lib/libpcl_io.so
viewOpenni: /usr/lib/libpcl_filters.so
viewOpenni: /usr/lib/libpcl_features.so
viewOpenni: /usr/lib/libpcl_keypoints.so
viewOpenni: /usr/lib/libpcl_registration.so
viewOpenni: /usr/lib/libpcl_segmentation.so
viewOpenni: /usr/lib/libpcl_recognition.so
viewOpenni: /usr/lib/libpcl_visualization.so
viewOpenni: /usr/lib/libpcl_people.so
viewOpenni: /usr/lib/libpcl_outofcore.so
viewOpenni: /usr/lib/libpcl_tracking.so
viewOpenni: /usr/lib/libpcl_apps.so
viewOpenni: /usr/lib/libvtkViews.so.5.8.0
viewOpenni: /usr/lib/libvtkInfovis.so.5.8.0
viewOpenni: /usr/lib/libvtkWidgets.so.5.8.0
viewOpenni: /usr/lib/libvtkVolumeRendering.so.5.8.0
viewOpenni: /usr/lib/libvtkHybrid.so.5.8.0
viewOpenni: /usr/lib/libvtkParallel.so.5.8.0
viewOpenni: /usr/lib/libvtkRendering.so.5.8.0
viewOpenni: /usr/lib/libvtkImaging.so.5.8.0
viewOpenni: /usr/lib/libvtkGraphics.so.5.8.0
viewOpenni: /usr/lib/libvtkIO.so.5.8.0
viewOpenni: /usr/lib/libvtkFiltering.so.5.8.0
viewOpenni: /usr/lib/libvtkCommon.so.5.8.0
viewOpenni: /usr/lib/libvtksys.so.5.8.0
viewOpenni: CMakeFiles/viewOpenni.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable viewOpenni"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/viewOpenni.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/viewOpenni.dir/build: viewOpenni
.PHONY : CMakeFiles/viewOpenni.dir/build

CMakeFiles/viewOpenni.dir/requires: CMakeFiles/viewOpenni.dir/pcl_io.cpp.o.requires
.PHONY : CMakeFiles/viewOpenni.dir/requires

CMakeFiles/viewOpenni.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/viewOpenni.dir/cmake_clean.cmake
.PHONY : CMakeFiles/viewOpenni.dir/clean

CMakeFiles/viewOpenni.dir/depend:
	cd /home/roliveira/Documents/CV/aula7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roliveira/Documents/CV/aula7 /home/roliveira/Documents/CV/aula7 /home/roliveira/Documents/CV/aula7/build /home/roliveira/Documents/CV/aula7/build /home/roliveira/Documents/CV/aula7/build/CMakeFiles/viewOpenni.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/viewOpenni.dir/depend
