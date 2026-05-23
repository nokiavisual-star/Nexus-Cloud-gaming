# 🚀 Инструкция по Сборке и Развертыванию

## Быстрый старт (Linux/Mac)

```bash
# 1. Клонируем репозиторий
git clone https://github.com/nokiavisual-star/Nexus-Cloud-gaming.git
cd Nexus-Cloud-gaming

# 2. Делаем скрипт исполняемым
chmod +x run.sh

# 3. Запускаем (сборка + запуск)
./run.sh
```

Откройте браузер: **http://localhost:8080**

---

## Подробная установка

### 🔧 Требования

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    libcurl4-openssl-dev \
    python3-venv \
    python3-pip
```

#### macOS
```bash
# Установка Homebrew (если не установлен)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Установка зависимостей
brew install cmake openssl curl
```

#### Windows
1. Скачайте Visual Studio 2019+ (включая C++ development tools)
2. Установите CMake (https://cmake.org/download/)
3. Установите OpenSSL (https://slproweb.com/products/Win32OpenSSL.html)

---

### 📦 Сборка проекта

#### На Linux/Mac

```bash
# Перейдите в папку проекта
cd Nexus-Cloud-gaming

# Создайте папку для сборки
mkdir -p build
cd build

# Конфигурируйте CMake
cmake ..

# Компилируйте
make -j$(nproc)

# Исполняемый файл находится в build/NexusCloudGaming
```

#### На Windows (Visual Studio)

```cmd
cd Nexus-Cloud-gaming
mkdir build
cd build

cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release

REM Исполняемый файл находится в build\Release\NexusCloudGaming.exe
```

#### На Windows (MinGW)

```cmd
cd Nexus-Cloud-gaming
mkdir build
cd build

cmake -G "MinGW Makefiles" ..
mingw32-make

REM Исполняемый файл находится в build\NexusCloudGaming.exe
```

---

### 🌐 Запуск Веб-Интерфейса

#### Вариант 1: Python (Рекомендуется)
```bash
cd web
python3 -m http.server 8080
```

#### Вариант 2: Node.js
```bash
npm install -g http-server
cd web
http-server -p 8080
```

#### Вариант 3: PHP
```bash
cd web
php -S localhost:8080
```

#### Вариант 4: Docker
```bash
docker run -p 8080:80 -v $(pwd)/web:/usr/share/nginx/html nginx:alpine
```

---

### 🎮 Полный запуск

#### Linux/Mac (автоматический)
```bash
./run.sh
```

Это запустит:
- ✅ C++ Backend (порт 8443)
- ✅ Веб-сервер (порт 8080)
- ✅ Автоматически откроет браузер

#### Windows (автоматический)
```cmd
run.bat
```

#### Ручной запуск (все платформы)

Терминал 1 (Backend):
```bash
./build/NexusCloudGaming
# или на Windows: build\Release\NexusCloudGaming.exe
```

Терминал 2 (Веб-сервер):
```bash
cd web
python3 -m http.server 8080
```

---

## 📋 Структура Проекта

```
Nexus-Cloud-gaming/
├── src/                      # Исходный код C++
│   ├── main.cpp
│   ├── server/              # Серверная часть
│   ├── core/                # Ядро (аутентификация, хранилище)
│   └── client/              # Клиентская часть
├── web/                      # Веб-интерфейс
│   ├── index.html
│   ├── styles.css
│   └── script.js
├── build/                    # Скомпилированные файлы
│   └── NexusCloudGaming      # Исполняемый файл
├── CMakeLists.txt           # Конфигурация сборки
├── README.md                # Документация
├── run.sh                   # Скрипт запуска (Linux/Mac)
├── run.bat                  # Скрипт запуска (Windows)
└── .gitignore
```

---

## 🔍 Проверка Установки

### Linux/Mac
```bash
# Проверка компилятора
gcc --version
g++ --version

# Проверка CMake
cmake --version

# Проверка OpenSSL
openssl version

# Проверка curl
curl --version

