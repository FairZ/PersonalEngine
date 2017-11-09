cmake_minimum_required(VERSION 2.6)
project(PERSONALENGINE)

# SETTING UP DIRECTORIES

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

if(WIN32)
  include_directories(
    ${PROJECT_SOURCE_DIR}/contrib/msvc/include
  )
  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/msvc/lib
  )
endif()
# END DIRECTORY SETUP


# SETTING UP PERSONAL ENGINE EXE
add_executable(PersonalEngine

  src/PersonalEngine/main.cpp
  src/PersonalEngine/Engine.cpp
  src/PersonalEngine/Window.cpp
  src/PersonalEngine/Input.cpp
  src/PersonalEngine/Component.cpp
  src/PersonalEngine/Entity.cpp
  src/PersonalEngine/Transform.cpp
  src/PersonalEngine/Scene.cpp
  src/PersonalEngine/Camera.cpp
  src/PersonalEngine/Shader.cpp
  src/PersonalEngine/Material.cpp
  src/PersonalEngine/Resource.cpp
  src/PersonalEngine/ResourceManager.cpp
  src/PersonalEngine/Mesh.cpp
  src/PersonalEngine/MeshRenderer.cpp
  src/PersonalEngine/TurnTable.cpp
  src/PersonalEngine/Texture.cpp
  
  #remove for final build:
  #messes with OBJloader
  #src/PersonalEngine/plank.cpp

)

# LINKING NECESSARY Libraries
if(WIN32)
  target_link_libraries(PersonalEngine glew32 freeglut SOIL)
endif()