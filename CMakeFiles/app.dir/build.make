# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/alex/Programming/C_C++/Projects/imgp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Programming/C_C++/Projects/imgp

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/main.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/main.c.o: main.c
CMakeFiles/app.dir/main.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Programming/C_C++/Projects/imgp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/app.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/main.c.o -MF CMakeFiles/app.dir/main.c.o.d -o CMakeFiles/app.dir/main.c.o -c /home/alex/Programming/C_C++/Projects/imgp/main.c

CMakeFiles/app.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Programming/C_C++/Projects/imgp/main.c > CMakeFiles/app.dir/main.c.i

CMakeFiles/app.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Programming/C_C++/Projects/imgp/main.c -o CMakeFiles/app.dir/main.c.s

CMakeFiles/app.dir/imgp_bitmap.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/imgp_bitmap.c.o: imgp_bitmap.c
CMakeFiles/app.dir/imgp_bitmap.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Programming/C_C++/Projects/imgp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/app.dir/imgp_bitmap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/imgp_bitmap.c.o -MF CMakeFiles/app.dir/imgp_bitmap.c.o.d -o CMakeFiles/app.dir/imgp_bitmap.c.o -c /home/alex/Programming/C_C++/Projects/imgp/imgp_bitmap.c

CMakeFiles/app.dir/imgp_bitmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/imgp_bitmap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Programming/C_C++/Projects/imgp/imgp_bitmap.c > CMakeFiles/app.dir/imgp_bitmap.c.i

CMakeFiles/app.dir/imgp_bitmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/imgp_bitmap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Programming/C_C++/Projects/imgp/imgp_bitmap.c -o CMakeFiles/app.dir/imgp_bitmap.c.s

CMakeFiles/app.dir/imgp_utils.c.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/imgp_utils.c.o: imgp_utils.c
CMakeFiles/app.dir/imgp_utils.c.o: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Programming/C_C++/Projects/imgp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/app.dir/imgp_utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/imgp_utils.c.o -MF CMakeFiles/app.dir/imgp_utils.c.o.d -o CMakeFiles/app.dir/imgp_utils.c.o -c /home/alex/Programming/C_C++/Projects/imgp/imgp_utils.c

CMakeFiles/app.dir/imgp_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/imgp_utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Programming/C_C++/Projects/imgp/imgp_utils.c > CMakeFiles/app.dir/imgp_utils.c.i

CMakeFiles/app.dir/imgp_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/imgp_utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Programming/C_C++/Projects/imgp/imgp_utils.c -o CMakeFiles/app.dir/imgp_utils.c.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.c.o" \
"CMakeFiles/app.dir/imgp_bitmap.c.o" \
"CMakeFiles/app.dir/imgp_utils.c.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app: CMakeFiles/app.dir/main.c.o
app: CMakeFiles/app.dir/imgp_bitmap.c.o
app: CMakeFiles/app.dir/imgp_utils.c.o
app: CMakeFiles/app.dir/build.make
app: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Programming/C_C++/Projects/imgp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app
.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd /home/alex/Programming/C_C++/Projects/imgp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Programming/C_C++/Projects/imgp /home/alex/Programming/C_C++/Projects/imgp /home/alex/Programming/C_C++/Projects/imgp /home/alex/Programming/C_C++/Projects/imgp /home/alex/Programming/C_C++/Projects/imgp/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/app.dir/depend

