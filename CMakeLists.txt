cmake_minimum_required(VERSION 3.25)

project(
  $ENV{name_project}
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
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

set(UI ${CMAKE_CURRENT_LIST_DIR}/src/Widgets/MainWindow/mainwindow.ui)
qt_wrap_ui(UI_HEADERS ${UI})

add_executable(
  ${PROJECT_NAME}
  ${UI_HEADERS}
  src/main.cpp
  src/Widgets/MainWindow/Source/mainwindow.cpp
  src/Widgets/MainWindow/Source/mainwindow.h
  src/Lib/Networking/ServerPart/Server.h
  src/Lib/Networking/ServerPart/Server.cpp
  src/Lib/Networking/ServerPart/ClientConnection.h
  src/Lib/Networking/ServerPart/ClientConnection.cpp
  src/Lib/Networking/ClientPart/Client.h
  src/Lib/Networking/ClientPart/Client.cpp)

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Network)
