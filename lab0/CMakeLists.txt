# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_library(corelib OBJECT 
							module1.cpp 
							module1.h 
							module2.cpp 
							module2.h
							module3.cpp 
							module3.h
			)
add_executable (firstcmake main.cpp)
target_link_libraries (firstcmake corelib)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
