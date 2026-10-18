cmake_minimum_required(VERSION 4.3)
project(StarsView)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)
find_package(cereal CONFIG REQUIRED)

add_executable(StarsView main.cpp
        Star.h
        Camera.cpp
        Camera.h
        Engine.cpp
        Engine.h
        WindowSettings.h
        StarCatalog.cpp
        StarCatalog.h
        SceneRenderer.cpp
        SceneRenderer.h)

target_link_libraries(StarsView PRIVATE SFML::Graphics SFML::Window SFML::System cereal::cereal)

target_include_directories(StarsView SYSTEM PRIVATE
        $<TARGET_PROPERTY:cereal::cereal,INTERFACE_INCLUDE_DIRECTORIES>
)