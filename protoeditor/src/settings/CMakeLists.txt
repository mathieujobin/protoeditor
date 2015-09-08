
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/settings ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(widgets)


########### next target ###############

set(settings_STAT_SRCS
    protoeditorsettings.cpp
    extappsettings.cpp
    sitesettings.cpp
    languagesettings.cpp)

kde4_add_library(settings STATIC ${settings_STAT_SRCS})


