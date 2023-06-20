#ifndef WIDGET_H
#define WIDGET_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QWidget>
#include <QMessageBox>
#include <QList>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //上传文件
    //显示文件
    //下载文件
private slots:
    void on_start_clicked();
    void handleNewConnection();
    void handleOffLine();
private:
    Ui::Widget *ui;
    QTcpServer* server;
    QList<QTcpSocket*>* clientSockets;
};
#endif // WIDGET_H
