cmake_minimum_required(VERSION 3.15)
project(CollaborativeEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)

find_library(BOOST_SYSTEM_LIBRARY NAMES boost_system REQUIRED)

add_executable(server server.cpp)

target_compile_definitions(server PRIVATE ASIO_STANDALONE)

target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(server PRIVATE ${BOOST_SYSTEM_LIBRARY} nlohmann_json::nlohmann_json)
