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
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin

# Include any dependencies generated for this target.
include Screen/CMakeFiles/Screen.dir/depend.make

# Include the progress variables for this target.
include Screen/CMakeFiles/Screen.dir/progress.make

# Include the compile flags for this target's objects.
include Screen/CMakeFiles/Screen.dir/flags.make

Screen/CMakeFiles/Screen.dir/MainScreen.cc.o: Screen/CMakeFiles/Screen.dir/flags.make
Screen/CMakeFiles/Screen.dir/MainScreen.cc.o: /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src/Screen/MainScreen.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Screen/CMakeFiles/Screen.dir/MainScreen.cc.o"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Screen.dir/MainScreen.cc.o -c /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src/Screen/MainScreen.cc

Screen/CMakeFiles/Screen.dir/MainScreen.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Screen.dir/MainScreen.cc.i"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src/Screen/MainScreen.cc > CMakeFiles/Screen.dir/MainScreen.cc.i

Screen/CMakeFiles/Screen.dir/MainScreen.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Screen.dir/MainScreen.cc.s"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src/Screen/MainScreen.cc -o CMakeFiles/Screen.dir/MainScreen.cc.s

Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.requires:
.PHONY : Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.requires

Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.provides: Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.requires
	$(MAKE) -f Screen/CMakeFiles/Screen.dir/build.make Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.provides.build
.PHONY : Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.provides

Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.provides.build: Screen/CMakeFiles/Screen.dir/MainScreen.cc.o

# Object files for target Screen
Screen_OBJECTS = \
"CMakeFiles/Screen.dir/MainScreen.cc.o"

# External object files for target Screen
Screen_EXTERNAL_OBJECTS =

Screen/libScreen.a: Screen/CMakeFiles/Screen.dir/MainScreen.cc.o
Screen/libScreen.a: Screen/CMakeFiles/Screen.dir/build.make
Screen/libScreen.a: Screen/CMakeFiles/Screen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libScreen.a"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen && $(CMAKE_COMMAND) -P CMakeFiles/Screen.dir/cmake_clean_target.cmake
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Screen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Screen/CMakeFiles/Screen.dir/build: Screen/libScreen.a
.PHONY : Screen/CMakeFiles/Screen.dir/build

Screen/CMakeFiles/Screen.dir/requires: Screen/CMakeFiles/Screen.dir/MainScreen.cc.o.requires
.PHONY : Screen/CMakeFiles/Screen.dir/requires

Screen/CMakeFiles/Screen.dir/clean:
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen && $(CMAKE_COMMAND) -P CMakeFiles/Screen.dir/cmake_clean.cmake
.PHONY : Screen/CMakeFiles/Screen.dir/clean

Screen/CMakeFiles/Screen.dir/depend:
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/src/Screen /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen /home/rubens/UFMG/Grad/8/SE/EngSoft/Pastinhas/bin/Screen/CMakeFiles/Screen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Screen/CMakeFiles/Screen.dir/depend

