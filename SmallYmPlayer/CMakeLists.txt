################################################################################
# Source groups
################################################################################
set(Headers
    "SoundServer.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "SmallYmPlayer.cpp"
    "SoundServer.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(SmallYmPlayer ${ALL_FILES})

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(SmallYmPlayer PRIVATE
    StSoundLibrary
)

if(WIN32)
    target_link_libraries(SmallYmPlayer PRIVATE winmm)
endif()

install(TARGETS SmallYmPlayer
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

