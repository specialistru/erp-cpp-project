# ERP C++ Project

## О проекте

Минималистичная ERP-система на C++:

- GUI на Qt6
- PostgreSQL через libpqxx
- Слой бизнес-логики (UserService)
- Асинхронная работа GUI
- Юнит-тесты (GoogleTest)
- Автогенерация документации (Doxygen)

# Структура репозитория

```
erp-cpp-project/
│
├── CMakeLists.txt
├── README.md
├── docs/
├── src/
│   ├── data/
│   │   ├── UserRepositoryPostgres.h
│   │   └── UserRepositoryPostgres.cpp
│   ├── service/
│   │   └── UserService.h
│   ├── ui/
│   │   ├── main.cpp
│   │   ├── UserManagerWidget.h
│   │   ├── UserManagerWidget.cpp
│   │   ├── EditUserDialog.h
│   │   └── EditUserDialog.cpp
│   └── utils/
│       └── 
│
├── tests/
│   ├── UserServiceTest.cpp
│   └── CMakeLists.txt
│
├── Doxyfile
└── .gitignore

```

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

```

## Быстрый старт

1. Клонировать репозиторий:

```bash
git clone <url>
cd erp-cpp-project
````

2. Создать билд и собрать:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. Запустить приложение:

```bash
./erp_gui
```

4. Запустить тесты:

```bash
ctest --verbose
```

## Полноценная GUI, связанный с PostgreSQL через бизнес-слой, со следующими возможностями:

✅ Добавление, редактирование, удаление пользователей   
✅ Поиск в таблице   
✅ Асинхронное обновление   
✅ Диалоги редактирования   
✅ Простая архитектура MVC/MVVM   
✅ Тестируемый бизнес-слой

# Как подготовить репозиторий

1. Создай локальную папку, размести все файлы согласно структуре и примерам выше.  
2. Инициализируй git:  
```bash

git init
git add .
git commit -m "Initial commit: ERP C++ starter project"

````
