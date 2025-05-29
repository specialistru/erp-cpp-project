# ERP C++ Project

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













---

# Ключевые файлы и их описание

---

### 1. `CMakeLists.txt` (корневой)

```cmake
cmake_minimum_required(VERSION 3.16)
project(erp_cpp_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 Widgets и Concurrent
find_package(Qt6 COMPONENTS Widgets Concurrent REQUIRED)

# PostgreSQL + libpqxx
find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)

# GoogleTest (для тестов)
enable_testing()
find_package(GTest REQUIRED)

# Собираем основное приложение
add_executable(erp_gui
    src/ui/main.cpp
    src/ui/UserManagerWidget.cpp
    src/ui/UserManagerWidget.h
    src/ui/EditUserDialog.cpp
    src/ui/EditUserDialog.h
    src/data/UserRepositoryPostgres.cpp
    src/data/UserRepositoryPostgres.h
    src/service/UserService.h
)

target_include_directories(erp_gui PRIVATE
    ${PostgreSQL_INCLUDE_DIRS}
    ${LIBPQXX_INCLUDE_DIRS}
    src/
)

target_link_libraries(erp_gui
    Qt6::Widgets Qt6::Concurrent
    ${PostgreSQL_LIBRARIES}
    pqxx
)

set_target_properties(erp_gui PROPERTIES AUTOMOC ON)

# Тесты
add_executable(tests
    tests/UserServiceTest.cpp
)

target_include_directories(tests PRIVATE src/ ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)

add_test(NAME UserServiceTests COMMAND tests)
```

---

### 2. Пример `README.md`

````markdown
# ERP C++ Project

## О проекте

Минималистичный ERP с:

- Qt GUI (Widgets + Concurrent)
- PostgreSQL (libpqxx)
- Слои репозитория и бизнес-логики
- Асинхронные операции в GUI
- Юнит-тесты GoogleTest
- Документация Doxygen

## Требования

- CMake >= 3.16
- Qt6
- PostgreSQL сервер
- libpqxx
- GoogleTest

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

## Документация

Для генерации документации:

```bash
doxygen Doxyfile
```

Документация появится в папке `docs/html/index.html`.

```

---

### 3. Пример Doxyfile

Можно сгенерировать `doxygen -g` и немного подправить, например:

```

PROJECT\_NAME           = "ERP C++ Project"
OUTPUT\_DIRECTORY       = docs
INPUT                  = src
RECURSIVE              = YES
GENERATE\_LATEX         = NO
QUIET                  = YES
EXTRACT\_ALL            = YES

````

---

### 4. Основные исходники

- `src/data/UserRepositoryPostgres.*` — реализация репозитория с libpqxx (как в примерах выше)  
- `src/service/UserService.h` — сервисный слой  
- `src/ui/*.cpp/.h` — GUI на Qt (UserManagerWidget, EditUserDialog и main.cpp) с асинхронным обновлением и расширенными функциями (редактирование, удаление, поиск)  

---

### 5. Тесты

- `tests/UserServiceTest.cpp` — пример тестов с GoogleMock, как в предыдущем сообщении  

---

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
