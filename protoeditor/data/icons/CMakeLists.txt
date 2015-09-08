
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### install files ###############

install(FILES  DESTINATION share/apps/protoeditor/icons)

kde4_install_icons(${ICON_INSTALL_DIR})


