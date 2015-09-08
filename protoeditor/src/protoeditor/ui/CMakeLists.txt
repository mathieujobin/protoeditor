
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${CMAKE_SOURCE_DIR}/src/settings/widgets ${CMAKE_SOURCE_DIR}/src/protoeditor/ui ${CMAKE_SOURCE_DIR}/src/common ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(ui_STAT_SRCS
    debuggerui.cpp
    breakpointlistview.cpp
    breakpointlistviewitem.cpp
    combostack.cpp
    document.cpp
    editorui.cpp
    localtab.cpp
    mainwindow.cpp
    messagelistview.cpp
    variablelistview.cpp
    variablelistviewitem.cpp
    watchlistview.cpp
    watchtab.cpp
    statusbarwidget.cpp
    consolewidget.cpp)

kde4_add_library(ui STATIC ${ui_STAT_SRCS})

