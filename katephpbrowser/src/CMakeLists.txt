
include_directories(${CMAKE_SOURCE_DIR}/src/nodeclasses ${CMAKE_SOURCE_DIR}/src/parser ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(parser)
add_subdirectory(nodeclasses)


########### next target ###############

set(katephpbrowserplugin_PART_SRCS
    plugin_katephpbrowser.cpp
    browsertab.cpp
    browserlistview.cpp
    schemaconfigurationdlg.cpp
    schemasettings.cpp
    schema.cpp
    browserloader.cpp
    browserlistviewitem.cpp)

kde4_add_plugin(katephpbrowserplugin ${katephpbrowserplugin_PART_SRCS})

target_link_libraries(katephpbrowserplugin ${KDE4_KDECORE_LIBS} phpparser nodes antlr kateinterfaces)

install(TARGETS katephpbrowserplugin DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install(FILES  DESTINATION share/apps/kate/plugins/katephpbrowser)
install(FILES  katephpbrowser.desktop DESTINATION share/services)

