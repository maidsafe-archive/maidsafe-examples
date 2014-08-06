if(APPLE)
  cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.12.1 FATAL_ERROR)
endif()

project("maidsafe-examples")

file(GLOB SubDirs "${CMAKE_SOURCE_DIR}/*")
foreach(SubDir ${SubDirs})
  if(IS_DIRECTORY "${SubDir}")
    add_subdirectory("${SubDir}")
  endif()
endforeach()
