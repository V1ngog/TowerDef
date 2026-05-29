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
    src/PAGE/winpage.cpp
    src/WIN/basewindow.cpp
    src/WIN/mainwindow.cpp
    src/GAME/wavemanager.cpp
    src/GAME/gamescreen.cpp
    src/GAME/collisionmanager.cpp
    src/GAME/enemy.cpp
    src/GAME/missile.cpp
    src/GAME/build.cpp
    src/GAME/TOWER/strongtower.cpp
    src/GAME/TOWER/weaktower.cpp
    src/GAME/ENEMY/fastenemy.cpp
    src/GAME/ENEMY/slowenemy.cpp
    src/GAME/MISSILE/strongmissile.cpp
    src/GAME/MISSILE/weakmissile.cpp
    include/GAME/build.h
    include/GAME/collisionmanager.h
    include/GAME/gamescreen.h
    include/GAME/wavemanager.h
    include/GAME/enemy.h
    include/GAME/missile.h
    include/GAME/TOWER/strongtower.h
    include/GAME/TOWER/weaktower.h
    include/GAME/ENEMY/fastenemy.h
    include/GAME/ENEMY/slowenemy.h
    include/GAME/MISSILE/strongmissile.h
    include/GAME/MISSILE/weakmissile.h
    include/GAME/FACTORY/factories.h
    include/GAME/FACTORY/gamefactory.h
    include/PAGE/gamepage.h
    include/PAGE/basepage.h
    include/PAGE/settingspage.h
    include/PAGE/menupage.h
    include/PAGE/winpage.h
    include/WIN/basewindow.h
    include/WIN/mainwindow.h
)

target_link_libraries(TowerDef PRIVATE Qt6::Widgets)

target_include_directories(TowerDef PRIVATE 
    ${CMAKE_SOURCE_DIR}/include/WIN
    ${CMAKE_SOURCE_DIR}/include/PAGE
    ${CMAKE_SOURCE_DIR}/include/GAME
    ${CMAKE_SOURCE_DIR}/include/GAME/TOWER
    ${CMAKE_SOURCE_DIR}/include/GAME/MISSILE
    ${CMAKE_SOURCE_DIR}/include/GAME/ENEMY
    ${CMAKE_SOURCE_DIR}/include/GAME/FACTORY
)