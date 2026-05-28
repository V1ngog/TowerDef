cmake_minimum_required(VERSION 3.16)
project(TowerDef)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(TowerDef
    src/main.cpp
    src/PAGE/menupage.cpp
    src/PAGE/settingspage.cpp
    src/WIN/basewindow.cpp
    src/WIN/mainwindow.cpp
    include/PAGE/basepage.h
    include/PAGE/settingspage.h
    include/PAGE/menupage.h
    include/WIN/basewindow.h
    include/WIN/mainwindow.h
)

target_link_libraries(TowerDef PRIVATE Qt6::Widgets)

target_include_directories(TowerDef PRIVATE 
    ${CMAKE_SOURCE_DIR}/include/WIN
    ${CMAKE_SOURCE_DIR}/include/PAGE
)