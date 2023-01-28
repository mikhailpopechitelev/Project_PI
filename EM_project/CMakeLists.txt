
cmake_minimum_required(VERSION 3.5)

project(EM_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

########################################################################################
#вместо CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/install можно прописать путь куда хотите произвести сборку"
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")

#начиная с какой версии сборка будет собираться
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#необходимо вставить путь к библиотеке qt для работы find_package
#set(CMAKE_PREFIX_PATH "C:/Qt/6.4.0/mingw_64/lib/cmake")

#поиск системой сборки файлов
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

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

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(EM_project SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(EM_project
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

#добавить в деррикторию ещё и папку с include 
#target_include_directories(EM_project SYSTEM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  #${CGRAPH_LIBRARY} ${CDT_LIBRARY} ${GVC_LIBRARY}

# поиск необходимых библиотек graphviz
find_library(GVC NAME gvc PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/lib")
find_library(CDT NAME cdt PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/lib")
find_library(CGRAPH NAME cgraph PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/lib")

#для отладки
message("4444")
message("${GVC} ; ${CDT}; ${CGRAPH}; ${CMAKE_CURRENT_SOURCE_DIR}; ${CMAKE_CURRENT_BINARY_DIR}"
;${CMAKE_INSTALL_PREFIX})
message("3333")

#подключение библиотек
 target_link_libraries(EM_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
   ${GVC} ${CDT} ${CGRAPH}
   nlohmann_json::nlohmann_json

#################################################################################################################
#необходимо вставить нужные библиотеки если find_library не найдет их
#"${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/lib/cdt.lib"
#"${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/lib/cgraph.lib"
#"${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/lib/gvc.lib"
#"${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/bin/cdt.dll"
#"${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/bin/cgraph.dll"
#"${CMAKE_CURRENT_SOURCE_DIR}/Graphviz/bin/gvc.dll"
################################################################################################################

)


#сборка под разные ОС
set_target_properties(EM_project PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


#сборка проекта от версии 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EM_project)
endif()


install(TARGETS EM_project
    CONFIGURATIONS Release
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)
#на случай если find_library найдет не статическую ,а динамическую библиотеку (не знаю почему но такое бывает)
install(FILES ${GVC} ${CDT} ${CGRAPH} DESTINATION ${CMAKE_INSTALL_PREFIX})

