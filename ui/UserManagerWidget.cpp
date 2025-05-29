#include "UserManagerWidget.h"
#include "EditUserDialog.h"
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QtConcurrent>

UserManagerWidget::UserManagerWidget(const std::string& dbConnStr, QWidget* parent)
    : QWidget(parent) {
    repo = std::make_unique<UserRepositoryPostgres>(dbConnStr);
    service = std::make_unique<UserService>(*repo);
    setupUI();
    refreshTableAsync();
}

void UserManagerWidget::setupUI() {
    nameInput = new QLineEdit;
    roleInput = new QLineEdit;
    nameInput->setPlaceholderText("Имя");
    roleInput->setPlaceholderText("Роль");

    addButton = new QPushButton("Добавить");
    searchBox = new QLineEdit;
    searchBox->setPlaceholderText("Поиск...");

    table = new QTableWidget;
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID", "Имя", "Роль", "Редактировать", "Удалить"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto formLayout = new QHBoxLayout;
    formLayout->addWidget(nameInput);
    formLayout->addWidget(roleInput);
    formLayout->addWidget(addButton);

    auto layout = new QVBoxLayout;
    layout->addWidget(searchBox);
    layout->addLayout(formLayout);
    layout->addWidget(table);
    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &UserManagerWidget::onAddUser);
    connect(searchBox, &QLineEdit::textChanged, this, &UserManagerWidget::onSearchTextChanged);
}

void UserManagerWidget::refreshTableAsync() {
    QtConcurrent::run([this] {
        auto users = service->getUsers();
        QMetaObject::invokeMethod(this, [this, users]() {
            updateTableWithUsers(users);
        }, Qt::QueuedConnection);
    });
}

void UserManagerWidget::updateTableWithUsers(const std::vector<User>& users) {
    table->setRowCount(static_cast<int>(users.size()));
    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        const User& user = users[i];

        table->setItem(i, 0, new QTableWidgetItem(QString::number(user.id)));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(user.name)));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(user.role)));

        auto* editBtn = new QPushButton("Редактировать");
        auto* delBtn = new QPushButton("Удалить");

        connect(editBtn, &QPushButton::clicked, this, [=]() {
            onEditUser(user.id, QString::fromStdString(user.name), QString::fromStdString(user.role));
        });
        connect(delBtn, &QPushButton::clicked, this, [=]() {
            onDeleteUser(user.id);
        });

        table->setCellWidget(i, 3, editBtn);
        table->setCellWidget(i, 4, delBtn);
    }
}

void UserManagerWidget::onAddUser() {
    try {
        auto name = nameInput->text().toStdString();
        auto role = roleInput->text().toStdString();
        service->addUser(name, role);
        nameInput->clear();
        roleInput->clear();
        refreshTableAsync();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void UserManagerWidget::onDeleteUser(int userId) {
    auto confirm = QMessageBox::question(this, "Подтверждение", "Удалить пользователя?");
    if (confirm == QMessageBox::Yes) {
        service->deleteUser(userId);
        refreshTableAsync();
    }
}

void UserManagerWidget::onEditUser(int userId, const QString& currentName, const QString& currentRole) {
    EditUserDialog dialog(currentName, currentRole, this);
    if (dialog.exec() == QDialog::Accepted) {
        try {
            service->updateUser(userId, dialog.getName().toStdString(), dialog.getRole().toStdString());
            refreshTableAsync();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", e.what());
        }
    }
}

void UserManagerWidget::onSearchTextChanged(const QString& text) {
    auto users = service->getUsers();
    std::vector<User> filtered;
    for (const auto& user : users) {
        QString name = QString::fromStdString(user.name);
        QString role = QString::fromStdString(user.role);
        if (name.contains(text, Qt::CaseInsensitive) || role.contains(text, Qt::CaseInsensitive)) {
            filtered.push_back(user);
        }
    }
    updateTableWithUsers(filtered);
}
