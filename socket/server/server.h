#ifndef WIDGET_H
#define WIDGET_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QWidget>
#include <QMessageBox>
#include <QList>
#include <QDebug>
#include <QJsonObject>
#include <QPair>
#include <QRandomGenerator>
#include <QString>
#include <QByteArray>
#include <QDataStream>
#include <QJsonDocument>

#include "opedb.h"
#include "thread_pool.h"
#include "protocol.h"
#include "smtp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void handleMSG();
    //void responseForCode(const QString& code);
    ~Widget();
    QString generateVerificationCode(int length);
    void sendMail(const QString& receiver,const QString& str);
    //上传文件
    //显示文件
    //下载文件
private slots:
    void on_start_clicked();
    void handleNewConnection();
    void handleOffLine();

private:
    QTcpSocket *clientSocket;
    opeDB* db;
    Ui::Widget *ui;
    QTcpServer* server;
    QList<QTcpSocket*>* clientSockets;
    ThreadPool threadPool;
    // 声明存储验证码和客户端Socket连接的容器
    //QPair<QString, QTcpSocket*> verificationCodes;
    //QList<QPair<QTcpSocket*, QString>> verificationCodes;
    QMap<QTcpSocket*, QString>myMap;
};
#endif // WIDGET_H
