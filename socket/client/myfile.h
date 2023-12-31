#ifndef MYFILE_H
#define MYFILE_H

#include <QWidget>

namespace Ui {
class MyFile;
}

class MyFile : public QWidget
{
    Q_OBJECT

public:
    explicit MyFile(QWidget *parent = nullptr);
    ~MyFile();
public slots:
    void onHomeButtonClicked();
    void onTransferButtonClicked();
    void onFriendsButtonClicked();
    void onMyButtonClicked();

private:
    Ui::MyFile *ui;
};

#endif // MYFILE_H
