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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/oliviahu/3451/cs3451

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/oliviahu/3451/cs3451/build

# Include any dependencies generated for this target.
include tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/compiler_depend.make

# Include the progress variables for this target.
include tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/progress.make

# Include the compile flags for this target's objects.
include tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/flags.make

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.o: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/flags.make
tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.o: /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/tests/opacity.c
tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.o: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/oliviahu/3451/cs3451/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.o"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.o -MF CMakeFiles/opacity.dir/opacity.c.o.d -o CMakeFiles/opacity.dir/opacity.c.o -c /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/tests/opacity.c

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/opacity.dir/opacity.c.i"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/tests/opacity.c > CMakeFiles/opacity.dir/opacity.c.i

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/opacity.dir/opacity.c.s"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/tests/opacity.c -o CMakeFiles/opacity.dir/opacity.c.s

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.o: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/flags.make
tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.o: /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/deps/glad_gl.c
tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.o: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/oliviahu/3451/cs3451/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.o"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.o -MF CMakeFiles/opacity.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/opacity.dir/__/deps/glad_gl.c.o -c /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/deps/glad_gl.c

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/opacity.dir/__/deps/glad_gl.c.i"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/deps/glad_gl.c > CMakeFiles/opacity.dir/__/deps/glad_gl.c.i

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/opacity.dir/__/deps/glad_gl.c.s"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/deps/glad_gl.c -o CMakeFiles/opacity.dir/__/deps/glad_gl.c.s

# Object files for target opacity
opacity_OBJECTS = \
"CMakeFiles/opacity.dir/opacity.c.o" \
"CMakeFiles/opacity.dir/__/deps/glad_gl.c.o"

# External object files for target opacity
opacity_EXTERNAL_OBJECTS =

tutorials/tutorial_opengl/glfw-3.3/tests/opacity.app/Contents/MacOS/opacity: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/opacity.c.o
tutorials/tutorial_opengl/glfw-3.3/tests/opacity.app/Contents/MacOS/opacity: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/__/deps/glad_gl.c.o
tutorials/tutorial_opengl/glfw-3.3/tests/opacity.app/Contents/MacOS/opacity: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/build.make
tutorials/tutorial_opengl/glfw-3.3/tests/opacity.app/Contents/MacOS/opacity: tutorials/tutorial_opengl/glfw-3.3/src/libglfw3.a
tutorials/tutorial_opengl/glfw-3.3/tests/opacity.app/Contents/MacOS/opacity: tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/oliviahu/3451/cs3451/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable opacity.app/Contents/MacOS/opacity"
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opacity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/build: tutorials/tutorial_opengl/glfw-3.3/tests/opacity.app/Contents/MacOS/opacity
.PHONY : tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/build

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/clean:
	cd /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests && $(CMAKE_COMMAND) -P CMakeFiles/opacity.dir/cmake_clean.cmake
.PHONY : tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/clean

tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/depend:
	cd /Users/oliviahu/3451/cs3451/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oliviahu/3451/cs3451 /Users/oliviahu/3451/cs3451/tutorials/tutorial_opengl/glfw-3.3/tests /Users/oliviahu/3451/cs3451/build /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests /Users/oliviahu/3451/cs3451/build/tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tutorials/tutorial_opengl/glfw-3.3/tests/CMakeFiles/opacity.dir/depend

