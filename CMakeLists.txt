cmake_minimum_required(VERSION 3.16)
project(erp_cpp_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Concurrent REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)
enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
