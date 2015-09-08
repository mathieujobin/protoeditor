
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/common/php ${CMAKE_SOURCE_DIR}/src/dbg ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(dbgprofiler_STAT_SRCS
    dbgprofilelocation.cpp
    dbgprofiledata.cpp
    dbgprofiledialog.cpp
    dbgprofilelistview.cpp)

kde4_add_library(dbgprofiler STATIC ${dbgprofiler_STAT_SRCS})

