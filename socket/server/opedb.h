#ifndef OPEDB_H
#define OPEDB_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QtDebug>
#include <QSqlQuery>
#include <QMessageBox>
class opeDB
{
public:
    opeDB();
    void insertInTODB();
    bool isExistInDB(const QString& account);
    void isOnline();
    bool inSertIntoDB(const QString account,const QString passwd);
    bool checkAccount(const QString& account,const QString& passwd);
private:
    void init();
    ~opeDB();
private:
    QSqlDatabase* db;
};

#endif // OPEDB_H
