This is a minimal real-time WebSocket server written in C++ using the WebSocket++ library. It supports multiple clients and allows broadcasting messages between them, useful for collaborative editors


## Features
  Real-time message broadcasting between connected clients
  
  Built using WebSocket++ and standalone ASIO
  
  JSON support with nlohmann/json
  
  Thread-safe with mutex locking

## Prerequisites (mac)
  brew install cmake asio websocketpp nlohmann-json

## Windows
  git clone https://github.com/microsoft/vcpkg
  cd vcpkg
  ./bootstrap-vcpkg.sh  # or bootstrap-vcpkg.bat on Windows
  ./vcpkg install websocketpp asio nlohmann-json


## Clone the repo
  git clone https://github.com/aadarshraj4321/c_plus_plus_real_time_code_editor_websocket.git
    
  go inisde the folder
  open terminal
  enter command:
  cmake -B build -S .
  cmake --build build
  ./build/server
  open the index.html file and connect multiple clients

