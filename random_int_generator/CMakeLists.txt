cmake_minimum_required(VERSION 4.0)
project(random_int_generator C)

set(CMAKE_C_STANDARD 17)

add_executable(random_int_generator main.c)

target_link_libraries(random_int_generator bcrypt)