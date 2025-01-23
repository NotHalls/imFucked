cmake_minimum_required(VERSION 3.24)


# setting the build type
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug"
            CACHE STRING "Build Type (Debug, Release, Export)" FORCE)
endif()
# the configuration types may be useful for project generators
# with multi build configs setup like msbuild
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Export"
    CACHE STRING "Available Build Configurations")


project(imFucked)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# defining the platofrms
if(WIN32)
    add_compile_definitions(IMF_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(IMF_PLATFORM_UNIX)
elseif(UNIX AND APPLE)
    add_compile_definitions(IMF_PLATFORM_MACOS)
elseif(ANDROID)
    add_compile_definitions(IMF_PLATFORM_ANDROID)
endif()


# headless or normal
if(NOT IMF_BUILD)
    set(IMF_BUILD "Client"
        CACHE STRING "Build Type (Client, Headless)" FORCE)
endif()

if(IMF_BUILD STREQUAL "Headless")
    add_compile_definitions(IMF_HEADLESS)
endif()


# settings some flags up for different build types
if(CMAKE_CXX_COMPILER_ID STREQUAL
  "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_EXPORT "-O2 -g")
elseif(MSVC)
    # we need as many warnings as possible
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /W4 /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "/02 /DNDEBUG")
    set(CMAKE_CXX_FLAGS_EXPORT "/02 /DNDEBUG")
else()
    message(WARNING "Unknown compiler. Defaulting to generic settings.")
    # Usual fallback flags
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_EXPORT "-O2 -g")
endif()


# sub-projects
if(IMF_BUILD STREQUAL "Client")
    add_subdirectory(imClient)
    add_subdirectory(imShared)
elseif(IMF_BUILD STREQUAL "Headless")
    add_subdirectory(imServer)
    add_subdirectory(imShared)
endif()


# setting up the startup project for VS
if(IMF_BUILD STREQUAL "Client")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT imClient)
elseif(IMF_BUILD STREQUAL "Headless")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT imServer)
endif()