#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

struct GameInfo {
    std::string id;
    std::string title;
    std::string description;
    std::string genre;
    std::string developer;
    std::string icon_url;
    float rating;
    bool is_running;
};

class GameManager {
public:
    GameManager();
    ~GameManager();
    
    void initialize_game_library();
    GameInfo get_game_info(const std::string& game_id) const;
    std::vector<GameInfo> get_all_games() const;
    std::vector<GameInfo> search_games(const std::string& query) const;
    
    bool start_game(const std::string& game_id, const std::string& user_id);
    bool stop_game(const std::string& game_id, const std::string& user_id);
    
    int get_total_games_count() const;
    
private:
    std::map<std::string, GameInfo> game_library_;
    std::map<std::string, std::vector<std::string>> running_games_;
    
    void load_default_games();
};

#endif
