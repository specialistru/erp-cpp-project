#include "EditUserDialog.h"

EditUserDialog::EditUserDialog(const QString& name, const QString& role, QWidget* parent)
    : QDialog(parent) {
    nameEdit = new QLineEdit(name);
    roleEdit = new QLineEdit(role);

    auto* form = new QFormLayout;
    form->addRow("Имя:", nameEdit);
    form->addRow("Роль:", roleEdit);

    auto* saveBtn = new QPushButton("Сохранить");
    auto* cancelBtn = new QPushButton("Отмена");

    auto* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);

    form->addRow(btnLayout);
    setLayout(form);

    connect(saveBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

QString EditUserDialog::getName() const {
    return nameEdit->text();
}

QString EditUserDialog::getRole() const {
    return roleEdit->text();
}
