set(PROJECT_NAME StSoundLibrary)

if(NOT WIN32 AND NOT APPLE)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/dummy.sym" "{\n global: *;\n};\n")
    check_linker_flag(CXX "-Wl,--version-script=${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/dummy.sym" HAVE_WL_VERSION_SCRIPT)
endif()

################################################################################
# Source groups
################################################################################
set(Headers
    "digidrum.h"
    "LZH/LZH.H"
    "StSoundLibrary.h"
    "Ym2149Ex.h"
    "YmLoad.h"
    "YmMusic.h"
    "YmTypes.h"
)

source_group("Headers" FILES ${Headers})

set(Sources
    "digidrum.cpp"
    "LZH/LzhLib.cpp"
    "Ym2149Ex.cpp"
    "Ymload.cpp"
    "YmMusic.cpp"
    "YmUserInterface.cpp"
)
if(WIN32)
    list(APPEND Sources "stsound.def")
endif()
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_library(StSoundLibrary STATIC ${ALL_FILES})

if(WIN32)
    set_property(TARGET StSoundLibrary PROPERTY PREFIX "")
endif()
if(BUILD_SHARED_LIBS AND HAVE_WL_VERSION_SCRIPT)
    target_link_options(StSoundLibrary PRIVATE "-Wl,--version-script,${CMAKE_CURRENT_SOURCE_DIR}/stsound.sym")
    set_property(TARGET StSoundLibrary APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/stsound.sym")
endiF()

install(TARGETS StSoundLibrary EXPORT StSound-exports
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
install(FILES "StSoundLibrary.h" "YmTypes.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
install(EXPORT StSound-exports DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/StSound/StSoundConfig.cmake")
