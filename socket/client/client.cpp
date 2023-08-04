#include "client.h"
#include "ui_widget.h"

//using
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,myAccount(nullptr)
    ,myNickName(nullptr)

{
    ui->setupUi(this);
    mySocket=new QTcpSocket();
    myFile=new MyFile;
    mySocket->connectToHost("127.0.0.1", 12345);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::onComboBoxIndexChanged);
    if (mySocket->waitForConnected()) {
        // 连接成功
        qDebug()<<"连接服务器成功！";
        //QMessageBox::information(this,"连接服务器","连接成功！");
        connect(mySocket,&QTcpSocket::readyRead,this,&Widget::handleMsgClient);
    } else {
        qDebug()<<"连接服务器失败！";
        //QMessageBox::critical(this,"连接服务器","连接失败！");
        qDebug() << mySocket->errorString();
    }


    accountLabel = new QLabel("账号:",ui->login_or_regist);
    nickNameLabel = new QLabel("昵称:",ui->login_or_regist);
    passwordLabel = new QLabel("密码:",ui->login_or_regist);
    confirmPasswordLabel = new QLabel("确认密码:",ui->login_or_regist);
    //codeLable=new QLabel("发送验证码:",ui->login_or_regist);
    nicknameLineEdit=new QLineEdit(ui->login_or_regist);
    accountLineEdit = new QLineEdit(ui->login_or_regist);
    passwordLineEdit = new QLineEdit(ui->login_or_regist);
    confirmPasswordLineEdit = new QLineEdit(ui->login_or_regist);
    verificationCodeLineEdit = new QLineEdit(ui->login_or_regist);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    sendVerificationCodeButton = new QPushButton("发送验证码",ui->login_or_regist);
    registerButton = new QPushButton("确定",ui->login_or_regist);

    accountLabel->hide();
    confirmPasswordLabel->hide();
    passwordLabel->hide();
    nicknameLineEdit->hide();
    verificationCodeLineEdit->hide();
    passwordLineEdit->hide();
    confirmPasswordLineEdit->hide();
    accountLineEdit->hide();
    nickNameLabel->hide();
    sendVerificationCodeButton->hide();
    registerButton->hide();

}

//using
Widget::~Widget()
{
    delete ui;
    mySocket->close();
    delete mySocket;
    delete myAccount;
}



//using
void Widget::sendMSG(const QJsonObject& data)
{
    // 创建 JSON 文档
    QJsonDocument doc(data);

    // 将 JSON 文档转换为字符串
    QByteArray jsonData = doc.toJson();
    mySocket->write(jsonData);
    if (mySocket->waitForBytesWritten()) {
        // 向服务器发送数据
        qDebug()<<"发送成功！";

    }
    else {
        // 连接失败处理
        QMessageBox::critical(this,"发送","发送失败！");
        qDebug()<<mySocket->errorString();
    }
}

void Widget::requestRegist(QString &account, QString &passwd,QString& verificationCode)
{
//    if (mySocket->state() != QAbstractSocket::ConnectedState) {
//        mySocket->connectToHost("127.0.0.1", 12345);
//    }
//    if (mySocket->waitForConnected()) {
//        // 连接成功
//        qDebug()<<"在requestRegist函数中重新连接服务器成功";
//        //connect(mySocket,&QTcpSocket::readyRead,this,&Widget::handleMsgClient);
//    } else {
//        qDebug()<<"在requestRegist函数中重新连接服务器失败";
//        qDebug() << mySocket->errorString();
//    }
    //将账户和密码发送到服务器
    QJsonObject data;
    data["type"]=REGIST_REQUEST;
    data["account"]=account;
    data["passwd"]=passwd;
    data["verificationCode"]=verificationCode;
    QJsonDocument doc(data);
    QByteArray jsonData=doc.toJson();
    mySocket->write(jsonData);
    // 确认数据已发送完毕
    if (!mySocket->waitForBytesWritten()) {
        QMessageBox::warning(this,"发送","发送失败！");
        return;
    }
}

bool Widget::requestForCode()
{
    if(*myAccount==nullptr)
        return false;
    QJsonObject data;
    data["type"]=REQUEST_CODE;
    //qDebug()<<myAccount;
    //qDebug()<<*myAccount;
    //QString str=*myAccount;
    data["receiver"]=(*myAccount);
    QJsonDocument doc(data);
    QByteArray jsonData=doc.toJson();
    mySocket->write(jsonData);
    // 确认数据已发送完毕
    if (!mySocket->waitForBytesWritten()) {
        QMessageBox::warning(this,"发送","发送失败！");
        return false;
    }
    qDebug()<<"验证码请求申请发送完毕";
    return true;
}

