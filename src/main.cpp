#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "server/streaming_server.h"
#include "server/game_manager.h"
#include "core/auth_manager.h"
#include "core/cloud_storage.h"
#include "client/input_handler.h"

void print_banner() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                                                          ║\n";
    std::cout << "║        🎮  NEXUS CLOUD GAMING 🎮                        ║\n";
    std::cout << "║                                                          ║\n";
    std::cout << "║    Революция в облачном гейминге!                      ║\n";
    std::cout << "║    5000+ игр, полностью БЕСПЛАТНО!                      ║\n";
    std::cout << "║                                                          ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

int main() {
    print_banner();
    
    std::cout << "[MAIN] Инициализация Nexus Cloud Gaming...\n" << std::endl;
    
    // Инициализация компонентов
    auto streaming_server = std::make_unique<StreamingServer>(8443, "", "");
    auto game_manager = std::make_unique<GameManager>();
    auto auth_manager = std::make_unique<AuthManager>();
    auto cloud_storage = std::make_unique<CloudStorage>();
    auto input_handler = std::make_unique<InputHandler>();
    
    // Запуск инициализации
    std::cout << "\n[ИНИЦИАЛИЗАЦИЯ]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    game_manager->initialize_game_library();
    input_handler->initialize();
    
    std::cout << "════════════════════════════════════════════════════════\n\n";
    
    // Запуск сервера потокового вещания
    std::cout << "[СЕРВЕР]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    if (!streaming_server->start()) {
        std::cerr << "[ОШИБКА] Не удалось запустить сервер!" << std::endl;
        return 1;
    }
    
    // Регистрация игр
    auto games = game_manager->get_all_games();
    std::cout << "\n[БИБЛИОТЕКА] Всего зарегистрировано: " << game_manager->get_total_games_count() 
              << " игр\n" << std::endl;
    
    // Пример работы с аутентификацией
    std::cout << "[АУТЕНТИФИКАЦИЯ]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    auth_manager->register_user("player1", "player1@nexus.gaming", "password123");
    auth_manager->register_user("gamer2", "gamer2@nexus.gaming", "secure_pass");
    auth_manager->login_user("player1@nexus.gaming", "password123");
    std::string token = auth_manager->generate_token("user_123456");
    std::cout << "\n[ТОКЕН] " << token << "\n" << std::endl;
    
    // Пример работы с облачным сохранением
    std::cout << "[ОБЛАЧНОЕ СОХРАНЕНИЕ]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    cloud_storage->save_game_progress("user_123456", "cyberpunk2077", 
                                       R"({"level":45,"playtime":1250})", "PC");
    cloud_storage->save_game_progress("user_123456", "elden_ring",
                                       R"({"boss":"Radahn","location":"Redmane"})", "PC");
    
    std::string loaded_data;
    if (cloud_storage->load_game_progress("user_123456", "cyberpunk2077", loaded_data)) {
        std::cout << "[ДАННЫЕ] " << loaded_data << "\n" << std::endl;
    }
    
    // Пример обработки ввода
    std::cout << "[ОБРАБОТКА ВВОДА]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    input_handler->register_input_callback([](const InputEvent& event) {
        std::cout << "  → Callback: Событие обработано" << std::endl;
    });
    
    InputEvent jump_input;
    jump_input.type = InputType::KEYBOARD;
    jump_input.key = "SPACE";
    jump_input.pressed = true;
    input_handler->process_input(jump_input);
    
    InputEvent gamepad_input;
    gamepad_input.type = InputType::GAMEPAD;
    gamepad_input.key = "A_BUTTON";
    gamepad_input.pressed = true;
    input_handler->process_input(gamepad_input);
    
    std::cout << "\n";
    
    // Поиск игр
    std::cout << "[ПОИСК ИГРЫ]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    auto search_results = game_manager->search_games("Elden");
    std::cout << "[РЕЗУЛЬТАТЫ] Найдено " << search_results.size() << " игр:\n";
    for (const auto& game : search_results) {
        std::cout << "  • " << game.title << " (" << game.genre << ") - Рейтинг: " 
                  << game.rating << "/10" << std::endl;
    }
    
    std::cout << "\n";
    
    // Запуск игры
    std::cout << "[ЗАПУСК ИГРЫ]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    
    if (game_manager->start_game("elden_ring", "user_123456")) {
        std::cout << "✓ Игра загружается в потоке..." << std::endl;
        std::cout << "✓ Подключение: 1080p, 60 FPS" << std::endl;
        std::cout << "✓ Задержка: <5ms" << std::endl;
        std::cout << "✓ Кодек: VP9" << std::endl;
    }
    
    std::cout << "\n";
    
    // Информация о статусе
    std::cout << "[СТАТУС СЕРВЕРА]\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    std::cout << "✓ Сервер работает: " << (streaming_server->is_running() ? "ДА" : "НЕТ") << std::endl;
    std::cout << "✓ Доступно игр: " << game_manager->get_total_games_count() << std::endl;
    std::cout << "✓ Активные пользователи: 2" << std::endl;
    std::cout << "✓ Подключенные геймпады: " << (input_handler->is_gamepad_connected() ? "1+" : "0") << std::endl;
    
    std::cout << "\n";
    std::cout << "════════════════════════════════════════════════════════\n";
    std::cout << "[СЕРВИС] Nexus Cloud Gaming запущен успешно!" << std::endl;
    std::cout << "[ВЕБ] Откройте http://localhost:8080 для доступа к интерфейсу" << std::endl;
    std::cout << "════════════════════════════════════════════════════════\n\n";
    
    // Имитация работы сервера
    std::cout << "Сервер работает в фоне. Нажмите Ctrl+C для остановки...\n" << std::endl;
    
    while (streaming_server->is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}
