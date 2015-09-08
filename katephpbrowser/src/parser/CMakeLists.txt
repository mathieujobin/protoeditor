
include_directories(${CMAKE_SOURCE_DIR}/src/nodeclasses ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(phpparser_STAT_SRCS phpbrowserparser.cpp PHPAST.cpp)

kde4_add_library(phpparser STATIC ${phpparser_STAT_SRCS})


