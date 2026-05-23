#!/bin/bash

# Скрипт для запуска Nexus Cloud Gaming

echo ""
echo "╔══════════════════════════════════════════════════════════╗"
echo "║                                                          ║"
echo "║        🎮  NEXUS CLOUD GAMING 🎮                        ║"
echo "║                                                          ║"
echo "║    Запуск сервиса облачного гейминга...               ║"
echo "║                                                          ║"
echo "╚══════════════════════════════════════════════════════════╝"
echo ""

# Переходим в папку проекта
cd "$(dirname "$0")"

# Проверяем, скомпилирован ли проект
if [ ! -f "build/NexusCloudGaming" ]; then
    echo "[СБОРКА] Компиляция проекта..."
    mkdir -p build
    cd build
    cmake ..
    make
    cd ..
    echo "[СБОРКА] Проект успешно скомпилирован!"
fi

echo ""
echo "[ЗАПУСК] Стартуем C++ backend..."
echo ""

# Запускаем C++ приложение в фоне
./build/NexusCloudGaming &
BACKEND_PID=$!

echo ""
echo "[ВЕБА] Запускаем веб-интерфейс..."
echo ""

# Проверяем, установлен ли Python
if command -v python3 &> /dev/null; then
    cd web
    python3 -m http.server 8080 &
    WEB_PID=$!
    cd ..
    echo "[ВЕБА] Веб-сервер запущен на http://localhost:8080"
else
    echo "[ОШИБКА] Python3 не установлен. Установите его и попробуйте снова."
    kill $BACKEND_PID
    exit 1
fi

echo ""
echo "════════════════════════════════════════════════════════════"
echo "✓ Backend работает на порту 8443"
echo "✓ Веб-интерфейс работает на http://localhost:8080"
echo ""
echo "Откройте браузер и перейдите на http://localhost:8080"
echo ""
echo "Для остановки нажмите Ctrl+C"
echo "════════════════════════════════════════════════════════════"
echo ""

# Ждем пока процессы работают
wait
