cmake_minimum_required(VERSION 3.5)

project(EM_project VERSION 0.1 LANGUAGES CXX)
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#начиная с какой версии сборка будет собираться
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#поиск системой сборки файлов
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS QuickWidgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
#find_package(nlohmann_json)


#из каких языков проект
set(TS_FILES EM_project_en_GB.ts)


#из каких файлов собирается проект
set(PROJECT_SOURCES
        main.cpp
        em_proj.h
        em_proj.cpp
        menu.h
        menu.cpp
        autors.h
        autors.cpp
        startwidget.h
        startwidget.cpp
        graph_parser.h
        graph_parser.cpp
        mygraphicsview.h
        mygraphicsview.cpp
        myqgraphicsrectiten.h
        myqgraphicsrectiten.cpp
        human.h
        human.cpp
        ${TS_FILES}
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EM_project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET EM_project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(EM_project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(EM_project
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


#подключение библиотек
#target_link_libraries(EM_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)
add_subdirectory(matplotplusplus)


#target_link_libraries(${EM_project} nlohmann::nlohmann )
#add_executable(EM_project em_proj.h)

target_link_libraries(EM_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets nlohmann_json::nlohmann_json matplot)

#add_subdirectory(dependencies/)
#target_link_libraries(${EM_project} nlohmann)


#сборка под разные ОС
set_target_properties(EM_project PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS EM_project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


#сборка проекта от версии 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EM_project)
endif()
