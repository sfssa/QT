#include "client.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,myAccount(nullptr)
    ,myNickName(nullptr)
    ,registerWidget(nullptr)
{
    ui->setupUi(this);
    mySocket=new QTcpSocket();
    mySocket->connectToHost("127.0.0.1", 12345);

    if (mySocket->waitForConnected()) {
        // 连接成功
        QMessageBox::information(this,"连接服务器","连接成功！");
    } else {
        QMessageBox::critical(this,"连接服务器","连接失败！");
        qDebug() << mySocket->errorString();
    }
}

Widget::~Widget()
{
    delete ui;
    mySocket->close();
    delete mySocket;
    delete registerWidget;
}


void Widget::on_regist_clicked()
{
    registerWidget = new QWidget(nullptr);

    QLabel *accountLabel = new QLabel("账号:",registerWidget);
    QLabel *nickNameLabel = new QLabel("昵称:",registerWidget);
    QLabel *passwordLabel = new QLabel("密码:",registerWidget);

    QLabel *confirmPasswordLabel = new QLabel("确认密码:",registerWidget);

    QLineEdit *accountLineEdit = new QLineEdit(registerWidget);
    QLineEdit *passwordLineEdit = new QLineEdit(registerWidget);
    QLineEdit *nickNameLineEdit = new QLineEdit(registerWidget);
    QLineEdit *confirmPasswordLineEdit = new QLineEdit(registerWidget);
    QLineEdit *verificationCodeLineEdit = new QLineEdit(registerWidget);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *sendCodeButton = new QPushButton("发送验证码",registerWidget);
    QPushButton *confirmButton = new QPushButton("确定",registerWidget);
    QFormLayout *formLayout = new QFormLayout(registerWidget);
    formLayout->addRow(nickNameLabel,nickNameLineEdit);
    formLayout->addRow(accountLabel, accountLineEdit);
    formLayout->addRow(passwordLabel, passwordLineEdit);
    formLayout->addRow(confirmPasswordLabel, confirmPasswordLineEdit);
    formLayout->addRow(verificationCodeLineEdit,sendCodeButton);
    formLayout->addRow(confirmButton);
    QVBoxLayout *mainLayout = new QVBoxLayout(registerWidget);
    mainLayout->addLayout(formLayout);

    registerWidget->setWindowTitle("注册界面");
    registerWidget->show();
    connect(confirmButton, &QPushButton::clicked, [=](){
        QString account = accountLineEdit->text();
        QString nickname = nickNameLineEdit->text();
        QString password = passwordLineEdit->text();
        QString confirmPassword = confirmPasswordLineEdit->text();
        QString verificationCode = verificationCodeLineEdit->text();

        //判断是否有空的数据
        if(account==nullptr||nickname==nullptr||password==nullptr||confirmPassword==nullptr||verificationCode==nullptr)
        {
            QMessageBox::warning(this,"注册","请输入完整信息！");
            return;
        }
        else if(password!=confirmPassword)
        {
            QMessageBox::warning(this,"注册","输入的密码不一致！");
            return;
        }

        //正则表达式，密码至少一个字母、一个数字、一个特殊字符、长度6-15
        QRegularExpression passwordRegex("^(?=.*[A-Za-z])(?=.*\\d)(?=.*[@$!%*#?&])[A-Za-z\\d@$!%*#?&]{6,15}$");
        // 进行正则表达式匹配
        QRegularExpressionMatch match = passwordRegex.match(password);
        if (!match.hasMatch()) {
            QMessageBox::warning(this,"注册","密码过于简单，至少包含一个数字，一个字母和一个特殊字符!");
        }else if(password.length()<6||password.length()>15)
        {
            QMessageBox::warning(this,"注册","密码长度不合法，长度应在6-15!");
        }
        myNickName=new QString(nickname.toUtf8().constData());
        myAccount=new QString(account.toUtf8().constData());
        requestRegist(account,password);

    });
    //connect(registerWidget,&QWidget::destroyed,this,&Widget::show);

    //this->hide();
}

void Widget::sendMSG(QJsonObject& data)
{
    // 创建 JSON 文档
    QJsonDocument doc(data);

    // 将 JSON 文档转换为字符串
    QByteArray jsonData = doc.toJson();

    if (mySocket->waitForConnected()) {
        // 向服务器发送数据
        mySocket->write(jsonData);
        mySocket->waitForBytesWritten();
        mySocket->flush();
    }
    else {
        // 连接失败处理
        QMessageBox::critical(this,"发送","发送失败！");
    }
}

void Widget::requestRegist(QString &account, QString &passwd)
{
    //将账户和密码发送到服务器
    QJsonObject data;
    data["type"]=REGIST_REQUEST;
    data["account"]=account;
    data["passwd"]=passwd;
    QJsonDocument doc(data);
    QByteArray jsonData=doc.toJson();
    mySocket->write(jsonData);
    // 确认数据已发送完毕
    if (!mySocket->waitForBytesWritten()) {
        QMessageBox::warning(this,"发送","发送失败！");
        return;
    }
}



