cmake_minimum_required(VERSION 3.16)

project(SuperMarioProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
    main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SuperMarioProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        game.h game.cpp
        player.h player.cpp
        resources.qrc
        block.h block.cpp
        obstacle.h obstacle.cpp
        level.h level.cpp
        checkpoint.h checkpoint.cpp
    )
else()
    if(ANDROID)
        add_library(SuperMarioProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SuperMarioProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SuperMarioProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(SuperMarioProject PRIVATE Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(SuperMarioProject PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SuperMarioProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SuperMarioProject)
endif()
