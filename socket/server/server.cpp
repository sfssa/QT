#include "server.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server=new QTcpServer(this);
    db=new opeDB;
    clientSockets=new QList<QTcpSocket*>();
}

void Widget::handleMSG()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj=doc.object();
        int type=jsonObj["type"].toInt();
        switch(type)
        {
        case REGIST_REQUEST:
        {
            QJsonObject data;
            //判断验证码是否正确
            QString value=myMap.value(clientSocket);
            qDebug()<<"value of code is : "<<value;
            QString conCode=jsonObj["verificationCode"].toString();
            qDebug()<<"value of code recv is "<<conCode;
            if(value!=conCode)
            {
                //验证码不正确
                data["type"]=CODE_NONCONRECT;
            }
            else {
                //调用MYSQL将数据添加到MYSQL中
                QString account=jsonObj["account"].toString();
                QString passwd=jsonObj["passwd"].toString();

                if(db->inSertIntoDB(account,passwd))
                {
                    //插入成功
                    data["type"]=REGIST_SUCCESS;
                }
                else
                {
                    //插入失败
                    data["type"]=REGIST_FAILED;
                }
            }
            QJsonDocument doc(data);
            QByteArray jsonData=doc.toJson();
            clientSocket->write(jsonData);
            if(!clientSocket->waitForBytesWritten())
            {
                qDebug()<<"发送regist_success失败";
            }
            qDebug()<<"滴滴滴滴滴"<<type;
            break;
        }
        case REQUEST_CODE:
        {
            //QTcpSocket* curentSocket=qobject_cast<QTcpSocket*>(sender());
            QString receiver=jsonObj["receiver"].toString();
            //检查账户是否存在
            if(db->isExistInDB(receiver))
            {
                qDebug()<<"账号已经存在";
                QJsonObject data;
                data["type"]=RESPONSE_CODE_ISEXIST;
                QJsonDocument doc(data);
                QByteArray jsonData=doc.toJson();
                clientSocket->write(jsonData);
                if(!clientSocket->waitForBytesWritten())
                {
                    delete clientSocket;
                }
                return;
            }
            else
            {
                qDebug()<<"接收到验证码请求";
                //生成验证码并获得客户端socket后保存
                // 生成长度为6的验证码
                QString code = generateVerificationCode(6);
                qDebug()<<"滴滴滴滴滴"<<code;

                //verificationCodes.first=clientSocket;
                //verificationCodes.second=code;
                myMap.insert(clientSocket,code);
                QString emailContent = QString("Your confirm code is ：%1").arg(code);
                Smtp *sendMail=new Smtp;
                if(sendMail->Send(receiver,"Confirm Code",emailContent))
                {
                    if(sendMail->PutSendLine())
                    {
                        qDebug()<<"发送成功！";
                    }
                    else
                    {
                        qDebug()<<"发送失败！";
                    }
                }
            }
        }
        default:
            break;
        }
        if(clientSocket)
            delete clientSocket;
    }
}

//void Widget::responseForCode(const QString &code)
//{
//    QJsonObject data;
//    data["type"]=RESPONSE_CODE;
//    data["code"]=code;
//    QJsonDocument doc(data);
//    QByteArray jsonData=doc.toJson();

//}

Widget::~Widget()
{
    server->close();
    delete ui;
    delete server;
    threadPool.shutdown();
    //遍历容器释放每个指针的空间
    qDeleteAll(*clientSockets);
    //释放容器指针的空间
    delete clientSockets;
}

QString Widget::generateVerificationCode(int length)
{
    const QString characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    QString verificationCode;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(characters.length());
        verificationCode.append(characters.at(index));
    }

    return verificationCode;
}

void Widget::sendMail(const QString &receiver,const QString& str)
{
    // 创建一个套接字对象
     QTcpSocket socket;

     // 连接到SMTP服务器
     socket.connectToHost("smtp.example.com", 25); // SMTP服务器的地址和端口号

     if (!socket.waitForConnected()) {
         qDebug() << "Failed to connect to SMTP server:" << socket.errorString();
         return;
     }

     // 读取服务器响应
     if (!socket.waitForReadyRead()) {
         qDebug() << "Failed to receive response from SMTP server:" << socket.errorString();
         return;
     }

     // 发送命令和数据给SMTP服务器
     socket.write("HELO localhost\r\n");
     socket.write("MAIL FROM: <1664549131@qq.com>\r\n"); // 发件人邮箱
     socket.write(QString("RCPT TO: <%1>\r\n").arg(receiver).toUtf8()); // 收件人邮箱
     socket.write("DATA\r\n");
     socket.write("Subject: Confirm Code\r\n"); // 邮件主题
     socket.write("From: atpdxy <1664549131@qq.com>\r\n"); // 发件人姓名和邮箱
     socket.write(QString("To: <%1>\r\n").arg(receiver).toUtf8()); // 收件人邮箱
     socket.write("\r\n");
     socket.write(str.toUtf8()); // 邮件正文内容
     socket.write("\r\n.\r\n");
     socket.write("QUIT\r\n");

     // 等待服务器响应
     if (!socket.waitForReadyRead()) {
         qDebug() << "Failed to receive response from SMTP server:" << socket.errorString();
         return;
     }

     // 读取服务器的响应数据
     QString response = socket.readAll();
     qDebug() << "SMTP server response:" << response;

     // 关闭连接
     socket.close();
}


void Widget::on_start_clicked()
{
    if(server->listen(QHostAddress::Any,12345))
    {
        qDebug()<<"服务器开启成功！正在监听连接...";
        //绑定连接和断开连接的槽函数
        connect(server, &QTcpServer::newConnection, this, &Widget::handleNewConnection);        
        ui->start->setEnabled(false);

    }else
    {
        qDebug()<<"服务器开启失败！无法监听连接...";
        qDebug()<<"服务器出错："<<server->errorString();
    }
}

void Widget::handleNewConnection()
{
    while(server->hasPendingConnections())
    {
        qDebug()<<"new connection"<<"添加新数据";
        //当有客户端请求连接时，服务器会将连接放入到队列中等待处理，而nextPendingConnection函数用于从队列中获取下一个挂起的队列
        QTcpSocket* newSocket = server->nextPendingConnection();
        clientSockets->append(newSocket);
        //这里设置断开连接更合适，不适合在构造中绑定，你得先确定连接才会断开
        connect(newSocket, &QTcpSocket::disconnected, this, &Widget::handleOffLine);
        connect(newSocket,&QTcpSocket::readyRead,this,&Widget::handleMSG);
    }
}

void Widget::handleOffLine()
{
    //得到发送断开连接信号的对象，并通过类似静态转换指针的方式安全转换成socket
    QTcpSocket* disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (disconnectedSocket)
    {
        //qDebug()<<"断开连接";
        clientSockets->removeAll(disconnectedSocket);
        disconnectedSocket->deleteLater();
    }
}


