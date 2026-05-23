#include "cloud_storage.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>

CloudStorage::CloudStorage() {
}

CloudStorage::~CloudStorage() {
}

bool CloudStorage::save_game_progress(const std::string& user_id, 
                                      const std::string& game_id,
                                      const std::string& save_data,
                                      const std::string& device) {
    SaveData new_save;
    new_save.game_id = game_id;
    new_save.user_id = user_id;
    new_save.data = save_data;
    new_save.timestamp = get_current_timestamp();
    new_save.device = device;
    
    user_saves_[user_id].push_back(new_save);
    
    std::cout << "[CloudStorage] Сохранено для пользователя " << user_id 
              << " игра " << game_id << " с устройства " << device << std::endl;
    
    return true;
}

bool CloudStorage::load_game_progress(const std::string& user_id,
                                      const std::string& game_id,
                                      std::string& out_data) {
    auto it = user_saves_.find(user_id);
    if (it == user_saves_.end()) {
        std::cerr << "[CloudStorage] Сохранения для пользователя не найдены: " << user_id << std::endl;
        return false;
    }
    
    for (const auto& save : it->second) {
        if (save.game_id == game_id) {
            out_data = save.data;
            std::cout << "[CloudStorage] Загружено сохранение для " << game_id << std::endl;
            return true;
        }
    }
    
    std::cerr << "[CloudStorage] Сохранение для игры не найдено: " << game_id << std::endl;
    return false;
}

bool CloudStorage::sync_progress(const std::string& user_id) {
    std::cout << "[CloudStorage] Синхронизация прогресса для пользователя " 
              << user_id << std::endl;
    return true;
}

bool CloudStorage::delete_save(const std::string& user_id, const std::string& game_id) {
    auto it = user_saves_.find(user_id);
    if (it == user_saves_.end()) {
        return false;
    }
    
    auto& saves = it->second;
    saves.erase(
        std::remove_if(saves.begin(), saves.end(),
                       [&game_id](const SaveData& s) { return s.game_id == game_id; }),
        saves.end()
    );
    
    std::cout << "[CloudStorage] Удалено сохранение для " << game_id << std::endl;
    return true;
}

std::vector<SaveData> CloudStorage::get_all_saves(const std::string& user_id) const {
    auto it = user_saves_.find(user_id);
    if (it != user_saves_.end()) {
        return it->second;
    }
    return std::vector<SaveData>();
}

std::string CloudStorage::get_current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
