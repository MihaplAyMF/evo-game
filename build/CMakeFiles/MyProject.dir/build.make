# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/miha/MyNewPetProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miha/MyNewPetProject/build

# Include any dependencies generated for this target.
include CMakeFiles/MyProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyProject.dir/flags.make

CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o: /home/miha/MyNewPetProject/src/Code/Component/Button.cpp
CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o -c /home/miha/MyNewPetProject/src/Code/Component/Button.cpp

CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/Component/Button.cpp > CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.i

CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/Component/Button.cpp -o CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.s

CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o: /home/miha/MyNewPetProject/src/Code/Component/Component.cpp
CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o -c /home/miha/MyNewPetProject/src/Code/Component/Component.cpp

CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/Component/Component.cpp > CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.i

CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/Component/Component.cpp -o CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.s

CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o: /home/miha/MyNewPetProject/src/Code/Component/Container.cpp
CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o -c /home/miha/MyNewPetProject/src/Code/Component/Container.cpp

CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/Component/Container.cpp > CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.i

CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/Component/Container.cpp -o CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.s

CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o: /home/miha/MyNewPetProject/src/Code/Component/Label.cpp
CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o -c /home/miha/MyNewPetProject/src/Code/Component/Label.cpp

CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/Component/Label.cpp > CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.i

CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/Component/Label.cpp -o CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.s

CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o: /home/miha/MyNewPetProject/src/Code/Entity/DataTables.cpp
CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o -c /home/miha/MyNewPetProject/src/Code/Entity/DataTables.cpp

CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/Entity/DataTables.cpp > CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.i

CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/Entity/DataTables.cpp -o CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.s

CMakeFiles/MyProject.dir/src/Code/Game.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/Game.cpp.o: /home/miha/MyNewPetProject/src/Code/Game.cpp
CMakeFiles/MyProject.dir/src/Code/Game.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MyProject.dir/src/Code/Game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/Game.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/Game.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/Game.cpp.o -c /home/miha/MyNewPetProject/src/Code/Game.cpp

CMakeFiles/MyProject.dir/src/Code/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/Game.cpp > CMakeFiles/MyProject.dir/src/Code/Game.cpp.i

CMakeFiles/MyProject.dir/src/Code/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/Game.cpp -o CMakeFiles/MyProject.dir/src/Code/Game.cpp.s

CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o: /home/miha/MyNewPetProject/src/Code/ResourseHandle/Utility.cpp
CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o -c /home/miha/MyNewPetProject/src/Code/ResourseHandle/Utility.cpp

CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/ResourseHandle/Utility.cpp > CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.i

CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/ResourseHandle/Utility.cpp -o CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.s

CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o: /home/miha/MyNewPetProject/src/Code/State/GameState.cpp
CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o -c /home/miha/MyNewPetProject/src/Code/State/GameState.cpp

CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/State/GameState.cpp > CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.i

CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/State/GameState.cpp -o CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.s

CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o: /home/miha/MyNewPetProject/src/Code/State/MenuState.cpp
CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o -c /home/miha/MyNewPetProject/src/Code/State/MenuState.cpp

CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/State/MenuState.cpp > CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.i

CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/State/MenuState.cpp -o CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.s

CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o: /home/miha/MyNewPetProject/src/Code/State/State.cpp
CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o -c /home/miha/MyNewPetProject/src/Code/State/State.cpp

CMakeFiles/MyProject.dir/src/Code/State/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/State/State.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/State/State.cpp > CMakeFiles/MyProject.dir/src/Code/State/State.cpp.i

CMakeFiles/MyProject.dir/src/Code/State/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/State/State.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/State/State.cpp -o CMakeFiles/MyProject.dir/src/Code/State/State.cpp.s

CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o: /home/miha/MyNewPetProject/src/Code/State/StateStack.cpp
CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o -c /home/miha/MyNewPetProject/src/Code/State/StateStack.cpp

CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/State/StateStack.cpp > CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.i

CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/State/StateStack.cpp -o CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.s

