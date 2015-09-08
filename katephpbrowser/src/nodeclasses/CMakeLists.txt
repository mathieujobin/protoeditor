
include_directories(${CMAKE_SOURCE_DIR}/src/parser ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(nodes_STAT_SRCS browsernode.cpp)

kde4_add_library(nodes STATIC ${nodes_STAT_SRCS})


