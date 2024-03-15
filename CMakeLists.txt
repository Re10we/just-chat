cmake_minimum_required(VERSION 3.25)

project(
  just-chat
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT REQUIRED COMPONENTS Widgets NAMES Qt6 Qt5)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(UI ${CMAKE_CURRENT_LIST_DIR}/src/Widgets/MainWindow/mainwindow.ui)
qt_wrap_ui(UI_HEADERS ${UI})

add_executable(
  ${PROJECT_NAME}
  ${UI_HEADERS} src/main.cpp src/Widgets/MainWindow/Source/mainwindow.cpp
  src/Widgets/MainWindow/Source/mainwindow.h)

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets)
#target_compile_options(${PROJECT_NAME} PRIVATE -std )
# set(PROJECT_SOURCES src/Widgets/MainWindow/mainwindow.ui src/main.cpp
# src/Widgets/MainWindow/src/mainwindow.cpp
# src/Widgets/MainWindow/src/mainwindow.h)

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6) qt_add_executable(just-chat
# MANUAL_FINALIZATION ${PROJECT_SOURCES}) # Define target properties for Android
# with Qt 6 as: set_property(TARGET # just-chat APPEND PROPERTY
# QT_ANDROID_PACKAGE_SOURCE_DIR # ${CMAKE_CURRENT_SOURCE_DIR}/android) For more
# information, see #
# https://doc.qt.io/qt-6/qt-add-executable.html#target-creation else()
# if(ANDROID) add_library(just-chat SHARED ${PROJECT_SOURCES}) # Define
# properties for Android with Qt 5 after find_package() calls as: #
# set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android") else()
# add_executable(just-chat ${PROJECT_SOURCES}) endif() endif()

# target_link_libraries(just-chat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# set_target_properties( just-chat PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER
# my.example.com MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
# MACOSX_BUNDLE_SHORT_VERSION_STRING
# ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

# if(QT_VERSION_MAJOR EQUAL 6) qt_finalize_executable(just-chat) endif()
