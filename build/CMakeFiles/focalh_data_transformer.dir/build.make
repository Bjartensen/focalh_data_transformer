# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bjartur/workspace/focalh_data_transformer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bjartur/workspace/focalh_data_transformer/build

# Include any dependencies generated for this target.
include CMakeFiles/focalh_data_transformer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/focalh_data_transformer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/focalh_data_transformer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/focalh_data_transformer.dir/flags.make

CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o: CMakeFiles/focalh_data_transformer.dir/flags.make
CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o: /home/bjartur/workspace/focalh_data_transformer/src/focal_sim_reader.cxx
CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o: CMakeFiles/focalh_data_transformer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bjartur/workspace/focalh_data_transformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o -MF CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o.d -o CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o -c /home/bjartur/workspace/focalh_data_transformer/src/focal_sim_reader.cxx

CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bjartur/workspace/focalh_data_transformer/src/focal_sim_reader.cxx > CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.i

CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bjartur/workspace/focalh_data_transformer/src/focal_sim_reader.cxx -o CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.s

CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o: CMakeFiles/focalh_data_transformer.dir/flags.make
CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o: /home/bjartur/workspace/focalh_data_transformer/src/superimpose_events.cxx
CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o: CMakeFiles/focalh_data_transformer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bjartur/workspace/focalh_data_transformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o -MF CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o.d -o CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o -c /home/bjartur/workspace/focalh_data_transformer/src/superimpose_events.cxx

CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bjartur/workspace/focalh_data_transformer/src/superimpose_events.cxx > CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.i

CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bjartur/workspace/focalh_data_transformer/src/superimpose_events.cxx -o CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.s

# Object files for target focalh_data_transformer
focalh_data_transformer_OBJECTS = \
"CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o" \
"CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o"

# External object files for target focalh_data_transformer
focalh_data_transformer_EXTERNAL_OBJECTS =

libfocalh_data_transformer.so: CMakeFiles/focalh_data_transformer.dir/src/focal_sim_reader.cxx.o
libfocalh_data_transformer.so: CMakeFiles/focalh_data_transformer.dir/src/superimpose_events.cxx.o
libfocalh_data_transformer.so: CMakeFiles/focalh_data_transformer.dir/build.make
libfocalh_data_transformer.so: /opt/sw/inst/lib/libTree.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libMathCore.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libImt.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libMultiProc.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libNet.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libRIO.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libThread.so
libfocalh_data_transformer.so: /opt/sw/inst/lib/libCore.so
libfocalh_data_transformer.so: CMakeFiles/focalh_data_transformer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/bjartur/workspace/focalh_data_transformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libfocalh_data_transformer.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/focalh_data_transformer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/focalh_data_transformer.dir/build: libfocalh_data_transformer.so
.PHONY : CMakeFiles/focalh_data_transformer.dir/build

CMakeFiles/focalh_data_transformer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/focalh_data_transformer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/focalh_data_transformer.dir/clean

CMakeFiles/focalh_data_transformer.dir/depend:
	cd /home/bjartur/workspace/focalh_data_transformer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bjartur/workspace/focalh_data_transformer /home/bjartur/workspace/focalh_data_transformer /home/bjartur/workspace/focalh_data_transformer/build /home/bjartur/workspace/focalh_data_transformer/build /home/bjartur/workspace/focalh_data_transformer/build/CMakeFiles/focalh_data_transformer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/focalh_data_transformer.dir/depend

