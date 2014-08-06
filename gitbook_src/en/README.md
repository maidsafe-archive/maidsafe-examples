# MaidSafe-Examples

Welcome to the MaidSafe Examples GitBook. This book provides a walkthrough to get started with the SAFE network and its API project.

## Localisation

If you wish to add a translation for this book in another language, please submit a pull request to the [github project for MaidSafe-Examples](https://github.com/maidsafe/maidsafe-examples/) on the master branch.

## Setting up a new project with MaidSafe libs:

MaidSafe Super-Project comes with many utility libraries such as CLI (command-line tool helper) SFML (low level graphics) and Qt (cross platform C++ UI based applications with widgets), along with the native MaidSafe libraries. If you’re starting a new project, the following instructions should help you get your project set up with ease and link against these tools.

Firstly you would need to follow the Build Instructions for [Linux](https://github.com/maidsafe/MaidSafe/wiki/Build-Instructions-for-Linux) / [OS X](https://github.com/maidsafe/MaidSafe/wiki/Build-Instructions-for-OS-X) / [Windows](https://github.com/maidsafe/MaidSafe/wiki/Build-Instructions-for-Windows) to get the Super-Project set up. With this out of the way we need to create a folder for this new project with a `CMakeLists.txt` file such as:

    cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)
    project("my_project")

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


CMake for this project needs to be run with: `-DMAIDSAFE_BINARY_DIR=<path to MaidSafe Super-Project build folder>`. This will import all the MaidSafe targets into the new project’s scope to link against.



To link against the API project, we need to add the following:

    add_executable(${PROJECT_NAME} main.cc)
    target_link_libraries(${PROJECT_NAME} maidsafe_api)


You can now choose to link against any of your required libraries from the Super-Project and get your project going. Good luck!

All MaidSafe-Examples that come with code snippets use this approach to link to their required libraries.
