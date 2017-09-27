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


# SETTING UP INDIGO ENGINE LIB
add_executable(PersonalEngine

  src/PersonalEngine/main.cpp
  src/PersonalEngine/Engine.cpp  

)

# LINKING NECESSARY DLLs
if(WIN32)
  target_link_libraries(PersonalEngine glew32 freeglut)
endif()