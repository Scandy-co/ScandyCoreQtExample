# Copyright (C) 2017 Scandy
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 2.8.11)

project(ScandyCoreQtExample)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# find the ui_mainwindow
SET(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)

# And now add the ScandyCore directory
set(ScandyCore_DIR "${ScandyCoreQtExample_SOURCE_DIR}/dependencies/ScandyCore/")
find_package(ScandyCore)

set(CMAKE_CXX_STANDARD 14)

# link the ScandyCore lib directory
link_directories(
  "${ScandyCore_LIB_DIRS}"
)

# include the ScandyCore include directory
include_directories(
  "${ScandyCore_INCLUDE_DIRS}"
)

# Tell CMake to create the helloworld executable
add_executable(ScandyCoreQtExample mainwindow.cpp main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(ScandyCoreQtExample
  Qt5::Widgets
)

# Also link the ScandyCore libraries
target_link_libraries(ScandyCoreQtExample
  ${ScandyCore_LIBRARIES}
)
