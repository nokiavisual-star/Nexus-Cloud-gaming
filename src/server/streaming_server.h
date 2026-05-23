#ifndef STREAMING_SERVER_H
#define STREAMING_SERVER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class StreamingServer {
public:
    StreamingServer(int port, const std::string& cert_path, const std::string& key_path);
    ~StreamingServer();
    
    bool start();
    void stop();
    bool is_running() const;
    
    void register_game(const std::string& game_id, const std::string& game_path);
    std::vector<std::string> get_available_games() const;
    
private:
    int port_;
    std::string cert_path_;
    std::string key_path_;
    bool running_;
    std::map<std::string, std::string> registered_games_;
    
    bool setup_ssl();
    bool bind_socket();
};

#endif
