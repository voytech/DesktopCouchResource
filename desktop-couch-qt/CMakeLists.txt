FIND_PACKAGE(GLIB2)
if (GLIB2_FOUND) 
  message("GLIB2 FOUND \n")
endif(GLIB2_FOUND)
set(ALL_INCLUDES 
                 #/usr/include/glib-2.0
                 #/usr/lib/glib-2.0/include  
		 ./ 
                 ../lib           
                 ${GLIB_INCLUDE_DIRS}
                 ${GNOME_KEYRING_INCLUDE_DIRS}
) 
#                 /usr/include/gnome-keyring-1 
#                 /usr/include/glib-2.0
#                 /usr/lib/glib-2.0/include)
                       
#include_directories(./)
#include_directories(../lib)
#include_directories(${GNOME_KEYRING_INCLUDE_DIRS}) 
#include_directories(${GLIB_INCLUDE_DIRS})
#include_directories(/usr/include/gnome-keyring-1)
#include_directories(/usr/include/glib-2.0) 
#include_directories(/usr/lib/glib-2.0/include) 

include_directories(${ALL_INCLUDES}) 

install(FILES
        desktop_couch.h
        DESTINATION include/desktopcouch
)
set(DESKTOPCOUCH_MOC_HDRS
    desktop_couch.h   
)
#We are setting path to 
set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})

qt4_wrap_cpp(DESKTOPCOUCH_MOC_SRCS ${DESKTOPCOUCH_MOC_HDRS})

set (DESKTOPCOUCH_SRCS
  desktop_couch.cpp 
)

add_library (desktop_couch SHARED ${DESKTOPCOUCH_SRCS} ${DESKTOPCOUCH_MOC_SRCS})

target_link_libraries( desktop_couch ${QT_LIBRARIES} ${QJSON_LIBRARIES} ${GNOME_KEYRING_LIBRARIES} ${GLIB2_LIBRARIES} couchdb-qt /usr/lib/libqoauth.so /usr/lib/libglib-2.0.so)

set_target_properties( desktop_couch PROPERTIES
     VERSION ${DESKTOPCOUCH_LIB_MAJOR_VERSION}.${DESKTOPCOUCH_LIB_MINOR_VERSION}.${DESKTOPCOUCH_LIB_PATCH_VERSION}
     SOVERSION ${DESKTOPCOUCH_LIB_MAJOR_VERSION}
     DEFINE_SYMBOL DESKTOPCOUCH_MAKEDLL
)

install(TARGETS desktop_couch EXPORT  LIBRARY DESTINATION ${LIB_INSTALL_DIR} ${INSTALL_TARGETS_DEFAULT_ARGS})