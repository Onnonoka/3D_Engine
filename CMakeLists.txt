cmake_minimum_required(VERSION 3.0)
project(OpenGLProject)

# Définition des chemins de construction pour les types de build
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BIN_DIR ${BUILD_DIR}/bin)

# Chemin pour les fichiers spécifiques au type de build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_DIR "Debug")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    set(BUILD_TYPE_DIR "Release")
endif()

set(TEMP_DIR ${BUILD_DIR}/temp)

# Création des répertoires s'ils n'existent pas déjà
file(MAKE_DIRECTORY ${TEMP_DIR})
file(MAKE_DIRECTORY ${BIN_DIR})

# Emplacement des fichiers sources
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Emplacement des fichiers d'en-tête
set(OPENGL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/OpenGL/include)
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes/Engine)

# Liste des fichiers source
set(SOURCES
    # lib sources files
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/OpenGL/src/glad.c
    # main
    ${SOURCE_DIR}/main.cpp
    # Engine Error
    ${SOURCE_DIR}/Engine/Error/EngineError.cpp
    # Engine Basic
    ${SOURCE_DIR}/Engine/Basic/Window.cpp
    ${SOURCE_DIR}/Engine/Basic/FPSCounter.cpp
    ${SOURCE_DIR}/Engine/Basic/Color.cpp
    ${SOURCE_DIR}/Engine/Basic/Dirty.cpp
    # Engine Renderer
    ${SOURCE_DIR}/Engine/Renderer/Renderer.cpp
    ${SOURCE_DIR}/Engine/Renderer/MinimalRenderer.cpp
    # Engine Object3D
    ${SOURCE_DIR}/Engine/Object3D/BasicObject.cpp
    ${SOURCE_DIR}/Engine/Object3D/Point.cpp
    ${SOURCE_DIR}/Engine/Object3D/Face.cpp
    ${SOURCE_DIR}/Engine/Object3D/Geometry.cpp
    ${SOURCE_DIR}/Engine/Object3D/Object3D.cpp
    ${SOURCE_DIR}/Engine/Object3D/Camera.cpp
    ${SOURCE_DIR}/Engine/Object3D/SimpleObject/Cube.cpp
    # Engine Material
    ${SOURCE_DIR}/Engine/Material/Material.cpp
)

# Chemin de sortie pour les binaires
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Inclure les en-têtes
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${ENGINE_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

# Liaison des bibliothèques
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/lib/libglfw3dll.a)

# Copier glfw3.dll dans le répertoire bin lors de la compilation
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/lib/glfw3.dll DESTINATION ${BIN_DIR}/${BUILD_TYPE_DIR})
# Copier les Media and Shaders
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Media DESTINATION ${BIN_DIR}/${BUILD_TYPE_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/Shaders DESTINATION ${BIN_DIR}/${BUILD_TYPE_DIR}/Engine)
