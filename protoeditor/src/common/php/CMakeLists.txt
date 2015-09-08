
include_directories(${CMAKE_SOURCE_DIR}/src/common ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(commonphp_STAT_SRCS phpvariable.cpp phpvariableparser.cpp)

kde4_add_library(commonphp STATIC ${commonphp_STAT_SRCS})