//using
void Widget::handleMsgClient()
{
    //qDebug()<<"收到信息！"<<endl;
    QByteArray data = mySocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj=doc.object();
    int type=jsonObj["type"].toInt();
    qDebug()<<"current type is :"<<type;
    switch(type)
    {
    case RESPONSE_CODE_ISEXIST:
    {
        QMessageBox::warning(NULL,"注册","账号已存在！");
        break;
    }
    case CODE_NONCONRECT:
    {
        QMessageBox::warning(nullptr,"注册","验证码有误，请检查后重试！");
        break;
    }
    case REGIST_SUCCESS:
    {
        QMessageBox::information(nullptr,"注册","注册成功！");
        break;
    }
    case REGIST_FAILED:
    {
        QMessageBox::warning(nullptr,"注册","注册失败！请检查网络！");
        break;
    }
    case LOGIN_FAILED_NOT_REGIST:
    {
        QMessageBox::warning(nullptr,"登录","登陆失败，账号不存在！");
        break;
    }
    case LOGIN_FAILED_ACCOUNT_OR_PASSWD:
    {
        QMessageBox::warning(nullptr,"登录","登录失败，密码有误！");
        break;
    }
    case LOGIN_SUCCESS:
    {
        //QMessageBox::warning(nullptr,"登录","登录成功！");
        emit loginSuccess();
        //发送信息到服务器请求资源信息
        //ui->widget->setVisible(false);

        //ui->comboBox->hide();
        //myFile->show();
        break;
    }
    default:
        break;
    }
}



//
//void Widget::on_login_clicked()
//{
//    //账号、密码、登录
//    // 设置窗口大小和标题
//    // 创建输入框和登录按钮
//    //qDebug()<<"嘀嘀嘀嘀嘀嘀";
//    QWidget* loginWidget=new QWidget(nullptr);
//    loginWidget->setObjectName("登录");
//    QLabel* accountLabel=new QLabel("账号：",loginWidget);
//    QLabel* passwdLabel=new QLabel("密码：",loginWidget);
//    QLineEdit* accountLineEdit=new QLineEdit(loginWidget);
//    QLineEdit* passwdLineEdit=new QLineEdit(loginWidget);
//    QPushButton* confirmButton=new QPushButton("确认",loginWidget);
//    QVBoxLayout* mainLayout=new QVBoxLayout;
//    QHBoxLayout* level2=new QHBoxLayout;
//    QHBoxLayout* level1=new QHBoxLayout;
//    level1->addWidget(accountLabel);
//    level2->addWidget(passwdLabel);
//    level1->addWidget(accountLineEdit);
//    level2->addWidget(passwdLineEdit);
//    mainLayout->addLayout(level1);
//    mainLayout->addLayout(level2);
//    mainLayout->addWidget(confirmButton);
//    loginWidget->setLayout(mainLayout);
//    loginWidget->show();
//    connect(confirmButton,&QPushButton::clicked,[=](){
//        confirmButton->setEnabled(false);
//        //获取所有信息，调用handleLgon函数
//        QString account=accountLineEdit->text();
//        QString passwd=passwdLineEdit->text();
//        qDebug()<<"账户："<<account<<" 密码："<<passwd;
//        QJsonObject data;
//        data["type"]=LOGIN_REQUEST;
//        data["account"]=account;
//        data["passwd"]=passwd;
//        sendMSG(data);
//    });

//    // 连接登录按钮的点击信号与槽函数

//}

//void Widget::handleLogin()
//{

//}

//using
void Widget::on_yes_clicked()
{
    //获得账号和密码
    QString account=ui->account->text();
    QString passwd=ui->passwd->text();
    if(account==nullptr||passwd==nullptr)
    {
        QMessageBox::warning(nullptr,"登录","账号或密码为空！");
        return;
    }
    //将账号密码发送到服务器
    QJsonObject data;
    data["type"]=LOGIN_REQUEST;
    data["account"]=account;
    data["passwd"]=passwd;
    sendMSG(data);
}

