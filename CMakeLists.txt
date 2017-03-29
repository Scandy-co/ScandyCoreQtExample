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
set(Qt5Widgets_DIR "/usr/local/opt/qt5/lib/cmake/Qt5Widgets")
find_package(Qt5Widgets REQUIRED)
set(Qt5Core_DIR "/usr/local/opt/qt5/lib/cmake/Qt5Core")
find_package(Qt5Core REQUIRED)

# And now add the ScandyCore directory
#set(ScandyCore_DIR "${ScandyCoreQtExample_SOURCE_DIR}/dependencies/ScandyCore/")
#find_package(ScandyCore)

set(CMAKE_CXX_STANDARD 14)

# link the ScandyCore lib directory
# link_directories(
#   "${ScandyCore_LIB_DIRS}"
# )

# include the ScandyCore include directory
# include_directories(
#   "${ScandyCore_INCLUDE_DIRS}"
# )

include_directories(
  ${ScandyCore_HEADER_DIRS}
)

link_directories(
  "${royale_LIB_DIR}"
)

link_directories(
  "${Scandy_VTK_LIBRARY_DIRS}"
)

set(common_libs
  "ScandyCore"
  "snappy"
  "${VTK_LIBRARIES}"
)

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CPP_FILES *.cpp)

# Tell CMake to create the helloworld executable
qt5_wrap_ui(UISrcs ${UI_FILES})
add_executable(ScandyCoreQtExample MACOSX_BUNDLE ${CPP_FILES} ${UISrcs} ${QT_WRAP})
qt5_use_modules(ScandyCoreQtExample Core Gui)

# Use the Widgets module from Qt 5.
target_link_libraries(ScandyCoreQtExample
  Qt5::Widgets
)

# Also link the ScandyCore libraries
# target_link_libraries(ScandyCoreQtExample
#   ${ScandyCore_LIBRARIES}
# )

target_link_libraries(ScandyCoreQtExample
  "${common_libs}"
)
