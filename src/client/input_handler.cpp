#include "input_handler.h"
#include <iostream>
#include <algorithm>

InputHandler::InputHandler() : gamepad_connected_(false) {
}

InputHandler::~InputHandler() {
}

void InputHandler::initialize() {
    std::cout << "[InputHandler] Инициализация обработчика ввода..." << std::endl;
    std::cout << "[InputHandler] Поддержка: Клавиатура, Мышь, Геймпад, Сенсорный ввод" << std::endl;
}

void InputHandler::process_input(const InputEvent& event) {
    std::string input_type;
    switch(event.type) {
        case InputType::KEYBOARD:
            input_type = "Клавиатура";
            break;
        case InputType::MOUSE:
            input_type = "Мышь";
            break;
        case InputType::GAMEPAD:
            input_type = "Геймпад";
            break;
        case InputType::TOUCH:
            input_type = "Сенсор";
            break;
    }
    
    std::cout << "[Input] " << input_type << ": " << event.key 
              << " (" << (event.pressed ? "НАЖАТО" : "ОТПУЩЕНО") << ")" << std::endl;
    
    // Вызываем все зарегистрированные callback-ы
    for (auto& callback : input_callbacks_) {
        callback(event);
    }
}

void InputHandler::register_input_callback(std::function<void(const InputEvent&)> callback) {
    input_callbacks_.push_back(callback);
}

bool InputHandler::is_gamepad_connected() const {
    return gamepad_connected_;
}

void InputHandler::poll_gamepad_input() {
    std::cout << "[InputHandler] Опрос геймпада..." << std::endl;
    gamepad_connected_ = true;
}
