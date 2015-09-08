
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/perl ${CMAKE_SOURCE_DIR}/src/perl ${CMAKE_SOURCE_DIR}/src/perl/perldb ${CMAKE_SOURCE_DIR}/src/perl/perldbgp ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(perldbgp)


########### next target ###############

set(perllang_STAT_SRCS perlsettings.cpp perlsettingswidget.cpp)

kde4_add_library(perllang STATIC ${perllang_STAT_SRCS})

