if(APPLE)
  cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.12.1 FATAL_ERROR)
endif()

project("safe_drive")

#==================================================================================================#
#  Brings all the MaidSafe libraries into scope as CMake targets.                                  #
#==================================================================================================#
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

include(utils)
#set(SkipReturnCodeValue 127)
#include(standard_setup)

#==================================================================================================#
# Qt library search.                                                                               #
#==================================================================================================#
set(Qt5Required ON)
set(Qt5RequiredVersion 5.3.2)
set(Qt5RequiredLibs
      Qt5Concurrent
      Qt5Core
      Qt5Gui
      Qt5LinguistTools
      Qt5Network
      Qt5Qml
      Qt5Quick
      Qt5Script
      Qt5Svg
      Qt5Widgets)
include(maidsafe_find_qt5)


#==================================================================================================#
# Set up SAFEDrive files as GLOBs.                                                                 #
#==================================================================================================#
set(ProjectSourceDir ${CMAKE_SOURCE_DIR}/003_vfs_drive)
set(UiMain ${ProjectSourceDir}/main.cc)
source_group("Auto Compiled\\Qt MOC Files" FILES "${CMAKE_CURRENT_BINARY_DIR}/safe_drive_automoc.cpp")

ms_glob_dir(Helpers ${ProjectSourceDir}/helpers "Helpers\\\\")

set(QtPchHeader ${ProjectSourceDir}/helpers/qt_push_headers.h)
if(NOT MSVC)
  list(REMOVE_ITEM HelpersSources ${ProjectSourceDir}/helpers/qt_push_headers.cc)
endif()

ms_glob_dir(Controllers ${ProjectSourceDir}/controllers "Controllers\\\\")
ms_glob_dir(Models ${ProjectSourceDir}/models "Models\\\\")

qt5_add_resources(ResourceFilesUiResourcesDir ${ProjectSourceDir}/main_resource.qrc)
source_group("Auto Compiled\\Resource Files" FILES ${ResourceFilesUiResourcesDir})

file(GLOB_RECURSE ViewsAllFiles ${ProjectSourceDir}/views/*.*)
source_group("Views" FILES ${ViewsAllFiles})

set(AllUiSourceFiles
      ${HelpersSources}
      ${ControllersSources}
      ${ModelsSources})
set(AllUiHeaderFiles
      ${HelpersHeaders}
      ${ControllersHeaders}
      ${ModelsHeaders})

#####    Set Application Icon    ####
if(MSVC)
  set(UiAppIconResource ${ProjectSourceDir}/app_icon.rc)
  source_group("Auto Compiled\\App Icon File" FILES ${UiAppIconResource})
endif()

add_executable(${PROJECT_NAME} ${UiMain}
                               ${HelpersAllFiles}
                               ${ControllersAllFiles}
                               ${ModelsAllFiles}
                               ${ResourceFilesUiResourcesDir}
                               ${ViewsAllFiles}
                               ${UiAppIconResource})

target_link_libraries(${PROJECT_NAME} maidsafe_api maidsafe_drive ${Qt5TargetLibs} "-ldl")
if(COMMAND apply_target_properties)  # Available if run from maidsafe-examples root
  apply_target_properties(${PROJECT_NAME})
endif()

if(MSVC)
  set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

#==================================================================================================#
# Set compiler and linker flags.                                                                   #
#==================================================================================================#
include(standard_flags)
target_compile_definitions(${PROJECT_NAME} PRIVATE APPLICATION_NAME=SafeDrive COMPANY_NAME=MaidSafe)

if(MSVC)
  string(REGEX REPLACE "/Zm[0-9]+ " "/Zm500 " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set_source_files_properties(${AllUiSourceFiles} PROPERTIES
                              COMPILE_FLAGS "/Yu\"${QtPchHeader}\" /FI\"${QtPchHeader}\"")
  set_source_files_properties("${ProjectSourceDir}/helpers/qt_push_headers.cc" PROPERTIES
                              COMPILE_FLAGS "/Yc\"${QtPchHeader}\" /FI\"${QtPchHeader}\"")
endif()

#==================================================================================================#
# Generate Qt .pro file.                                                                           #
#==================================================================================================#
set(QtPROHelper ${CMAKE_CURRENT_BINARY_DIR}/safe_drive_mock.pro)
file(WRITE ${QtPROHelper} "#This File is Auto-Generated. Do Not Edit Manually.")
file(APPEND ${QtPROHelper} "\nQT += qml quick widgets")
file(APPEND ${QtPROHelper} "\nTARGET = safe_drive")

file(APPEND ${QtPROHelper} "\n\nSOURCES += ")
set(SourceFilesCollection ${UiMain} ${AllUiSourceFiles})
foreach(SourceFile ${SourceFilesCollection})
  file(APPEND ${QtPROHelper} "$$quote(${SourceFile}) ")
endforeach()

file(APPEND ${QtPROHelper} "\n\nHEADERS += ")
foreach(HeaderFile ${AllUiHeaderFiles})
  file(APPEND ${QtPROHelper} "$$quote(${HeaderFile}) ")
endforeach()

file(APPEND ${QtPROHelper} "\n\nRESOURCES += $$quote(${ProjectSourceDir}/main_resource.qrc)")

if(MSVC)
  ms_get_dependencies(maidsafe_api OptimizedDependencies DebugDependencies ON)
  get_target_property(ReleaseLocation maidsafe_api LOCATION_RELEASE)
  get_target_property(DebugLocation maidsafe_api LOCATION_DEBUG)
  list(INSERT OptimizedDependencies 0 "\"${ReleaseLocation}\"")
  list(INSERT DebugDependencies 0 "\"${DebugLocation}\"")
  file(APPEND ${QtPROHelper} "\n\n*:CONFIG(release, debug|release): LIBS += ")
  foreach(OptimizedDependency ${OptimizedDependencies})
    file(APPEND ${QtPROHelper} "$$quote(${OptimizedDependency}) ")
  endforeach()
  file(APPEND ${QtPROHelper} "\nelse:*:CONFIG(debug, debug|release): LIBS += ")
  foreach(DebugDependency ${DebugDependencies})
    file(APPEND ${QtPROHelper} "$$quote(${DebugDependency}) ")
  endforeach()
endif()

file(APPEND ${QtPROHelper} "\n\nINCLUDEPATH += $$quote(${ProjectSourceDir})")

file(APPEND ${QtPROHelper} "\n\nOTHER_FILES += ")
foreach(ViewFile ${ViewsAllFiles})
  file(APPEND ${QtPROHelper} "$$quote(${ViewFile}) ")
endforeach()
file(GLOB_RECURSE UiFilesResourceContentFiles ${ProjectSourceDir}/resources/*.*)
foreach(UiFilesResourceContentFile ${UiFilesResourceContentFiles})
  file(APPEND ${QtPROHelper} "$$quote(${UiFilesResourceContentFile}) ")
endforeach()
