
################################################################################
# Source groups
################################################################################
set(Sources
    "Ym2Wav.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(Ym2Wav ${ALL_FILES})

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(Ym2Wav PRIVATE
    StSoundLibrary
)

install(TARGETS Ym2Wav
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

