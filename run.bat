@echo off
REM Скрипт для запуска Nexus Cloud Gaming на Windows

cls
echo.
echo ╔══════════════════════════════════════════════════════════╗
echo ║                                                          ║
echo ║        🎮  NEXUS CLOUD GAMING 🎮                        ║
echo ║                                                          ║
echo ║    Запуск сервиса облачного гейминга...               ║
echo ║                                                          ║
echo ╚══════════════════════════════════════════════════════════╝
echo.

REM Проверяем, существует ли скомпилированный файл
if not exist "build\NexusCloudGaming.exe" (
    echo [СБОРКА] Компиляция проекта...
    if not exist "build" mkdir build
    cd build
    cmake -G "Visual Studio 17 2022" ..
    cmake --build . --config Release
    cd ..
    echo [СБОРКА] Проект успешно скомпилирован!
)

echo.
echo [ЗАПУСК] Стартуем C++ backend...
echo.

REM Запускаем C++ приложение в фоне
start "Nexus Backend" build\NexusCloudGaming.exe

echo [ЗАПУСК] Ожидание запуска backend...
timeout /t 2 /nobreak

echo.
echo [ВЕБА] Запускаем веб-интерфейс...
echo.

REM Запускаем веб-сервер
cd web
start "Nexus Web" python -m http.server 8080
cd ..

echo.
echo ════════════════════════════════════════════════════════════
echo ✓ Backend работает на порту 8443
echo ✓ Веб-интерфейс работает на http://localhost:8080
echo.
echo Откройте браузер и перейдите на http://localhost:8080
echo.
echo Для остановки закройте окна консоли
echo ════════════════════════════════════════════════════════════
echo.

pause