CMakeFiles/MyProject.dir/src/Code/main.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/src/Code/main.cpp.o: /home/miha/MyNewPetProject/src/Code/main.cpp
CMakeFiles/MyProject.dir/src/Code/main.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/MyProject.dir/src/Code/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/src/Code/main.cpp.o -MF CMakeFiles/MyProject.dir/src/Code/main.cpp.o.d -o CMakeFiles/MyProject.dir/src/Code/main.cpp.o -c /home/miha/MyNewPetProject/src/Code/main.cpp

CMakeFiles/MyProject.dir/src/Code/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/src/Code/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miha/MyNewPetProject/src/Code/main.cpp > CMakeFiles/MyProject.dir/src/Code/main.cpp.i

CMakeFiles/MyProject.dir/src/Code/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/src/Code/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miha/MyNewPetProject/src/Code/main.cpp -o CMakeFiles/MyProject.dir/src/Code/main.cpp.s

# Object files for target MyProject
MyProject_OBJECTS = \
"CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/Game.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o" \
"CMakeFiles/MyProject.dir/src/Code/main.cpp.o"

# External object files for target MyProject
MyProject_EXTERNAL_OBJECTS =

MyProject: CMakeFiles/MyProject.dir/src/Code/Component/Button.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/Component/Component.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/Component/Container.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/Component/Label.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/Entity/DataTables.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/Game.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/ResourseHandle/Utility.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/State/GameState.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/State/MenuState.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/State/State.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/State/StateStack.cpp.o
MyProject: CMakeFiles/MyProject.dir/src/Code/main.cpp.o
MyProject: CMakeFiles/MyProject.dir/build.make
MyProject: /home/miha/MyNewPetProject/vcpkg/installed/x64-linux/debug/lib/libsfml-network-s-d.a
MyProject: /home/miha/MyNewPetProject/vcpkg/installed/x64-linux/debug/lib/libsfml-graphics-s-d.a
MyProject: /home/miha/MyNewPetProject/vcpkg/installed/x64-linux/debug/lib/libsfml-window-s-d.a
MyProject: /home/miha/MyNewPetProject/vcpkg/installed/x64-linux/debug/lib/libsfml-audio-s-d.a
MyProject: /home/miha/MyNewPetProject/vcpkg/installed/x64-linux/debug/lib/libsfml-system-s-d.a
MyProject: /usr/lib/x86_64-linux-gnu/libXrandr.so
MyProject: /usr/lib/x86_64-linux-gnu/libXcursor.so
MyProject: /usr/lib/x86_64-linux-gnu/libXrender.so
MyProject: /usr/lib/x86_64-linux-gnu/libXfixes.so
MyProject: /usr/lib/x86_64-linux-gnu/libXi.so
MyProject: /usr/lib/x86_64-linux-gnu/libXext.so
MyProject: /usr/lib/x86_64-linux-gnu/libX11.so
MyProject: /usr/lib/x86_64-linux-gnu/libGL.so
MyProject: /usr/lib/x86_64-linux-gnu/libudev.so
MyProject: /usr/lib/x86_64-linux-gnu/libfreetype.so
MyProject: /usr/lib/x86_64-linux-gnu/libvorbisfile.so
MyProject: /usr/lib/x86_64-linux-gnu/libvorbisenc.so
MyProject: /usr/lib/x86_64-linux-gnu/libvorbis.so
MyProject: /usr/lib/x86_64-linux-gnu/libogg.so
MyProject: /usr/lib/x86_64-linux-gnu/libFLAC.so
MyProject: CMakeFiles/MyProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/miha/MyNewPetProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable MyProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyProject.dir/build: MyProject
.PHONY : CMakeFiles/MyProject.dir/build

CMakeFiles/MyProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyProject.dir/clean

CMakeFiles/MyProject.dir/depend:
	cd /home/miha/MyNewPetProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miha/MyNewPetProject /home/miha/MyNewPetProject /home/miha/MyNewPetProject/build /home/miha/MyNewPetProject/build /home/miha/MyNewPetProject/build/CMakeFiles/MyProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyProject.dir/depend

