#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class EditUserDialog : public QDialog {
    Q_OBJECT
    QLineEdit* nameEdit;
    QLineEdit* roleEdit;

public:
    EditUserDialog(const QString& name, const QString& role, QWidget* parent = nullptr);

    QString getName() const;
    QString getRole() const;
};
