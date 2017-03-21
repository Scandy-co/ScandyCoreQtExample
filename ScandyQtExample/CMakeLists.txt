cmake_minimum_required(VERSION 2.8.11)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# find the ui_mainwindow
SET(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)

set(CMAKE_CXX_STANDARD 14)

get_target_property(QtCore_location Qt5::Core LOCATION)

# Tell CMake to create the helloworld executable
# add_executable(helloworld WIN32 main.cpp)
add_executable(helloworld mainwindow.cpp main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)