# Проверка Python
python3 --version
```

### Windows (cmd)
```cmd
gcc --version
cmake --version
openssl version
python --version
```

---

## 🐛 Устранение неполадок

### Ошибка: "CMake not found"
**Решение:**
```bash
# Linux
sudo apt install cmake

# Mac
brew install cmake

# Windows: скачайте с cmake.org
```

### Ошибка: "OpenSSL not found"
**Решение:**
```bash
# Linux
sudo apt install libssl-dev

# Mac
brew install openssl
# И установите переменные окружения:
export LDFLAGS="-L/usr/local/opt/openssl/lib"
export CPPFLAGS="-I/usr/local/opt/openssl/include"

# Windows: скачайте с slproweb.com
```

### Ошибка: "Python not found"
**Решение:**
```bash
# Linux
sudo apt install python3

# Mac
brew install python3

# Windows: скачайте с python.org
```

### Ошибка: "Port already in use"
**Решение:**
```bash
# Измените порт в скрипте
python3 -m http.server 8081  # Вместо 8080
```

### Ошибка компиляции с OpenSSL 3.0
**Решение:**
Это предупреждение (не ошибка). SHA1_Init и друзья помечены как deprecated, но они работают.
Для избежания предупреждений:
```bash
cd build
cmake -DCMAKE_C_FLAGS="-Wno-deprecated-declarations" ..
make
```

---

## 📊 Логирование

### Включение отладки
В `src/main.cpp` раскомментируйте нужные строки для более подробного логирования.

### Просмотр логов
```bash
# Linux/Mac
./build/NexusCloudGaming > logs.txt 2>&1

# Windows
build\NexusCloudGaming.exe > logs.txt 2>&1
```

---

## 🚀 Развертывание на Сервере

### На VPS (Ubuntu)

```bash
# SSH подключение
ssh user@your-vps.com

# Установка зависимостей
sudo apt update
sudo apt install -y build-essential cmake git libssl-dev libcurl4-openssl-dev python3

# Клонирование
git clone https://github.com/nokiavisual-star/Nexus-Cloud-gaming.git
cd Nexus-Cloud-gaming

# Сборка
mkdir build && cd build
cmake ..
make -j$(nproc)
cd ..

# Запуск с systemd
sudo nano /etc/systemd/system/nexus.service
```

**Содержимое `/etc/systemd/system/nexus.service`:**
```ini
[Unit]
Description=Nexus Cloud Gaming Service
After=network.target

[Service]
Type=simple
User=nexus
WorkingDirectory=/home/nexus/Nexus-Cloud-gaming
ExecStart=/home/nexus/Nexus-Cloud-gaming/build/NexusCloudGaming
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

```bash
sudo systemctl enable nexus
sudo systemctl start nexus
sudo systemctl status nexus
```

### На Docker

**Dockerfile:**
```dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential cmake git libssl-dev libcurl4-openssl-dev python3

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

EXPOSE 8443 8080

CMD ["./run.sh"]
```

**Сборка и запуск:**
```bash
docker build -t nexus-cloud-gaming .
docker run -p 8443:8443 -p 8080:8080 nexus-cloud-gaming
```

---

## 📈 Производительность

Рекомендуемые характеристики сервера:
- **CPU:** 4+ ядер
- **RAM:** 8GB+
- **SSD:** 100GB+
- **Сеть:** 1Gbps+

---

## 🔐 Безопасность в Продакшене

1. Используйте HTTPS (Let's Encrypt)
2. Настройте firewall
3. Используйте nginx как reverse proxy
4. Включите CORS политику
5. Настройте логирование и мониторинг

---

## 📞 Поддержка

Если у вас возникли проблемы:
1. Проверьте логи: `build/NexusCloudGaming > logs.txt 2>&1`
2. Посмотрите FAQ в README.md
3. Создайте issue на GitHub
4. Свяжитесь с нами: support@nexuscloudgaming.com

---

**Успешной сборки и развертывания! 🚀**
