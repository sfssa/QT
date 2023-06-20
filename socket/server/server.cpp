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

Widget::~Widget()
{
    server->close();
    delete ui;
    delete server;
}


void Widget::on_start_clicked()
{
    if(server->listen(QHostAddress::Any,12345))
    {
        QMessageBox::information(this,"服务器开启","服务器开启成功！正在监听连接...");
        //绑定连接和断开连接的槽函数
        connect(server,SIGNAL(QTcpServer::newConnection),this,SLOT(handleNewConnection));
        connect(server,SIGNAL(QTcpServer::disconnected),this,SLOT(handleOffLine));
    }else
    {
        QMessageBox::warning(this,"服务器开启","服务器开启失败！无法监听连接...");
        qDebug()<<"服务器出错："<<server->errorString();
    }
}

void Widget::handleNewConnection()
{

}

void Widget::handleOffLine()
{

}

