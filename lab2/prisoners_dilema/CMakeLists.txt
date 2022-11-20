cmake_minimum_required(VERSION 3.14)
project(PRISONERS_CHOICE)

set(CMAKE_CXX_STANDARD 14)

#....................................................................добавляем исполняемые файлы....................................................................#

#...................добавляем библиотеку сначала подключив новую папку, а затем, линкнув библиотеку, настраиваем нормальное использование include...................#

add_subdirectory(prisoners_habbit)

add_executable(PRISONERS_CHOICE main.cpp)

target_include_directories(PRISONERS_CHOICE PRIVATE prisoners_habbit)

target_link_libraries(PRISONERS_CHOICE PRIVATE prisoners_habbit)



#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        # Specify the commit you depend on and update it regularly.
#        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
#)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

#target_link_libraries(BigInt_lab PRIVATE bigint_ gtest_main)