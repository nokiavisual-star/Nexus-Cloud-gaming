#include "auth_manager.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <openssl/sha.h>

AuthManager::AuthManager() {
}

AuthManager::~AuthManager() {
}

bool AuthManager::register_user(const std::string& username, const std::string& email,
                                const std::string& password) {
    // Проверка, не существует ли уже пользователь с такой почтой
    for (const auto& pair : users_) {
        if (pair.second.email == email) {
            std::cerr << "[Auth] Пользователь с такой почтой уже зарегистрирован" << std::endl;
            return false;
        }
    }
    
    User new_user;
    new_user.id = generate_user_id();
    new_user.username = username;
    new_user.email = email;
    new_user.password_hash = hash_password(password);
    new_user.verified = false;
    new_user.last_login = "";
    
    users_[new_user.id] = new_user;
    std::cout << "[Auth] Пользователь зарегистрирован: " << username << " (" << new_user.id << ")" << std::endl;
    
    return true;
}

bool AuthManager::login_user(const std::string& email, const std::string& password) {
    for (auto& pair : users_) {
        if (pair.second.email == email) {
            if (pair.second.password_hash == hash_password(password)) {
                pair.second.last_login = std::to_string(
                    std::chrono::system_clock::now().time_since_epoch().count()
                );
                std::cout << "[Auth] Пользователь вошел: " << email << std::endl;
                return true;
            }
        }
    }
    
    std::cerr << "[Auth] Неверный пароль или почта: " << email << std::endl;
    return false;
}

bool AuthManager::logout_user(const std::string& user_id) {
    auto it = active_tokens_.find(user_id);
    if (it != active_tokens_.end()) {
        active_tokens_.erase(it);
        std::cout << "[Auth] Пользователь вышел: " << user_id << std::endl;
        return true;
    }
    return false;
}

bool AuthManager::verify_token(const std::string& token) const {
    return active_tokens_.find(token) != active_tokens_.end();
}

User AuthManager::get_user(const std::string& user_id) const {
    auto it = users_.find(user_id);
    if (it != users_.end()) {
        return it->second;
    }
    return User{"", "", "", "", false, ""};
}

std::string AuthManager::generate_token(const std::string& user_id) {
    std::string token = generate_random_token();
    active_tokens_[token] = user_id;
    return token;
}

std::string AuthManager::hash_password(const std::string& password) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, password.c_str(), password.length());
    SHA1_Final(hash, &sha1);
    
    std::stringstream ss;
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        ss << std::hex << (int)hash[i];
    }
    return ss.str();
}

std::string AuthManager::generate_user_id() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    return "user_" + std::to_string(dis(gen));
}

std::string AuthManager::generate_random_token() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::stringstream ss;
    
    for(int i = 0; i < 32; i++) {
        ss << std::hex << dis(gen);
    }
    return ss.str();
}
