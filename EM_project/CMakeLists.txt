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

#необходимо вставить путь к библиотеке qt
#set(CMAKE_PREFIX_PATH "C:/Qt/6.4.0/mingw_64/lib/cmake")


#target_compile_options(qt_cmake PUBLIC "/Zc:__cplusplus")

#поиск системой сборки файлов
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

#find_package(Qt6 REQUIRED COMPONENTS QuickWidgets)
#find_package(Qt6 REQUIRED COMPONENTS Widgets)ww
# PATHS "C:/Program Files (x86)/Graphviz/bin"


            #PATH "C:/Program Files/Graphviz/lib"
            #NO_CACHE )
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
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)


#set(PROJECT_LINK_LIBS ast.lib cdt.lib cgraph.lib circogen.lib dot.lib dotgen.lib expr.lib fdpgen.lib gd.lib graph.lib gts.lib gvc.lib
#gvortho.lib gvpack.lib gvplugin_core.lib gvplugin_dot_layout.lib gvplugin_gd.lib gvplugin_gdiplus.lib gvplugin_neato_layout.lib gvplugin_pango.lib
#gvprlib.lib ingraphs.lib minglelib.lib neatogen.lib osage.lib patchwork.lib Pathplan.lib rbtree.lib sfdp.lib sfio.lib sparse.lib
#topfish.lib twopigen.lib vmalloc.lib vpsc.lib xdot.lib)
#set(PROJECT_LINK_LIBS ${GVC} )
#set(PROJECT_LINK_LIBS ann.dll cdt.dll cgraph.dll gvc.dll gvplugin_core.dll gvplugin_dot_layout.dll gvplugin_gd.dll gvplugin_gdiplus.dll
#gvplugin_neato_layout.dll gvplugin_pango.dll Pathplan.dll vmalloc.dll)
#find_package(PkgConfig)'njn
#pkg_check_modules(GVC REQUIRED libgvc)
#target_include_directories(EM_project SYSTEM PUBLIC "C:/Program Files (x86)/Graphviz/bin")


#добавить в деррикторию ещё и папку с include 
target_include_directories(EM_project SYSTEM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/include/graphviz")  #${CGRAPH_LIBRARY} ${CDT_LIBRARY} ${GVC_LIBRARY}

find_library(GVC NAME gvc PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/bin")
find_library(CDT NAME cdt PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/bin")
find_library(CGRAPH NAME cgraph PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/bin")

message("4444")
message("${GVC} ${CDT} ${CGRAPH}")
message("3333")


#target_link_libraries(EM_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
#    "C:/Program Files/Graphviz/lib/gvc.lib"
#   "C:/Program Files/Graphviz/lib/cgraph.lib"
#   "C:/Program Files/Graphviz/lib/cdt.lib"
#    nlohmann_json::nlohmann_json)
#"D:/Graphviz/bin/gvc.dll" "D:/Graphviz/bin/cgraph.dll" "D:/Graphviz/bin/cdt.dll"


target_link_libraries(EM_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
 ${GVC} ${CDT} ${CGRAPH}
    #необходимо вставить нужные библиотеки
   #"C:/Program Files/Graphviz/lib/cdt.lib" "C:/Program Files/Graphviz/lib/cgraph.lib" "C:/Program Files/Graphviz/lib/gvc.lib" #vgc.lib cgraph.lib cdt.lib
    nlohmann_json::nlohmann_json)


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
