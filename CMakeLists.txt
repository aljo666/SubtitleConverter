cmake_minimum_required(VERSION 3.16)

project(SubtitleConverter LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core5Compat)

add_executable(SubtitleConverter
  main.cpp
  subfileconverter.h subfileconverter.cpp
)
target_link_libraries(SubtitleConverter PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Core5Compat
)

include(GNUInstallDirs)
install(TARGETS SubtitleConverter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
