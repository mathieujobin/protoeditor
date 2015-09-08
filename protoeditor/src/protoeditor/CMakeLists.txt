
include_directories(${CMAKE_SOURCE_DIR}/. ${CMAKE_SOURCE_DIR}/src/common ${CMAKE_SOURCE_DIR}/src/perl ${CMAKE_SOURCE_DIR}/src/perl/perldb ${CMAKE_SOURCE_DIR}/src/perl/perldbgp ${CMAKE_SOURCE_DIR}/src/php ${CMAKE_SOURCE_DIR}/src/php/dbg ${CMAKE_SOURCE_DIR}/src/php/gubed ${CMAKE_SOURCE_DIR}/src/php/xdebug ${CMAKE_SOURCE_DIR}/src/protoeditor ${CMAKE_SOURCE_DIR}/src/protoeditor/ui ${CMAKE_SOURCE_DIR}/src/python ${CMAKE_SOURCE_DIR}/src/settings ${CMAKE_SOURCE_DIR}/src/settings/widgets ${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )

add_subdirectory(ui)


########### next target ###############

set(protoeditor_STAT_SRCS
    debuggerfactory.cpp
    protoeditor.cpp
    executioncontroller.cpp
    datacontroller.cpp
    uinterface.cpp
    editorinterface.cpp
    debuggerinterface.cpp
    main.cpp)

kde4_add_library(protoeditor STATIC ${protoeditor_STAT_SRCS})


########### next target ###############

set(protoeditor_SRCS ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)

kde4_add_executable(protoeditor ${protoeditor_SRCS})

target_link_libraries(protoeditor ${KDE4_KDECORE_LIBS})

install(TARGETS protoeditor ${INSTALL_TARGETS_DEFAULT_ARGS})


########### install files ###############

install(FILES  protoeditor.desktop DESTINATION share/applnk/Development)
install(FILES  protoeditorui.rc DESTINATION share/apps/protoeditor)

