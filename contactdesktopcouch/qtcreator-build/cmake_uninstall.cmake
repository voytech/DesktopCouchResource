IF(NOT EXISTS "/media/storage/PROGRAMMING/MasterThesis/DesktopCouchResource/contactdesktopcouch/qtcreator-build/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/media/storage/PROGRAMMING/MasterThesis/DesktopCouchResource/contactdesktopcouch/qtcreator-build/install_manifest.txt\"")
ENDIF(NOT EXISTS "/media/storage/PROGRAMMING/MasterThesis/DesktopCouchResource/contactdesktopcouch/qtcreator-build/install_manifest.txt")

FILE(READ "/media/storage/PROGRAMMING/MasterThesis/DesktopCouchResource/contactdesktopcouch/qtcreator-build/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"${file}\"")
  IF(EXISTS "${file}")
    EXEC_PROGRAM(
      "/usr/bin/cmake" ARGS "-E remove \"${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF("${rm_retval}" STREQUAL 0)
    ELSE("${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"${file}\"")
    ENDIF("${rm_retval}" STREQUAL 0)
  ELSE(EXISTS "${file}")
    MESSAGE(STATUS "File \"${file}\" does not exist.")
  ENDIF(EXISTS "${file}")
ENDFOREACH(file)
