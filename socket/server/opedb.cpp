#include "opedb.h"

opeDB::opeDB()
{
    init();
}

bool opeDB::isExistInDB(const QString& account)
{
    if (db->isOpen()) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM users WHERE account = ?");
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

bool opeDB::inSertIntoDB(const QString account, const QString passwd)
{
    // 准备SQL查询语句
    QString sqlQuery = "INSERT INTO users VALUES (:account, :passwd)";

    // 创建QSqlQuery对象并将值绑定到占位符
    QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":account", account);
    query.bindValue(":passwd", passwd);

    // 执行查询
    if (!query.exec()) {
        qDebug() << "错误：无法将数据插入数据库。";
        qDebug() << query.lastError().text();
    } else {
        qDebug() << "数据插入成功！";
    }
}

void opeDB::init()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QODBC"));

    // 指定使用的ODBC数据源名称
    db->setDatabaseName("qtdemo");
    if (db->open()) {
        qDebug()<<"连接数据库成功！";
    } else {
        qDebug()<<"连接数据库失败！";
        qDebug()<<db->lastError().text();
    }
}

opeDB::~opeDB()
{
    db->close();
    delete db;
}
