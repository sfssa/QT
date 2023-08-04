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
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "myfile.h"

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
    //void on_regist_clicked();
    void sendMSG(const QJsonObject& json);
    void requestRegist(QString& account,QString& passwd,QString& verificationCode);
    bool requestForCode();
    void handleMsgClient();
    //void on_login_clicked();
    //void handleLogin();
    void on_yes_clicked();
    void onComboBoxIndexChanged(int index);

signals:
    void updateButtonState();
    void loginSuccess();
private:
    Ui::Widget *ui;
    QTcpSocket* mySocket;
    QString* myAccount;
    QString* myNickName;
    //QWidget* registerWidget;
    MyFile* myFile;
    //登录界面控件
    QLabel *accountLabel ;
    QLabel *nickNameLabel ;
    //QLabel *codeLable;
    QLabel *passwordLabel ;
    QLabel *confirmPasswordLabel;
    //注册界面的控件

    QLineEdit *nicknameLineEdit;
    QLineEdit *accountLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *confirmPasswordLineEdit;
    QPushButton *sendVerificationCodeButton;
    QLineEdit *verificationCodeLineEdit;
    QPushButton *registerButton;

};
#endif // WIDGET_H
