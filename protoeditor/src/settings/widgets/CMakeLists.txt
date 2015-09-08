
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(settingswidget_STAT_SRCS
    configdlg.cpp
    sitesettingsdialog.cpp
    sitesettingswidget.cpp
    extappsettingswidget.cpp)

kde4_add_library(settingswidget STATIC ${settingswidget_STAT_SRCS})


