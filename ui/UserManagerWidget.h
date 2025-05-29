#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <memory>
#include "../service/UserService.h"

class UserManagerWidget : public QWidget {
    Q_OBJECT

public:
    explicit UserManagerWidget(const std::string& dbConnStr, QWidget* parent = nullptr);

private:
    std::unique_ptr<UserRepositoryPostgres> repo;
    std::unique_ptr<UserService> service;

    QTableWidget* table;
    QLineEdit* nameInput;
    QLineEdit* roleInput;
    QPushButton* addButton;
    QLineEdit* searchBox;

    void setupUI();
    void refreshTableAsync();
    void updateTableWithUsers(const std::vector<User>& users);
    void onAddUser();
    void onDeleteUser(int userId);
    void onEditUser(int userId, const QString& currentName, const QString& currentRole);
    void onSearchTextChanged(const QString& text);
};
