#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>
#include <functional>

enum class InputType {
    KEYBOARD,
    MOUSE,
    GAMEPAD,
    TOUCH
};

struct InputEvent {
    InputType type;
    std::string key;
    float x;
    float y;
    bool pressed;
};

class InputHandler {
public:
    InputHandler();
    ~InputHandler();
    
    void initialize();
    void process_input(const InputEvent& event);
    
    void register_input_callback(std::function<void(const InputEvent&)> callback);
    
    bool is_gamepad_connected() const;
    void poll_gamepad_input();
    
private:
    std::vector<std::function<void(const InputEvent&)>> input_callbacks_;
    bool gamepad_connected_;
};

#endif
