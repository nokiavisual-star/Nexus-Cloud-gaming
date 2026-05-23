cmake_minimum_required(VERSION 3.16)
project(NexusCloudGaming)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(NexusCloudGaming
    src/main.cpp
    src/server/streaming_server.cpp
    src/server/game_manager.cpp
    src/core/auth_manager.cpp
    src/core/cloud_storage.cpp
    src/client/input_handler.cpp
)

# Включить директории
target_include_directories(NexusCloudGaming PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

# Поиск необходимых пакетов
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

# Линковка библиотек
target_link_libraries(NexusCloudGaming
    OpenSSL::SSL OpenSSL::Crypto
    CURL::libcurl
    pthread
)

# Флаги оптимизации
if(MSVC)
    target_compile_options(NexusCloudGaming PRIVATE /W4 /O2)
else()
    target_compile_options(NexusCloudGaming PRIVATE -Wall -Wextra -O2)
endif()
