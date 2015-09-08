
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/python ${CMAKE_SOURCE_DIR}/src/python/pythondbgp ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(pythondbgp_STAT_SRCS
    debuggerpythondbgp.cpp
    pythondbgpnet.cpp
    pythondbgpsettings.cpp
    pythondbgpsettingswidget.cpp
    pythondbgpvariableparser.cpp)

kde4_add_library(pythondbgp STATIC ${pythondbgp_STAT_SRCS})

