project(contactdesktopcouch)

# search packages used by KDE
find_package (KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)
include(CheckIncludeFiles)
find_package (KdepimLibs  REQUIRED)
find_package( Boost REQUIRED )

find_program(XSLTPROC_EXECUTABLE xsltproc)
macro_log_feature(XSLTPROC_EXECUTABLE "xsltproc" "The command line XSLT processor from libxslt" "http://xmlsoft.org/XSLT/" FALSE "" "Needed for building Akonadi resources. Recommended.")


#temporary then it would be find***.cmake file
find_library( COUCHDBQT_LIBRARY
    NAMES
    couchdb-qt
    PATHS
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

find_path (COUCHDBQT_INCLUDE_DIR
    NAMES
    couchdb-qt.h
    PATH_SUFFIXES
    couchdb-qt
    PATHS
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
  )
find_library( DESKTOPCOUCH_LIBRARY
    NAMES
    desktop-couch-qt
    PATHS
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)
find_path (DESKTOPCOUCH_INCLUDE_DIR
    NAMES
    desktop_couch.h
    PATH_SUFFIXES
    desktop-couch-qt
    PATHS
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
  )
# these are includes that are never used,
# but the compiler still needs it
find_path (QTCRYPTO
    NAMES
    QtCrypto
    PATH_SUFFIXES
    QtCrypto
    PATHS
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
  )
find_path (GLIB_INCLUDES
    NAMES
    glib.h
    PATH_SUFFIXES
    glib-2.0
    PATHS
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
  )
# end of strange includes declaration

if (XSLTPROC_EXECUTABLE)
  # generates a D-Bus interface description from a KConfigXT file
  macro( kcfg_generate_dbus_interface _kcfg _name )
    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_name}.xml
      COMMAND ${XSLTPROC_EXECUTABLE} --stringparam interfaceName ${_name}
              ${KDEPIMLIBS_DATA_DIR}/akonadi-kde/kcfg2dbus.xsl
              ${_kcfg}
              > ${CMAKE_CURRENT_BINARY_DIR}/${_name}.xml
      DEPENDS ${KDEPIMLIBS_DATA_DIR}/akonadi-kde/kcfg2dbus.xsl
              ${_kcfg}
    )
  endmacro( kcfg_generate_dbus_interface )
endif (XSLTPROC_EXECUTABLE)

if(WIN32)
    set(LIB_INSTALL_DIR ${LIB_INSTALL_DIR}
                        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
                        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
                        ARCHIVE DESTINATION ${LIB_INSTALL_DIR} )
endif(WIN32)

set(KDE4_ICON_DIR ${KDE4_INSTALL_DIR}/share/icons)

include_directories(
    ${kdepim-runtime_SOURCE_DIR}
    ${QT_QTDBUS_INCLUDE_DIR}
    ${kdepim-runtime_BINARY_DIR}
    ${AKONADI_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
    ${KDE4_INCLUDES}
    ${KDEPIMLIBS_INCLUDE_DIRS}
    ${COUCHDBQT_INCLUDE_DIR}
    ${DESKTOPCOUCH_INCLUDE_DIR}
    ${QTCRYPTO}
    ${GLIB_INCLUDES}
    /usr/lib/glib-2.0/include
)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}" )


########### next target ###############

set( contactdesktopcouchresource_SRCS
  contactdesktopcouchresource.cpp
  mapper.cpp
)

install( FILES contactdesktopcouchresource.desktop DESTINATION "${CMAKE_INSTALL_PREFIX}/share/akonadi/agents" )

kde4_add_kcfg_files(contactdesktopcouchresource_SRCS settings.kcfgc)
kcfg_generate_dbus_interface(${CMAKE_CURRENT_SOURCE_DIR}/contactdesktopcouchresource.kcfg org.kde.Akonadi.ContactDesktopCouch.Settings)
qt4_add_dbus_adaptor(contactdesktopcouchresource_SRCS
  ${CMAKE_CURRENT_BINARY_DIR}/org.kde.Akonadi.ContactDesktopCouch.Settings.xml settings.h Settings
)

kde4_add_executable(akonadi_contactdesktopcouch_resource RUN_UNINSTALLED ${contactdesktopcouchresource_SRCS})

target_link_libraries(akonadi_contactdesktopcouch_resource
    ${KDE4_AKONADI_LIBS}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTDBUS_LIBRARY}
    ${KDE4_KDECORE_LIBS}
    ${KDEPIMLIBS_AKONADI_LIBS}
    ${KDE4_KABC_LIBRARY}
    ${COUCHDBQT_LIBRARY}
    ${DESKTOPCOUCH_LIBRARY}
)

install(TARGETS akonadi_contactdesktopcouch_resource ${INSTALL_TARGETS_DEFAULT_ARGS})
