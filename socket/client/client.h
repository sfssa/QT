#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpSocket>
#include <QWidget>
#include <QMessageBox>
#include "protocol.h"
#include <QPushButton>
#include <QFormLayout>
#include <QRegularExpression>
#include <QLineEdit>
#include <QLabel>
#include <QJsonObject>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_regist_clicked();
    void sendMSG(QJsonObject& json);
    void requestRegist(QString& account,QString& passwd);
    void requestForCode();
    void handleMsgClient();
private:
    Ui::Widget *ui;
    QTcpSocket* mySocket;
    QString* myAccount;
    QString* myNickName;
    QWidget* registerWidget;


};
#endif // WIDGET_H
