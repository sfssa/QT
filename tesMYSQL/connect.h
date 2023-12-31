#ifndef WIDGET_H
#define WIDGET_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QSqlDatabase db;
};
#endif // WIDGET_H
