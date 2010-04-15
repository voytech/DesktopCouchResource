SET(
	TESTS  
	cmdline_tester
)
SET(
        HELPERS
        test
    
)
##### Probably don't want to edit below this line ##### 

# Find Qt4
FIND_PACKAGE( Qt4 REQUIRED )

# Pick modules
SET( QT_DONT_USE_QTGUI TRUE )
SET( QT_USE_QTTEST TRUE )

# Use it
INCLUDE( ${QT_USE_FILE} )

# Include the library include directories, and the current build directory (moc)
INCLUDE_DIRECTORIES(
	../lib
        ../desktop_couch
	${CMAKE_CURRENT_BINARY_DIR}
)


# Build the tests
 INCLUDE(AddFileDependencies)
# FOREACH(test ${TESTS})
	#MESSAGE(STATUS "Building ${test}")
 MESSAGE(STATUS "Building ${TESTS}")       
	QT4_WRAP_CPP(MOC_SOURCE ${TESTS}.cpp)
        QT4_WRAP_CPP(MOC_SOURCE2 ${HELPERS}.h)      
	ADD_EXECUTABLE(
		${TESTS}
		${TESTS}.cpp
                ${HELPERS}.cpp 
                ${MOC_SOURCE2}
	)       
	ADD_FILE_DEPENDENCIES(${TESTS}.cpp ${MOC_SOURCE})
	
        TARGET_LINK_LIBRARIES(
		${TESTS}
		${QT_LIBRARIES}
		#couchdb-qt
                desktop_couch
	)
# ENDFOREACH()

