# ERP C++ Project

Минималистичная ERP-система на C++:

- GUI на Qt6
- PostgreSQL через libpqxx
- Слой бизнес-логики (UserService)
- Асинхронная работа GUI
- Юнит-тесты (GoogleTest)
- Автогенерация документации (Doxygen)

## Требования

- CMake >= 3.16
- Qt6
- PostgreSQL
- libpqxx
- GoogleTest

## Сборка

```bash
mkdir build && cd build
cmake ..
cmake --build .
