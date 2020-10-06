cmake_minimum_required(VERSION 3.14)
project(Centipede)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Bullet.cpp Bullet.h Player.cpp Player.h Collision.cpp Collision.h Mushroom.cpp Mushroom.h Animation.cpp Animation.h Head.cpp Head.h )
add_executable(Centipede ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Centipede sfml-system sfml-window sfml-graphics sfml-audio sfml-network)