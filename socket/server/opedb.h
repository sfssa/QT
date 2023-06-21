#ifndef OPEDB_H
#define OPEDB_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
class opeDB
{
public:
    opeDB();
    void insertInTODB();
    void isExistInDB();
    void isOnline();
private:
    void init();
    ~opeDB();
private:
    QSqlDatabase* db;
};

#endif // OPEDB_H
