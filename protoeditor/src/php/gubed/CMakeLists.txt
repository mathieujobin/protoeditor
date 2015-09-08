
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/php ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${CMAKE_SOURCE_DIR}/src/php/gubed ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(gubed_STAT_SRCS
    gbsettings.cpp
    gbsettingswidget.cpp
    gbnet.cpp
    debuggergb.cpp)

kde4_add_library(gubed STATIC ${gubed_STAT_SRCS})

