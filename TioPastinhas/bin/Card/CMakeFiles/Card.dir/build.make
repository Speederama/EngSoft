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
CMAKE_SOURCE_DIR = /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin

# Include any dependencies generated for this target.
include Card/CMakeFiles/Card.dir/depend.make

# Include the progress variables for this target.
include Card/CMakeFiles/Card.dir/progress.make

# Include the compile flags for this target's objects.
include Card/CMakeFiles/Card.dir/flags.make

Card/CMakeFiles/Card.dir/Card.cc.o: Card/CMakeFiles/Card.dir/flags.make
Card/CMakeFiles/Card.dir/Card.cc.o: /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src/Card/Card.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Card/CMakeFiles/Card.dir/Card.cc.o"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Card.dir/Card.cc.o -c /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src/Card/Card.cc

Card/CMakeFiles/Card.dir/Card.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Card.dir/Card.cc.i"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src/Card/Card.cc > CMakeFiles/Card.dir/Card.cc.i

Card/CMakeFiles/Card.dir/Card.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Card.dir/Card.cc.s"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src/Card/Card.cc -o CMakeFiles/Card.dir/Card.cc.s

Card/CMakeFiles/Card.dir/Card.cc.o.requires:
.PHONY : Card/CMakeFiles/Card.dir/Card.cc.o.requires

Card/CMakeFiles/Card.dir/Card.cc.o.provides: Card/CMakeFiles/Card.dir/Card.cc.o.requires
	$(MAKE) -f Card/CMakeFiles/Card.dir/build.make Card/CMakeFiles/Card.dir/Card.cc.o.provides.build
.PHONY : Card/CMakeFiles/Card.dir/Card.cc.o.provides

Card/CMakeFiles/Card.dir/Card.cc.o.provides.build: Card/CMakeFiles/Card.dir/Card.cc.o

# Object files for target Card
Card_OBJECTS = \
"CMakeFiles/Card.dir/Card.cc.o"

# External object files for target Card
Card_EXTERNAL_OBJECTS =

Card/libCard.a: Card/CMakeFiles/Card.dir/Card.cc.o
Card/libCard.a: Card/CMakeFiles/Card.dir/build.make
Card/libCard.a: Card/CMakeFiles/Card.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libCard.a"
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card && $(CMAKE_COMMAND) -P CMakeFiles/Card.dir/cmake_clean_target.cmake
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Card.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Card/CMakeFiles/Card.dir/build: Card/libCard.a
.PHONY : Card/CMakeFiles/Card.dir/build

Card/CMakeFiles/Card.dir/requires: Card/CMakeFiles/Card.dir/Card.cc.o.requires
.PHONY : Card/CMakeFiles/Card.dir/requires

Card/CMakeFiles/Card.dir/clean:
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card && $(CMAKE_COMMAND) -P CMakeFiles/Card.dir/cmake_clean.cmake
.PHONY : Card/CMakeFiles/Card.dir/clean

Card/CMakeFiles/Card.dir/depend:
	cd /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/src/Card /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card /home/rubens/UFMG/Grad/8/SE/EngSoft/TioPastinhas/bin/Card/CMakeFiles/Card.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Card/CMakeFiles/Card.dir/depend

