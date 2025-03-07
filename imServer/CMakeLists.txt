cmake_minimum_required(VERSION 3.24)

project(imServer)


#settings up dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/objs/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/objs/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")


# files
file(GLOB_RECURSE SERVER_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SERVER_SOURCES})


# linking
target_link_libraries(${PROJECT_NAME} PRIVATE imShared)


# spesifying compile definitions based on the build type
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Debug>:IMF_BUILD_DEBUG>)
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Release>:IMF_BUILD_RELEASE>)
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Export>:IMF_BUILD_EXPORT>)


# setting up the PreCompiled Header
set(PCH_HEADER "src/pch.hpp")
set(PCH_SOURCE "src/pch.cpp")
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_HEADER})


target_include_directories(${PROJECT_NAME} PUBLIC
    ../submodules/glm/glm

    ../imShared/src
    src
)