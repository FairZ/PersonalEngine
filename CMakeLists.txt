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
  src/PersonalEngine/Engine.h
  src/PersonalEngine/Window.cpp
  src/PersonalEngine/Window.h
  src/PersonalEngine/Input.cpp
  src/PersonalEngine/Input.h
  src/PersonalEngine/Component.cpp
  src/PersonalEngine/Component.h
  src/PersonalEngine/Entity.cpp
  src/PersonalEngine/Entity.h
  src/PersonalEngine/Transform.cpp
  src/PersonalEngine/Transform.h
  src/PersonalEngine/Scene.cpp
  src/PersonalEngine/Scene.h
  src/PersonalEngine/Camera.cpp
  src/PersonalEngine/Camera.h
  src/PersonalEngine/Shader.cpp
  src/PersonalEngine/Shader.h
  src/PersonalEngine/Material.cpp
  src/PersonalEngine/Material.h
  src/PersonalEngine/Resource.cpp
  src/PersonalEngine/Resource.h
  src/PersonalEngine/ResourceManager.cpp
  src/PersonalEngine/ResourceManager.h
  src/PersonalEngine/Mesh.cpp
  src/PersonalEngine/Mesh.h
  src/PersonalEngine/MeshRenderer.cpp
  src/PersonalEngine/MeshRenderer.h
  src/PersonalEngine/TurnTable.cpp
  src/PersonalEngine/TurnTable.h
  src/PersonalEngine/Texture.cpp
  src/PersonalEngine/Texture.h
  src/PersonalEngine/RenderController.cpp
  src/PersonalEngine/RenderController.h
  src/PersonalEngine/Time.cpp
  src/PersonalEngine/Time.h
  src/PersonalEngine/RigidBody.cpp
  src/PersonalEngine/RigidBody.h
  src/PersonalEngine/FlyingController.cpp
  src/PersonalEngine/FlyingController.h
  src/PersonalEngine/Collider.cpp
  src/PersonalEngine/Collider.h
  src/PersonalEngine/Jetpack.cpp
  src/PersonalEngine/JetPack.h
  src/PersonalEngine/SphereCollider.cpp
  src/PersonalEngine/SphereCollider.h
  src/PersonalEngine/CollisionResolver.cpp
  src/PersonalEngine/CollisionResolver.h
  src/PersonalEngine/Contact.cpp
  src/PersonalEngine/Contact.h
  
  #remove for final build:
  #src/PersonalEngine/plank.cpp

)

# LINKING NECESSARY Libraries
if(WIN32)
  target_link_libraries(PersonalEngine glew32 freeglut SOIL assimp)
endif()