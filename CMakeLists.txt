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
