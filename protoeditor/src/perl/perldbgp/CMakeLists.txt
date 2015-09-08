
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/perl ${CMAKE_SOURCE_DIR}/src/perl/perldbgp ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(perldbgp_STAT_SRCS
    debuggerperldbgp.cpp
    perldbgpnet.cpp
    perldbgpsettings.cpp
    perldbgpsettingswidget.cpp
    perldbgpvariableparser.cpp)

kde4_add_library(perldbgp STATIC ${perldbgp_STAT_SRCS})


