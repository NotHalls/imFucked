cmake_minimum_required(VERSION 3.24)

project(imClient)


#settings up dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/objs/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin/objs/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")

find_package(Vulkan REQUIRED)

# setting up files
file(GLOB_RECURSE CLIENT_SOURCES "src/*.cpp")
file(GLOB_RECURSE STB_SOURCES
    "../submodules/stb/*.cpp" "../submodules/stb/*.c")


# making the exec
add_executable(${PROJECT_NAME} ${CLIENT_SOURCES} ${STB_SOURCES})


# adding submodules
add_subdirectory(../submodules/sdl ../submodules/build)

add_library(imgui STATIC
    ../submodules/imgui/imconfig.h
    ../submodules/imgui/imgui.h
    ../submodules/imgui/imgui.cpp
    ../submodules/imgui/imgui_draw.cpp
    ../submodules/imgui/imgui_internal.h
    ../submodules/imgui/imgui_tables.cpp
    ../submodules/imgui/imgui_widgets.cpp
    ../submodules/imgui/imstb_rectpack.h
    ../submodules/imgui/imstb_textedit.h
    ../submodules/imgui/imstb_truetype.h
    ../submodules/imgui/imgui_demo.cpp

    ../submodules/imgui/backends/imgui_impl_sdl3.cpp
    ../submodules/imgui/backends/imgui_impl_vulkan.cpp
)
target_include_directories(imgui PUBLIC
    ../submodules/imgui
    ../submodules/sdl/include
    ${Vulkan_INCLUDE_DIR}
)


# linking libs
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Vulkan_LIBRARIES}
    SDL3::SDL3
    imgui

    imShared
)


# spesifying compile definitions based on the build type
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Debug>:IMF_BUILD_DEBUG>)
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Release>:IMF_BUILD_RELEASE>)
target_compile_definitions(${PROJECT_NAME}
    PUBLIC $<$<CONFIG:Export>:IMF_BUILD_EXPORT>)


# includes
target_include_directories(${PROJECT_NAME} PUBLIC
    ${Vulkan_INCLUDE_DIR}
    ../submodules/sdl/include
    ../submodules/glm/glm
    ../submodules/imgui
    ../submodules/stb

    ../imShared/src
    src
)