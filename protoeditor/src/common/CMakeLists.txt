
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(php)
add_subdirectory(perl)
add_subdirectory(python)


########### next target ###############

set(common_STAT_SRCS
    abstractdebugger.cpp
    debuggerbreakpoint.cpp
    variable.cpp
    debuggerstack.cpp
    connection.cpp
    session.cpp)

kde4_add_library(common STATIC ${common_STAT_SRCS})


