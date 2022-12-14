cmake_minimum_required(VERSION 3.5)

project(GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories($ENV{HOME}/pes/include)
link_directories($ENV{HOME}/pes/lib)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES

	corecontroller.h
	coregui.h
        usermanager.h
        main.cpp
        corecontroller.cpp
        coregui.cpp
        usermanager.cpp
        loginwindow.cpp
        loginwindow.ui
        loginwindow.h
        dialog_failure.cpp
        dialog_failure.h
        dialog_failure.ui
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        dialog_selectimage_file.cpp
        dialog_selectimage_file.h
        dialog_selectimage_file.ui
        imagefileoperationmanager.cpp
        imagefileoperationmanager.h
        rsc_file.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets authentication log uiapi pthread gcrypt gpg-error communicationmanager arinc615a transfer tftp tftpd blsecurity cjson imagemanager tinyxml2)

set_target_properties(GUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GUI)
endif()
