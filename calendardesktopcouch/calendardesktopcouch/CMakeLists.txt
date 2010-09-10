project(calendardesktopcouch)

# search packages used by KDE
find_package (KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)
include(CheckIncludeFiles)
find_package (KdepimLibs REQUIRED)

find_program(XSLTPROC_EXECUTABLE xsltproc)
macro_log_feature(XSLTPROC_EXECUTABLE "xsltproc" "The command line XSLT processor from libxslt" "http://xmlsoft.org/XSLT/" FALSE "" "Needed for building Akonadi resources. Recommended.")

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
find_library(QLOG_LIBRARY
     NAMES
     QLog
     PATHS
     ${LIB_INSTALL_DIR}
     ${KDE4_LIB_DIR}
)
find_path( QLOG_INCLUDE_DIR
    NAMES
    QLog.h
    PATH_SUFFIXES
    #QLog
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
    ${QLOG_INCLUDE_DIR}
    ${DESKTOPCOUCH_INCLUDE_DIR}
    ${QTCRYPTO}
    ${GLIB_INCLUDES}
    /usr/lib/glib-2.0/include

)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}" )


########### next target ###############

set( calendardesktopcouchresource_SRCS
  calendardesktopcouchresource.cpp
  incidencemapper.cpp
)

install( FILES calendardesktopcouchresource.desktop DESTINATION "${CMAKE_INSTALL_PREFIX}/share/akonadi/agents" )

kde4_add_kcfg_files(calendardesktopcouchresource_SRCS settings.kcfgc)
kcfg_generate_dbus_interface(${CMAKE_CURRENT_SOURCE_DIR}/calendardesktopcouchresource.kcfg org.kde.Akonadi.calendardesktopcouch.Settings)
qt4_add_dbus_adaptor(calendardesktopcouchresource_SRCS
  ${CMAKE_CURRENT_BINARY_DIR}/org.kde.Akonadi.calendardesktopcouch.Settings.xml settings.h Settings
)

kde4_add_executable(akonadi_calendardesktopcouch_resource RUN_UNINSTALLED ${calendardesktopcouchresource_SRCS})

target_link_libraries(akonadi_calendardesktopcouch_resource ${KDE4_AKONADI_LIBS} 
							    ${QT_QTCORE_LIBRARY}
                                                            ${QT_QTDBUS_LIBRARY}
                                                            ${KDE4_KDECORE_LIBS}
							    ${KDEPIMLIBS_AKONADI_LIBS}
                                                            ${KDE4_KIO_LIBS}
                                                            #${KDE4_KABC_LIBRARY}
                                                            ${KDEPIMLIBS_KCAL_LIBS}
							    ${COUCHDBQT_LIBRARY}
                                                            ${QLOG_LIBRARY}
							    ${DESKTOPCOUCH_LIBRARY}
)

install(TARGETS akonadi_calendardesktopcouch_resource ${INSTALL_TARGETS_DEFAULT_ARGS})
