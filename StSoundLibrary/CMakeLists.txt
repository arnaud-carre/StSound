set(PROJECT_NAME StSoundLibrary)

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
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "StSoundLibrary"
    TARGET_NAME_RELEASE "StSoundLibrary"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/./Debug"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/./Release"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebug
    >
    $<$<CONFIG:Release>:
        MultiThreaded
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "WIN32;"
    "_LIB;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            /ZI
        >
        $<$<CONFIG:Release>:
            /O2;
            /Ob1;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /NOLOGO
    )
endif()

