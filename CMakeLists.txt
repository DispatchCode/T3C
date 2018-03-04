cmake_minimum_required(VERSION 3.7)
project(TicTacToe_C)

set(CMAKE_C_FLAGS "-std=c99 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(SOURCE_FILES
        include/game.h
        include/minimax_alphabeta.h
        include/spatial_coords.h
        include/state.h
        include/utils.h
        src/game.c
        src/utility.c
        src/state.c
        src/minimax_alphabeta.c
        src/utility.c
        src/main_gui.c)

## SDL2 setup
## ----------------------------------------
set(prefix "C:\\MinGW")
set(exec_prefix "${prefix}")
set(libdir "${exec_prefix}\\lib")
set(SDL2_PREFIX "C:\\MinGW")
set(SDL2_EXEC_PREFIX "C:\\MinGW")
set(SDL2_LIBDIR "${exec_prefix}\\lib")
set(SDL2_INCLUDE_DIRS "${prefix}\\include\\SDL")
set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image  -mwindows")
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
## -----------------------------------------

## Executable and library names
add_executable(tic_tac_toe ${SOURCE_FILES})
target_include_directories(tic_tac_toe PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(tic_tac_toe ${SDL2_LIBRARIES})

## On Windows, copy DLL library from lib/windows/ under /bin
IF (WIN32)
add_custom_command(TARGET tic_tac_toe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/lib/windows"
        $<TARGET_FILE_DIR:tic_tac_toe>)
ENDIF()