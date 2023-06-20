#include "connect.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");

    // 指定使用的ODBC数据源名称
    db.setDatabaseName("design");
    if (db.open()) {
        QMessageBox::information(nullptr, "连接数据库", "连接数据库成功！");
    } else {
        QMessageBox::critical(nullptr, "连接数据库", "连接数据库失败！\n" + db.lastError().text());
    }
}

Widget::~Widget()
{
    delete ui;

}

