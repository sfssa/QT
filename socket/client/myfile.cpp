#include "myfile.h"
#include "ui_myfile.h"

MyFile::MyFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyFile)
{
    ui->setupUi(this);
    // 连接按钮的点击信号到槽函数
    connect(ui->index, &QPushButton::clicked, this, &MyFile::onHomeButtonClicked);
    connect(ui->transform, &QPushButton::clicked, this, &MyFile::onTransferButtonClicked);
    connect(ui->friend_2, &QPushButton::clicked, this, &MyFile::onFriendsButtonClicked);
    connect(ui->myself, &QPushButton::clicked, this, &MyFile::onMyButtonClicked);
}

MyFile::~MyFile()
{
    delete ui;
}

void MyFile::onHomeButtonClicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget->addItem("我的文件");
    ui->listWidget->addItem("我的分享");
}

void MyFile::onTransferButtonClicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget->addItem("正在下载");
    ui->listWidget->addItem("正在上传");
    ui->listWidget->addItem("传输完成");
}

void MyFile::onFriendsButtonClicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    //从MySQL数据库提取出好友列表然后显示出来
}

void MyFile::onMyButtonClicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget->addItem("我的信息");
    ui->listWidget->addItem("修改密码");
}
