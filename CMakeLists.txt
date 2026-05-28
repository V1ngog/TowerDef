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
    src/PAGE/gamepage.cpp
    src/WIN/basewindow.cpp
    src/WIN/mainwindow.cpp
    src/GAME/wavemanager.cpp
    src/GAME/gamescreen.cpp
    src/GAME/collisionmanager.cpp
    src/BUILDS/build.cpp
    src/GAME/enemy.cpp
    src/GAME/missile.cpp
    include/FACTORY/factories.h
    include/FACTORY/gamefactory.h
    include/FACTORY/tempgameclasses.h
    include/GAME/build.h
    include/GAME/collisionmanager.h
    include/GAME/gamescreen.h
    include/GAME/wavemanager.h
    include/GAME/enemy.h
    include/GAME/missile.h
    include/PAGE/gamepage.h
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
    ${CMAKE_SOURCE_DIR}/include/GAME
    ${CMAKE_SOURCE_DIR}/include/factory
)