
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/php ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${CMAKE_SOURCE_DIR}/src/php/xdebug ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(xdebug_STAT_SRCS
    xdsettings.cpp
    xdsettingswidget.cpp
    debuggerxd.cpp
    xdnet.cpp
    xdvariableparser.cpp)

kde4_add_library(xdebug STATIC ${xdebug_STAT_SRCS})


