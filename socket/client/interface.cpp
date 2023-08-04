#include "interface.h"


Interface::Interface()
{
    in_widget=new Widget;
    in_myfile=new MyFile;
    connect(in_widget,&Widget::loginSuccess,[=](){
        this->in_myfile->show();
        this->in_widget->hide();
    });
}

Widget *Interface::getWidget()
{
    return this->in_widget;
}

MyFile *Interface::getMyFile()
{
    return this->in_myfile;
}
