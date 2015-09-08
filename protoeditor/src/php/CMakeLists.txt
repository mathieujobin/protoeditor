
include_directories(${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/php/dbg ${CMAKE_SOURCE_DIR}/src/php/gubed ${CMAKE_SOURCE_DIR}/src/php/xdebug ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(dbg)
add_subdirectory(gubed)
add_subdirectory(xdebug)


########### next target ###############

set(phplang_STAT_SRCS phpsettings.cpp phpsettingswidget.cpp)

kde4_add_library(phplang STATIC ${phplang_STAT_SRCS})