void Widget::onComboBoxIndexChanged(int index)
{
    if(index==0)//登录
    {
        //显示登录
        ui->account->show();
        ui->passwd->show();
        ui->label->show();
        ui->label_2->show();
        ui->yes->show();

        //隐藏注册
        nickNameLabel->hide();
        accountLabel->hide();
        passwordLabel->hide();
        confirmPasswordLabel->hide();


        nicknameLineEdit->hide();
        accountLineEdit->hide();
        passwordLineEdit->hide();
        confirmPasswordLineEdit->hide();
        verificationCodeLineEdit->hide();

        sendVerificationCodeButton->hide();
        registerButton->hide();

    }
    else        //注册
    {
        //隐藏登录界面,
        ui->account->hide();
        ui->passwd->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->yes->hide();

        // 获取父对象的布局
        QLayout* layout = ui->login_or_regist->layout();

        // 移除布局与控件的关联
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget() != nullptr) {
                child->widget()->setParent(nullptr); // 设置父对象为空，释放控件的内存
            }
            delete child; // 删除布局项
        }

        // 删除布局
        delete layout;



        //显示注册界面
        //registerWidget = new QWidget(nullptr);
        nickNameLabel->show();
        accountLabel->show();
        confirmPasswordLabel->show();
        passwordLabel->show();

        nicknameLineEdit->show();
        verificationCodeLineEdit->show();
        passwordLineEdit->show();
        confirmPasswordLineEdit->show();
        accountLineEdit->show();
        sendVerificationCodeButton->show();
        registerButton->show();


        connect(sendVerificationCodeButton,&QPushButton::clicked,[=](){
            QString account=accountLineEdit->text();
            myAccount=new QString(account);
            if(requestForCode())//发送成功
            {
                QMessageBox::information(nullptr,"注册","验证码已发送，请检查邮箱！");
                sendVerificationCodeButton->setEnabled(false);
            }
            qDebug()<<myAccount;
            qDebug()<<*myAccount;
        });

        // 创建一个垂直布局
        QVBoxLayout *mainLayout = new QVBoxLayout(ui->login_or_regist);

        // 添加昵称、账号、密码和确认密码等行
        QHBoxLayout *nickNameLayout = new QHBoxLayout();
        nickNameLayout->addWidget(nickNameLabel);
        nickNameLayout->addWidget(nicknameLineEdit);

        QHBoxLayout *accountLayout = new QHBoxLayout();
        accountLayout->addWidget(accountLabel);
        accountLayout->addWidget(accountLineEdit);

        QHBoxLayout *passwordLayout = new QHBoxLayout();
        passwordLayout->addWidget(passwordLabel);
        passwordLayout->addWidget(passwordLineEdit);

        QHBoxLayout *confirmPasswordLayout = new QHBoxLayout();
        confirmPasswordLayout->addWidget(confirmPasswordLabel);
        confirmPasswordLayout->addWidget(confirmPasswordLineEdit);

        // 创建一个水平布局
        QHBoxLayout *verificationCodeLayout = new QHBoxLayout();
        verificationCodeLayout->addWidget(verificationCodeLineEdit);
        verificationCodeLayout->addWidget(sendVerificationCodeButton);

        // 添加每一行到垂直布局中
        mainLayout->addLayout(nickNameLayout);
        mainLayout->addLayout(accountLayout);
        mainLayout->addLayout(passwordLayout);
        mainLayout->addLayout(confirmPasswordLayout);
        mainLayout->addLayout(verificationCodeLayout);
        mainLayout->addWidget(registerButton);

        // 将mainLayout设置为ui->login_or_regist的布局
        ui->login_or_regist->setLayout(mainLayout);


        connect(registerButton, &QPushButton::clicked, [=](){
            QString account = accountLineEdit->text();
            QString nickname = nicknameLineEdit->text();
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
            else if(password.length()<6||password.length()>15)
            {
                QMessageBox::warning(this,"注册","密码长度不合法，长度应在6-15!");
                return;
            }
            else if(!account.contains('@'))
            {
                QMessageBox::warning(this,"注册","邮箱格式不正确!");
                return;
            }
            //正则表达式，密码至少一个字母、一个数字、一个特殊字符、长度6-15
            QRegularExpression passwordRegex("^(?=.*[A-Za-z])(?=.*\\d).{6,15}$");
            // 进行正则表达式匹配
            QRegularExpressionMatch match = passwordRegex.match(password);
            if (!match.hasMatch()) {
                QMessageBox::warning(this,"注册","密码应包含一个数字，一个字母!");
                return;
            }
            myNickName=new QString(nickname.toUtf8().constData());
            myAccount=new QString(account.toUtf8().constData());
            requestRegist(account,password,verificationCode);

        });
    }
}

