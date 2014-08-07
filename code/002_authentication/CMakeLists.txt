if(APPLE)
  cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.12.1 FATAL_ERROR)
endif()

project("authentication")

# Including maidsafe_export.cmake brings all the MaidSafe libraries into scope as CMake targets.
find_file(MaidSafeExport NAMES maidsafe_export.cmake
                         PATHS ${MAIDSAFE_BINARY_DIR}
                         NO_DEFAULT_PATH)
if(NOT MaidSafeExport)
  set(ErrorMessage "\n\nCan't find maidsafe_export.cmake in MAIDSAFE_BINARY_DIR.  ")
  set(ErrorMessage "${ErrorMessage}Currently MAIDSAFE_BINARY_DIR is set to ")
  set(ErrorMessage "${ErrorMessage}\"${MAIDSAFE_BINARY_DIR}\"  It must be set to the MaidSafe ")
  set(ErrorMessage "${ErrorMessage}super-project's build root.\nTo set it, run:\n")
  set(ErrorMessage "${ErrorMessage}    cmake . -DMAIDSAFE_BINARY_DIR=\"<path to build root>\"\n\n")
  message(FATAL_ERROR "${ErrorMessage}")
endif()
include(${MaidSafeExport})

add_executable(${PROJECT_NAME} main.cc)
ms_underscores_to_camel_case(${PROJECT_NAME} AppName)
set_target_properties(${PROJECT_NAME} PROPERTIES PROJECT_LABEL ${AppName} FOLDER "Examples")
target_link_libraries(${PROJECT_NAME} maidsafe_api)
