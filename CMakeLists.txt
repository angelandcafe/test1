cmake_minimum_required(VERSION 3.3)
project(osd_tests)

include(../Common.cmake)

set(PREFIX_HEADER_FILE ${PROJECT_SOURCE_DIR}/../PrefixHeader.pch)

# FIXME: This is considered a CMake anti-pattern, because the resulting build
# rules can't tell when files have been added to or removed from the project.
# If we explicitly list the sources we want to build, we avoid that problem,
# and the build system can re-invoke `cmake` only when necessary.
file(GLOB_RECURSE SOURCE_FILES *.cpp ${PROJECT_SOURCE_DIR}/../PrefixHeader.pch)

list(APPEND ALL_TEST_PROGRAMS
  configure_test
  command_test
  home_coordinator_unit_test
  command_center_test
)

add_executable(configure_test configure_test.cpp)
add_executable(command_test command_test.cpp)
add_executable(home_coordinator_unit_test home_coordinator_unit_test.cpp)
add_executable(command_center_test command_center_test.cpp)



##### Boilerplate below:

find_path(ATF_INCLUDE_DIR atf-c++.hpp)
find_library(ATFC++ atf-c++ REQUIRED)

foreach(testprogram IN LISTS ALL_TEST_PROGRAMS)
  target_link_libraries(${testprogram} ${ATFC++})

  set(WARNFLAGS "-Wall -Werror -Wno-unknown-pragmas -Wno-unused-local-typedefs -Wno-deprecated-register")
  set_target_properties(${testprogram} PROPERTIES COMPILE_FLAGS "-include ${PREFIX_HEADER_FILE} ${WARNFLAGS}")

  target_include_directories(${testprogram} SYSTEM PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/..
    ${PROJECT_SOURCE_DIR}/../middleware
    ${PROJECT_SOURCE_DIR}/../middleware/src
    ${PROJECT_SOURCE_DIR}/../ui/presto
    ${ATF_INCLUDE_DIR}
  )

  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND OUR_FRAMEWORKS
      Foundation IOKit OpenGL AGL AppKit CoreVideo AVFoundation IOSurface
      CoreMedia VideoToolbox QuartzCore)

    foreach(fwk IN LISTS OUR_FRAMEWORKS)
      find_library(FWK_${fwk} ${fwk})
      target_link_libraries(${testprogram} ${FWK_${fwk}})
    endforeach()
  endif()

  find_package(jetpack_foundation REQUIRED)
  find_package(jetpack_iokit REQUIRED)
  find_package(jetpack_graphics REQUIRED)
  find_package(jetpack_glkit REQUIRED)
  find_package(jetpack_layerkit REQUIRED)
  find_package(jetpack_appkit REQUIRED)

  target_link_libraries(${testprogram}
    jetpack_foundation jetpack_iokit jetpack_graphics jetpack_glkit
    jetpack_layerkit jetpack_appkit)

  target_link_libraries(${testprogram} fuse)
endforeach()
