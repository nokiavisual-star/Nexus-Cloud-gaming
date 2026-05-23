#ifndef CLOUD_STORAGE_H
#define CLOUD_STORAGE_H

#include <string>
#include <map>
#include <vector>
#include <memory>

struct SaveData {
    std::string game_id;
    std::string user_id;
    std::string data;
    std::string timestamp;
    std::string device;
};

class CloudStorage {
public:
    CloudStorage();
    ~CloudStorage();
    
    bool save_game_progress(const std::string& user_id, const std::string& game_id,
                            const std::string& save_data, const std::string& device);
    bool load_game_progress(const std::string& user_id, const std::string& game_id,
                            std::string& out_data);
    
    bool sync_progress(const std::string& user_id);
    bool delete_save(const std::string& user_id, const std::string& game_id);
    
    std::vector<SaveData> get_all_saves(const std::string& user_id) const;
    
private:
    std::map<std::string, std::vector<SaveData>> user_saves_;
    
    std::string get_current_timestamp();
};

#endif
