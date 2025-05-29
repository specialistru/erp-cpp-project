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
        table->setItem(i, 1, new QTableWid
