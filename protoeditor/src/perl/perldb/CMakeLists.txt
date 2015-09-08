
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/perl ${CMAKE_SOURCE_DIR}/src/perl ${CMAKE_SOURCE_DIR}/src/perl/perldb ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(perldb_STAT_SRCS
    perldebugger.cpp
    perldebuggersettings.cpp
    perldebuggersettingswidget.cpp
    perllocalcom.cpp)

kde4_add_library(perldb STATIC ${perldb_STAT_SRCS})

