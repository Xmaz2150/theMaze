cmake_minimum_required(VERSION 3.16)
project(theMaze)

add_executable(maze WIN32 src/maze.c src/draw.c src/init.c src/input.c src/math.c src/ray.c)

target_include_directories(maze PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(maze "${CMAKE_SOURCE_DIR}/lib/x64/SDL2main.lib")
target_link_libraries(maze "${CMAKE_SOURCE_DIR}/lib/x64/SDL2.lib")
target_link_libraries(maze "${CMAKE_SOURCE_DIR}/lib/x64/SDL2_image.lib")