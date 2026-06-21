# Игра в слова

## Фичи

- CLI интерфейс
- Автоматический фильтр кириллицы и латиницы
- Загрузка/сохранение в файл

## Установка

### Windows
#### Требования:
- `MinGW-w64`
- `CMake`

#### Шаги:
1. Клонировать репозиторий:
    ```bash
    git clone https://github.com/bemn/word-game.git
    cd phone-book
    ```
2. Собрать проект:
    ```bash
    cmake -G "MinGW Makefiles" .
    cmake --build .
    ```

## Использование
**Windows:**
Запускать файл `word_game.exe` в корне проекта.