# ----------------------------------------------------------------- #
#                                                                   #
#                                                                   #
#           Universidade Federal de Minas Gerais - UFMG             #
#               Departamento de Ciência da Computação               #
#           -------------------------------------------             #
#           Júlio Albinati, Paulo Bicalho, Rubens Emilio            #
#              {jalbinati,paulo,rubens}@[dcc.ufmg.br]               #
#                                                                   #
#                                                                   #
# ----------------------------------------------------------------- #
cmake_minimum_required (VERSION 2.8)
project (SpeedGames CXX)

# Compiler
set (OUTPUT gIrAfA)
set (CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS "-std=c++0x -O3")
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Paths
add_subdirectory (Game)
add_subdirectory (Screen)
# add_subdirectory (Player)
# add_subdirectory (Company)

link_directories (/usr/lib)
link_directories (${CMAKE_BINARY_DIR}/Game)

# Build
add_executable (${OUTPUT} main.cpp)
add_dependencies (${OUTPUT} Game)
target_link_libraries (${OUTPUT} Game)
