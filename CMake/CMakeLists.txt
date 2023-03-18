cmake_minimum_required (VERSION 3.8)

project ("CMakeRobot")

# Подпроекты.
#add_subdirectory ("CMakeRobot")


set(SOURCE_EXE main.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB CMakeRobot.cpp)			# Тоже самое, но для библиотеки

add_library(CMakeRobot STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем CMakeRobot

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

target_link_libraries(main CMakeRobot)		# Линковка программы с библиотекой
