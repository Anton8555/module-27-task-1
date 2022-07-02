cmake_minimum_required(VERSION 3.21)

add_executable("module_27_task_1"
        main.cpp
        branch.cpp)

target_include_directories("module_27_task_1" PUBLIC ${MY_INCLUDE_DIR})