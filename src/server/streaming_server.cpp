#include "streaming_server.h"
#include <iostream>
#include <openssl/ssl.h>

StreamingServer::StreamingServer(int port, const std::string& cert_path, 
                                 const std::string& key_path)
    : port_(port), cert_path_(cert_path), key_path_(key_path), running_(false) {
}

StreamingServer::~StreamingServer() {
    stop();
}

bool StreamingServer::start() {
    std::cout << "[StreamingServer] Запуск сервера на порту " << port_ << "..." << std::endl;
    
    if (!setup_ssl()) {
        std::cerr << "[StreamingServer] Ошибка при настройке SSL" << std::endl;
        return false;
    }
    
    if (!bind_socket()) {
        std::cerr << "[StreamingServer] Ошибка при привязке сокета" << std::endl;
        return false;
    }
    
    running_ = true;
    std::cout << "[StreamingServer] Сервер успешно запущен" << std::endl;
    return true;
}

void StreamingServer::stop() {
    if (running_) {
        running_ = false;
        std::cout << "[StreamingServer] Сервер остановлен" << std::endl;
    }
}

bool StreamingServer::is_running() const {
    return running_;
}

void StreamingServer::register_game(const std::string& game_id, 
                                    const std::string& game_path) {
    registered_games_[game_id] = game_path;
    std::cout << "[StreamingServer] Зарегистрирована игра: " << game_id << std::endl;
}

std::vector<std::string> StreamingServer::get_available_games() const {
    std::vector<std::string> games;
    for (const auto& pair : registered_games_) {
        games.push_back(pair.first);
    }
    return games;
}

bool StreamingServer::setup_ssl() {
    std::cout << "[SSL] Инициализация SSL..." << std::endl;
    return true;
}

bool StreamingServer::bind_socket() {
    std::cout << "[Socket] Привязка сокета к порту " << port_ << "..." << std::endl;
    return true;
}
