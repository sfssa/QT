#include "opedb.h"

opeDB::opeDB()
{
    init();
}

void opeDB::isExistInDB()
{

}

void opeDB::init()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC"));

    // 指定使用的ODBC数据源名称
    db->setDatabaseName("design");
    if (db->open()) {
        QMessageBox::information(nullptr, "连接数据库", "连接数据库成功！");
    } else {
        QMessageBox::critical(nullptr, "连接数据库", "连接数据库失败！\n" + db->lastError().text());
    }
}

opeDB::~opeDB()
{
    db->close();
    delete db;
}
