cmake_minimum_required(VERSION 3.3)

project(imgp)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(app main.c imgp_bitmap.c imgp_utils.c)