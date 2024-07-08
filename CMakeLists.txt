cmake_minimum_required(VERSION 3.5)

project(SuperMario VERSION 0.1 LANGUAGES CXX)

# Enable automatic UIC, MOC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

# Add compiler flags for MSVC
if (MSVC)
    add_compile_options(/Zc:__cplusplus)
    add_compile_options(/permissive-)  # Add /permissive- option here
endif()

# Find the Qt package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Define project sources
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        position.h position.cpp
        bodyobject.h bodyobject.cpp
        platform.h platform.cpp
        decorator.h decorator.cpp
        game.h game.cpp
        player.h player.cpp

        )

# Add the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SuperMario
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            resource.qrc
            )
else()
    if(ANDROID)
        add_library(SuperMario SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SuperMario
                ${PROJECT_SOURCES}
                )
    endif()
endif()

# Link the required Qt libraries
target_link_libraries(SuperMario PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SuperMario)
endif()

set_target_properties(SuperMario PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

# Installation settings
include(GNUInstallDirs)
install(TARGETS SuperMario
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

# Finalize the executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SuperMario)
endif()
