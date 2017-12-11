cmake_minimum_required(VERSION 2.6)
project(FairEngine)

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
add_executable(FairEngine

  src/FairEngine/main.cpp
  src/FairEngine/Engine.cpp
  src/FairEngine/Engine.h
  src/FairEngine/Window.cpp
  src/FairEngine/Window.h
  src/FairEngine/Input.cpp
  src/FairEngine/Input.h
  src/FairEngine/Component.cpp
  src/FairEngine/Component.h
  src/FairEngine/Entity.cpp
  src/FairEngine/Entity.h
  src/FairEngine/Transform.cpp
  src/FairEngine/Transform.h
  src/FairEngine/Scene.cpp
  src/FairEngine/Scene.h
  src/FairEngine/Camera.cpp
  src/FairEngine/Camera.h
  src/FairEngine/Shader.cpp
  src/FairEngine/Shader.h
  src/FairEngine/Material.cpp
  src/FairEngine/Material.h
  src/FairEngine/Resource.cpp
  src/FairEngine/Resource.h
  src/FairEngine/ResourceManager.cpp
  src/FairEngine/ResourceManager.h
  src/FairEngine/Mesh.cpp
  src/FairEngine/Mesh.h
  src/FairEngine/MeshRenderer.cpp
  src/FairEngine/MeshRenderer.h
  src/FairEngine/TurnTable.cpp
  src/FairEngine/TurnTable.h
  src/FairEngine/Texture.cpp
  src/FairEngine/Texture.h
  src/FairEngine/RenderController.cpp
  src/FairEngine/RenderController.h
  src/FairEngine/Time.cpp
  src/FairEngine/Time.h
  src/FairEngine/RigidBody.cpp
  src/FairEngine/RigidBody.h
  src/FairEngine/FlyingController.cpp
  src/FairEngine/FlyingController.h
  src/FairEngine/Collider.cpp
  src/FairEngine/Collider.h
  src/FairEngine/Jetpack.cpp
  src/FairEngine/JetPack.h
  src/FairEngine/SphereCollider.cpp
  src/FairEngine/SphereCollider.h
  src/FairEngine/CollisionResolver.cpp
  src/FairEngine/CollisionResolver.h
  src/FairEngine/Contact.cpp
  src/FairEngine/Contact.h
  src/FairEngine/Light.cpp
  src/FairEngine/Light.h
  src/FairEngine/FlashLight.cpp
  src/FairEngine/FlashLight.h
  src/FairEngine/Gun.cpp
  src/FairEngine/Gun.h
  src/FairEngine/Bullet.h
  src/FairEngine/Bullet.cpp
  src/FairEngine/BulletBehaviour.h
  src/FairEngine/BulletBehaviour.cpp
  src/FairEngine/Asteroid.h
  src/FairEngine/Asteroid.cpp
  src/FairEngine/Sound.h
  src/FairEngine/Sound.cpp
  src/FairEngine/AudioSource.h
  src/FairEngine/AudioSource.cpp
)

# LINKING NECESSARY Libraries
if(WIN32)
  target_link_libraries(FairEngine glew32 freeglut SOIL assimp openal libogg libvorbis libvorbisfile)
endif()