#include "interface.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface myinterface;

    myinterface.getWidget()->show();
    return a.exec();
}
