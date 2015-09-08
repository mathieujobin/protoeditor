
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/python ${CMAKE_SOURCE_DIR}/src/python ${CMAKE_SOURCE_DIR}/src/python/pythondbgp ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(pythondbgp)


########### next target ###############

set(pythonlang_STAT_SRCS pythonsettings.cpp pythonsettingswidget.cpp)

kde4_add_library(pythonlang STATIC ${pythonlang_STAT_SRCS})

