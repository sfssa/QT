#include "opedb.h"

opeDB::opeDB()
{
    init();
}

bool opeDB::isExistInDB(const QString& account)
{
    if (db->isOpen()) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
        query.addBindValue(account);

        if (!query.exec()) {
            // 查询执行失败
            qDebug() << "Query execution failed:" << query.lastError().text();
            return false;
        }

        if (query.next()) {
            int count = query.value(0).toInt();
            return (count > 0); // 返回账号是否存在的判断结果
        }

        return false;
    }
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
