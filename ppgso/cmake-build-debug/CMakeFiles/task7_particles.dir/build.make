# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task7_particles.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/task7_particles.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task7_particles.dir/flags.make

CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.obj: CMakeFiles/task7_particles.dir/flags.make
CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.obj: CMakeFiles/task7_particles.dir/includes_CXX.rsp
CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.obj: ../src/task7_particles/task7_particles.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\task7_particles.dir\src\task7_particles\task7_particles.cpp.obj -c C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\src\task7_particles\task7_particles.cpp

CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\src\task7_particles\task7_particles.cpp > CMakeFiles\task7_particles.dir\src\task7_particles\task7_particles.cpp.i

CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\src\task7_particles\task7_particles.cpp -o CMakeFiles\task7_particles.dir\src\task7_particles\task7_particles.cpp.s

# Object files for target task7_particles
task7_particles_OBJECTS = \
"CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.obj"

# External object files for target task7_particles
task7_particles_EXTERNAL_OBJECTS =

task7_particles.exe: CMakeFiles/task7_particles.dir/src/task7_particles/task7_particles.cpp.obj
task7_particles.exe: CMakeFiles/task7_particles.dir/build.make
task7_particles.exe: libppgso.a
task7_particles.exe: libshaders.a
task7_particles.exe: ../dependencies/lib/mingw/libglfw3.a
task7_particles.exe: ../dependencies/lib/mingw/libglew32.a
task7_particles.exe: CMakeFiles/task7_particles.dir/linklibs.rsp
task7_particles.exe: CMakeFiles/task7_particles.dir/objects1.rsp
task7_particles.exe: CMakeFiles/task7_particles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task7_particles.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task7_particles.dir\link.txt --verbose=$(VERBOSE)
	"C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E copy_directory C:/Users/samue/OneDrive/School/PPGSO/projekt/ppgso/data/ C:/Users/samue/OneDrive/School/PPGSO/projekt/ppgso/cmake-build-debug

# Rule to build all files generated by this target.
CMakeFiles/task7_particles.dir/build: task7_particles.exe
.PHONY : CMakeFiles/task7_particles.dir/build

CMakeFiles/task7_particles.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\task7_particles.dir\cmake_clean.cmake
.PHONY : CMakeFiles/task7_particles.dir/clean

CMakeFiles/task7_particles.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\cmake-build-debug C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\cmake-build-debug C:\Users\samue\OneDrive\School\PPGSO\projekt\ppgso\cmake-build-debug\CMakeFiles\task7_particles.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task7_particles.dir/depend

