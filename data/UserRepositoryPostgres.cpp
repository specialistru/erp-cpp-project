#include "UserRepositoryPostgres.h"

UserRepositoryPostgres::UserRepositoryPostgres(const std::string& conn_str) : conn(conn_str) {
    pqxx::work txn(conn);
    txn.exec("CREATE TABLE IF NOT EXISTS users ("
             "id SERIAL PRIMARY KEY, "
             "name TEXT NOT NULL, "
             "role TEXT NOT NULL)");
    txn.commit();
}

std::vector<User> UserRepositoryPostgres::getAllUsers() {
    pqxx::work txn(conn);
    auto result = txn.exec("SELECT id, name, role FROM users ORDER BY id");
    std::vector<User> users;
    for (auto row : result) {
        users.push_back({row["id"].as<int>(), row["name"].c_str(), row["role"].c_str()});
    }
    return users;
}

User UserRepositoryPostgres::addUser(const std::string& name, const std::string& role) {
    pqxx::work txn(conn);
    auto result = txn.exec_params("INSERT INTO users (name, role) VALUES ($1, $2) RETURNING id", name, role);
    txn.commit();
    return {result[0][0].as<int>(), name, role};
}

void UserRepositoryPostgres::updateUser(int id, const std::string& name, const std::string& role) {
    pqxx::work txn(conn);
    txn.exec_params("UPDATE users SET name = $1, role = $2 WHERE id = $3", name, role, id);
    txn.commit();
}

void UserRepositoryPostgres::deleteUser(int id) {
    pqxx::work txn(conn);
    txn.exec_params("DELETE FROM users WHERE id = $1", id);
    txn.commit();
}
