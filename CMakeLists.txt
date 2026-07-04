cmake_minimum_required(VERSION 3.16)
project(MindScape VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Journalentry.h
        Journalentry.cpp
        Entrymanager.h
        Entrymanager.cpp
        Moodentry.h
        Moodentry.cpp
        Moodmanager.h
        Moodmanager.cpp
        Quote.h
        Quote.cpp
        Quotemanager.h
        Quotemanager.cpp
        Habit.h
        Habit.cpp
        Habitlog.h
        Habitlog.cpp
        Habitmanager.h
        Habitmanager.cpp
        Appcontroller.h
        Appcontroller.cpp
        bookcard.h
        bookcard.cpp
        bookcard.ui
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MindScape
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        stickerpicker.h stickerpicker.cpp stickerpicker.ui
        draggablesticker.h draggablesticker.cpp
        bookcard.h bookcard.cpp bookcard.ui
        resources.qrc
        habitcard.h habitcard.cpp habitcard.ui



    )
else()
    if(ANDROID)
        add_library(MindScape SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MindScape
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_link_libraries(MindScape PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MindScape)
endif()
set_target_properties(MindScape PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_custom_command(TARGET MindScape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data"
    "$<TARGET_FILE_DIR:MindScape>/data"
)

include(GNUInstallDirs)
install(TARGETS MindScape
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MindScape)
endif()