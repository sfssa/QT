#include "server.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server=new QTcpServer(this);
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

            break;
        }
        default:
            break;
        }
    }
}

Widget::~Widget()
{
    server->close();
    delete ui;
    delete server;
    //遍历容器释放每个指针的空间
    qDeleteAll(*clientSockets);
    //释放容器指针的空间
    delete clientSockets;
}


void Widget::on_start_clicked()
{
    if(server->listen(QHostAddress::Any,12345))
    {
        QMessageBox::information(this,"服务器开启","服务器开启成功！正在监听连接...");
        //绑定连接和断开连接的槽函数
        connect(server, &QTcpServer::newConnection, this, &Widget::handleNewConnection);        
    }else
    {
        QMessageBox::critical(this,"服务器开启","服务器开启失败！无法监听连接...");
        qDebug()<<"服务器出错："<<server->errorString();
    }
}

void Widget::handleNewConnection()
{
    while(server->hasPendingConnections())
    {
        //qDebug()<<"new connection"<<"添加新数据";
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

