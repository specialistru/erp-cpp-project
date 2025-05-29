#pragma once
#include "../data/UserRepositoryPostgres.h"

class UserService {
    UserRepositoryPostgres& repo;

public:
    explicit UserService(UserRepositoryPostgres& r) : repo(r) {}

    std::vector<User> getUsers() { return repo.getAllUsers(); }
    User addUser(const std::string& name, const std::string& role) {
        if (name.empty() || role.empty()) throw std::runtime_error("Имя и роль не могут быть пустыми.");
        return repo.addUser(name, role);
    }
    void updateUser(int id, const std::string& name, const std::string& role) {
        if (name.empty() || role.empty()) throw std::runtime_error("Поля не могут быть пустыми.");
        repo.updateUser(id, name, role);
    }
    void deleteUser(int id) { repo.deleteUser(id); }
};
