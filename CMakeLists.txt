cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)

project(StSound CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang|AppleClang)")
    add_compile_options(-Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "(MSVC)")
    add_compile_options(/W4)
endif()

################################################################################
# Common utils
################################################################################
include(CheckLinkerFlag)
include(GNUInstallDirs)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(SmallYmPlayer)
add_subdirectory(StSoundLibrary)
add_subdirectory(Ym2Wav)

enable_testing()

file(GLOB YM_SAMPLE_FILES "${PROJECT_SOURCE_DIR}/YmSampleFiles/*.ym" "${PROJECT_SOURCE_DIR}/YmSampleFiles/*.YM")
if(NOT YM_SAMPLE_FILES)
    message(SEND_ERROR "No YM sample files found")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/tests")
foreach(ym_path IN LISTS YM_SAMPLE_FILES)
    get_filename_component(ym_name "${ym_path}" NAME)
    string(MAKE_C_IDENTIFIER "${ym_name}" ym_name_ident)
    get_filename_component(ym_name_we "${ym_path}" NAME_WE)
    add_test(NAME "${ym_name_ident}-Ym2Wav" COMMAND Ym2Wav ${ym_path} "${CMAKE_CURRENT_BINARY_DIR}/${ym_name_we}.wav")
endforeach()
