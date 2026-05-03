set(SOURCES main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(run_exe ${SOURCES})
set_target_properties(run_exe PROPERTIES COMPILE_WARNING_AS_ERROR ON)