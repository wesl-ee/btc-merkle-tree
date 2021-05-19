project(btc-merkle-tree)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic -Wstrict-aliasing -Werror)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)

# Main executable
add_executable(btc-merkle-tree)
include_directories(include)
target_sources(btc-merkle-tree PUBLIC
	src/MerkleNode.cc
	src/MerkleTree.cc
	src/NodeHash.cc
	src/main.cc
)
target_link_libraries(btc-merkle-tree crypto)
