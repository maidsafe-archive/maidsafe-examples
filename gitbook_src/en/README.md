# MaidSafe-Examples

Welcome to the MaidSafe Examples GitBook. This book provides a walkthrough to get started with the SAFE network and its API project.

## Localisation

If you wish to add translation for this book in another language, please submit a pull request to the [github project for MaidSafe-Examples](https://github.com/maidsafe/maidsafe-examples/) on the master branch.

## Setting up a new project with MaidSafe libs:

MaidSafe-super project comes with a bunch of utility libs such as cli(command-line tool helper) sfml and qt, along with the native maidsafe libs. If you’re starting a new project, the following instructions should help you get your project setup with ease and link against these tools.

Firstly you would need to follow the Build instructions for your corresponding platform to get the Super project setup. With this out of the way all we need is to create a folder for this new project with a CMakeLists.txt file such as:

    cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)

    set(ProjectName "my_project")
    project(${ProjectName})

#===================================================================#
#  Brings all the MaidSafe libraries into scope as CMake targets.                                                  #
#===================================================================#
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


The above code requires that cmake for this project be run with: “-DMAIDSAFE_BINARY_DIR=<path to MaidSafe super project build folder>” and it will accordingly import all of the MaidSafe targets into the new project’s scope to link against.



So in the new project if we have a main.cc that we want to link against the API project, all we need to add extra to this CMakeLists.txt file would be:

    add_executable(${ProjectName} main.cc)
    target_link_libraries(${ProjectName} maidsafe_api)


That’s it for the entire CMakeLists.txt file. You can now choose to link against any of your required libs from the super project and get your project going. Good luck!!!

All MaidSafe-Examples that come with code snippets use this approach to link to their required libs.
