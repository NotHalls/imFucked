cmake_minimum_required(VERSION 3.24)

project(imShared)


#settings up dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/objs/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/objs/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")


# setting up files
file(GLOB_RECURSE SHARED_SOURCES "src/*.cpp")


# making exec
add_library(${PROJECT_NAME} STATIC ${SHARED_SOURCES})


# spesifying compile definitions based on the build type
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Debug>:IMF_BUILD_DEBUG>)
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Release>:IMF_BUILD_RELEASE>)
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Export>:IMF_BUILD_EXPORT>)


# includes
target_include_directories(${PROJECT_NAME} PUBLIC
    ../submodules/glm/glm

    src
)


# for client
if(IMF_BUILD STREQUAL "Client")
    find_package(Vulkan REQUIRED)
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${Vulkan_INCLUDE_DIR}
        ../submodules/sdl/include
        ../submodules/imgui
        ../submodules/stb
    )
endif()