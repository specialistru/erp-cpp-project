#include "UserManagerWidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string conn_str = "dbname=erp_db user=erp_user password=secret host=localhost port=5432";
    UserManagerWidget widget(conn_str);
    widget.setWindowTitle("ERP — Пользователи");
    widget.resize(800, 600);
    widget.show();
    return app.exec();
}
