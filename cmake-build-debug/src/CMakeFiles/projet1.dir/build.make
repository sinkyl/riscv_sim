# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\admin\Desktop\ele749P1-GUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/projet1.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/projet1.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/projet1.dir/flags.make

src/CMakeFiles/projet1.dir/decodeur.c.obj: src/CMakeFiles/projet1.dir/flags.make
src/CMakeFiles/projet1.dir/decodeur.c.obj: src/CMakeFiles/projet1.dir/includes_C.rsp
src/CMakeFiles/projet1.dir/decodeur.c.obj: ../src/decodeur.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/projet1.dir/decodeur.c.obj"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\projet1.dir\decodeur.c.obj   -c C:\Users\admin\Desktop\ele749P1-GUI\src\decodeur.c

src/CMakeFiles/projet1.dir/decodeur.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet1.dir/decodeur.c.i"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\admin\Desktop\ele749P1-GUI\src\decodeur.c > CMakeFiles\projet1.dir\decodeur.c.i

src/CMakeFiles/projet1.dir/decodeur.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet1.dir/decodeur.c.s"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\admin\Desktop\ele749P1-GUI\src\decodeur.c -o CMakeFiles\projet1.dir\decodeur.c.s

src/CMakeFiles/projet1.dir/processeur.c.obj: src/CMakeFiles/projet1.dir/flags.make
src/CMakeFiles/projet1.dir/processeur.c.obj: src/CMakeFiles/projet1.dir/includes_C.rsp
src/CMakeFiles/projet1.dir/processeur.c.obj: ../src/processeur.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/projet1.dir/processeur.c.obj"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\projet1.dir\processeur.c.obj   -c C:\Users\admin\Desktop\ele749P1-GUI\src\processeur.c

src/CMakeFiles/projet1.dir/processeur.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet1.dir/processeur.c.i"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\admin\Desktop\ele749P1-GUI\src\processeur.c > CMakeFiles\projet1.dir\processeur.c.i

src/CMakeFiles/projet1.dir/processeur.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet1.dir/processeur.c.s"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\admin\Desktop\ele749P1-GUI\src\processeur.c -o CMakeFiles\projet1.dir\processeur.c.s

src/CMakeFiles/projet1.dir/__/main.c.obj: src/CMakeFiles/projet1.dir/flags.make
src/CMakeFiles/projet1.dir/__/main.c.obj: src/CMakeFiles/projet1.dir/includes_C.rsp
src/CMakeFiles/projet1.dir/__/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/projet1.dir/__/main.c.obj"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\projet1.dir\__\main.c.obj   -c C:\Users\admin\Desktop\ele749P1-GUI\main.c

src/CMakeFiles/projet1.dir/__/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet1.dir/__/main.c.i"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\admin\Desktop\ele749P1-GUI\main.c > CMakeFiles\projet1.dir\__\main.c.i

src/CMakeFiles/projet1.dir/__/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet1.dir/__/main.c.s"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\admin\Desktop\ele749P1-GUI\main.c -o CMakeFiles\projet1.dir\__\main.c.s

src/CMakeFiles/projet1.dir/__/ui/ui.c.obj: src/CMakeFiles/projet1.dir/flags.make
src/CMakeFiles/projet1.dir/__/ui/ui.c.obj: src/CMakeFiles/projet1.dir/includes_C.rsp
src/CMakeFiles/projet1.dir/__/ui/ui.c.obj: ../ui/ui.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/projet1.dir/__/ui/ui.c.obj"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\projet1.dir\__\ui\ui.c.obj   -c C:\Users\admin\Desktop\ele749P1-GUI\ui\ui.c

src/CMakeFiles/projet1.dir/__/ui/ui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet1.dir/__/ui/ui.c.i"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\admin\Desktop\ele749P1-GUI\ui\ui.c > CMakeFiles\projet1.dir\__\ui\ui.c.i

src/CMakeFiles/projet1.dir/__/ui/ui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet1.dir/__/ui/ui.c.s"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\admin\Desktop\ele749P1-GUI\ui\ui.c -o CMakeFiles\projet1.dir\__\ui\ui.c.s

# Object files for target projet1
projet1_OBJECTS = \
"CMakeFiles/projet1.dir/decodeur.c.obj" \
"CMakeFiles/projet1.dir/processeur.c.obj" \
"CMakeFiles/projet1.dir/__/main.c.obj" \
"CMakeFiles/projet1.dir/__/ui/ui.c.obj"

# External object files for target projet1
projet1_EXTERNAL_OBJECTS =

src/projet1.exe: src/CMakeFiles/projet1.dir/decodeur.c.obj
src/projet1.exe: src/CMakeFiles/projet1.dir/processeur.c.obj
src/projet1.exe: src/CMakeFiles/projet1.dir/__/main.c.obj
src/projet1.exe: src/CMakeFiles/projet1.dir/__/ui/ui.c.obj
src/projet1.exe: src/CMakeFiles/projet1.dir/build.make
src/projet1.exe: src/CMakeFiles/projet1.dir/linklibs.rsp
src/projet1.exe: src/CMakeFiles/projet1.dir/objects1.rsp
src/projet1.exe: src/CMakeFiles/projet1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable projet1.exe"
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\projet1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/projet1.dir/build: src/projet1.exe

.PHONY : src/CMakeFiles/projet1.dir/build

src/CMakeFiles/projet1.dir/clean:
	cd /d C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src && $(CMAKE_COMMAND) -P CMakeFiles\projet1.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/projet1.dir/clean

src/CMakeFiles/projet1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\admin\Desktop\ele749P1-GUI C:\Users\admin\Desktop\ele749P1-GUI\src C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src C:\Users\admin\Desktop\ele749P1-GUI\cmake-build-debug\src\CMakeFiles\projet1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/projet1.dir/depend

