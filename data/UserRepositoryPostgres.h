#pragma once
#include <pqxx/pqxx>
#include <vector>
#include <string>

struct User {
    int id;
    std::string name;
    std::string role;
};

class UserRepositoryPostgres {
    pqxx::connection conn;

public:
    UserRepositoryPostgres(const std::string& conn_str);
    std::vector<User> getAllUsers();
    User addUser(const std::string& name, const std::string& role);
    void updateUser(int id, const std::string& name, const std::string& role);
    void deleteUser(int id);
};
