    katedocwrapper.cpp)

kde4_add_plugin(katescriptdebuggerplugin ${katescriptdebuggerplugin_PART_SRCS})

target_link_libraries(katescriptdebuggerplugin ${KDE4_KDECORE_LIBS} protoeditor kateinterfaces kdeui)

install(TARGETS katescriptdebuggerplugin DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install(FILES  ui.rc DESTINATION share/apps/kate/plugins/katescriptdebugger)
install(FILES  katescriptdebugger.desktop DESTINATION share/services)


