#include "game_manager.h"
#include <iostream>
#include <algorithm>

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::initialize_game_library() {
    std::cout << "[GameManager] Инициализация библиотеки игр..." << std::endl;
    load_default_games();
}

void GameManager::load_default_games() {
    // Загрузка примеров AAA игр
    game_library_["cyberpunk2077"] = {
        "cyberpunk2077", "Cyberpunk 2077", 
        "Научно-фантастический экшн-RPG от CD Projekt Red",
        "RPG", "CD Projekt Red", "/icons/cyberpunk2077.png", 8.5f, false
    };
    
    game_library_["elden_ring"] = {
        "elden_ring", "Elden Ring",
        "Действие разворачивается в мрачной фантастике от FromSoftware",
        "Action RPG", "FromSoftware", "/icons/elden_ring.png", 9.0f, false
    };
    
    game_library_["baldurs_gate_3"] = {
        "baldurs_gate_3", "Baldur's Gate 3",
        "Мощный сюжетный RPG от Larian Studios",
        "RPG", "Larian Studios", "/icons/baldurs_gate_3.png", 9.5f, false
    };
    
    // Инди-игры
    game_library_["hollow_knight"] = {
        "hollow_knight", "Hollow Knight",
        "Классический metroidvania, один из лучших инди-проектов",
        "Platformer", "Team Cherry", "/icons/hollow_knight.png", 9.2f, false
    };
    
    game_library_["stardew_valley"] = {
        "stardew_valley", "Stardew Valley",
        "Спокойный фермерский симулятор с огромной глубиной",
        "Simulation", "ConcernedApe", "/icons/stardew_valley.png", 9.1f, false
    };
    
    game_library_["hades"] = {
        "hades", "Hades",
        "Roguelike экшн с потрясающим стилем от Supergiant Games",
        "Roguelike", "Supergiant Games", "/icons/hades.png", 9.3f, false
    };
    
    // Дополнять можно бесконечно - здесь только примеры из 5000
    std::cout << "[GameManager] Загружено " << game_library_.size() << " игр" << std::endl;
}

GameInfo GameManager::get_game_info(const std::string& game_id) const {
    auto it = game_library_.find(game_id);
    if (it != game_library_.end()) {
        return it->second;
    }
    return GameInfo{"", "", "", "", "", "", 0.0f, false};
}

std::vector<GameInfo> GameManager::get_all_games() const {
    std::vector<GameInfo> games;
    for (const auto& pair : game_library_) {
        games.push_back(pair.second);
    }
    return games;
}

std::vector<GameInfo> GameManager::search_games(const std::string& query) const {
    std::vector<GameInfo> results;
    std::string lower_query = query;
    std::transform(lower_query.begin(), lower_query.end(), 
                   lower_query.begin(), ::tolower);
    
    for (const auto& pair : game_library_) {
        std::string title = pair.second.title;
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        
        if (title.find(lower_query) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

bool GameManager::start_game(const std::string& game_id, const std::string& user_id) {
    std::cout << "[GameManager] Запуск игры " << game_id << " для пользователя " 
              << user_id << std::endl;
    
    auto it = game_library_.find(game_id);
    if (it == game_library_.end()) {
        std::cerr << "[GameManager] Игра не найдена: " << game_id << std::endl;
        return false;
    }
    
    running_games_[user_id].push_back(game_id);
    it->second.is_running = true;
    
    return true;
}

bool GameManager::stop_game(const std::string& game_id, const std::string& user_id) {
    std::cout << "[GameManager] Остановка игры " << game_id << std::endl;
    
    auto it = game_library_.find(game_id);
    if (it != game_library_.end()) {
        it->second.is_running = false;
    }
    
    return true;
}

int GameManager::get_total_games_count() const {
    return game_library_.size();
}
