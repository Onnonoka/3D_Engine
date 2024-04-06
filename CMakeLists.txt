cmake_minimum_required(VERSION 3.0)
project(OpenGLProject)

# Define build paths for different build types
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BIN_DIR ${BUILD_DIR}/bin)

# Path for build type-specific files
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_DIR "Debug")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    set(BUILD_TYPE_DIR "Release")
endif()

# # Enable all warnings for gcc or clang compiler
# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# endif()

# # Enable all warnings for MSVC compiler
# if (MSVC)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
# endif()

set(TEMP_DIR ${BUILD_DIR}/temp)

# Create directories if they don't exist
file(MAKE_DIRECTORY ${TEMP_DIR})
file(MAKE_DIRECTORY ${BIN_DIR})

# Source files location
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Header files location
set(OPENGL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/OpenGL/include)
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes/Engine)

# List of source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/OpenGL/src/*.c"
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/Engine/Core/*.cpp"
    "${SOURCE_DIR}/Engine/Core/Error/*.cpp"
    "${SOURCE_DIR}/Engine/Renderer/*.cpp"
    "${SOURCE_DIR}/Engine/Camera/*.cpp"
    "${SOURCE_DIR}/Engine/Object3D/*.cpp"
    "${SOURCE_DIR}/Engine/Object3D/Sample/*.cpp"
    "${SOURCE_DIR}/Engine/Material/*.cpp"
)

# Output path for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${ENGINE_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/lib/libglfw3dll.a)

# Copy glfw3.dll to the bin directory during compilation
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/lib/glfw3.dll DESTINATION ${BIN_DIR}/${BUILD_TYPE_DIR})
# Copy Media and Shaders
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Media DESTINATION ${BIN_DIR}/${BUILD_TYPE_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/Shaders DESTINATION ${BIN_DIR}/${BUILD_TYPE_DIR}/Engine)
