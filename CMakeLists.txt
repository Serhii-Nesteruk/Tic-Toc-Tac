cmake_minimum_required(VERSION 3.0)

project(ClientServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SFML_DIR "C:/Users/shdh3/Desktop/Tic-tac-tok/dependencies/SFML-2.6.x/include/SFML") #TODO: fix

add_subdirectory(dependencies/SFML-2.6.x)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Server
	server.cpp
    Block.h 
	Block.cpp
	Game.h
	Game.cpp
	ClientNetworkManager.h 
	ClientNetworkManager.cpp
	ServerNetworkManager.h
	ServerNetworkManager.cpp
)

target_link_libraries(Server PUBLIC wsock32 ws2_32)

add_executable(Client
	client.cpp
    Block.h 
	Block.cpp
	Game.h
	Game.cpp
    ClientNetworkManager.h 
	ClientNetworkManager.cpp
	ServerNetworkManager.h
	ServerNetworkManager.cpp
)

target_link_libraries(Client PUBLIC wsock32 ws2_32)

target_link_libraries(Server PUBLIC sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(Client PUBLIC sfml-graphics sfml-window sfml-system sfml-network)
