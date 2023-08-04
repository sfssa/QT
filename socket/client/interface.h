#ifndef INTERFACE_H
#define INTERFACE_H
#include "client.h"
#include "myfile.h"

class Interface: public QWidget
{
    Q_OBJECT
public:
    Interface();
    Widget* getWidget();
    MyFile* getMyFile();
private:
    Widget* in_widget;
    MyFile* in_myfile;
};

#endif // INTERFACE_H
