#external
include(FetchContent)
include(imgui)
include(glfw)
include(glad2)
include(stb)
include(glm)
include(assimp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(base STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
)

target_include_directories(base PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(base PUBLIC
  glfw
  glad
  stb
  glm::glm
  imgui::imgui
  assimp::assimp
)