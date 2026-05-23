#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
#include <map>
#include <memory>

struct User {
    std::string id;
    std::string username;
    std::string email;
    std::string password_hash;
    bool verified;
    std::string last_login;
};

class AuthManager {
public:
    AuthManager();
    ~AuthManager();
    
    bool register_user(const std::string& username, const std::string& email, 
                       const std::string& password);
    bool login_user(const std::string& email, const std::string& password);
    bool logout_user(const std::string& user_id);
    bool verify_token(const std::string& token) const;
    
    User get_user(const std::string& user_id) const;
    std::string generate_token(const std::string& user_id);
    
private:
    std::map<std::string, User> users_;
    std::map<std::string, std::string> active_tokens_;
    
    std::string hash_password(const std::string& password);
    std::string generate_user_id();
    std::string generate_random_token();
};

#endif
