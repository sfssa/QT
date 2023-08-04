/********************************************************************************
** Form generated from reading UI file 'myfile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFILE_H
#define UI_MYFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyFile
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *index;
    QSpacerItem *verticalSpacer;
    QPushButton *transform;
    QSpacerItem *verticalSpacer_2;
    QPushButton *friend_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *myself;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;
    QSpacerItem *horizontalSpacer_2;
    QListWidget *listWidget_2;

    void setupUi(QWidget *MyFile)
    {
        if (MyFile->objectName().isEmpty())
            MyFile->setObjectName(QString::fromUtf8("MyFile"));
        MyFile->resize(419, 264);
        verticalLayout_2 = new QVBoxLayout(MyFile);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        index = new QPushButton(MyFile);
        index->setObjectName(QString::fromUtf8("index"));

        verticalLayout->addWidget(index);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        transform = new QPushButton(MyFile);
        transform->setObjectName(QString::fromUtf8("transform"));

        verticalLayout->addWidget(transform);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        friend_2 = new QPushButton(MyFile);
        friend_2->setObjectName(QString::fromUtf8("friend_2"));

        verticalLayout->addWidget(friend_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        myself = new QPushButton(MyFile);
        myself->setObjectName(QString::fromUtf8("myself"));

        verticalLayout->addWidget(myself);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(18, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        listWidget = new QListWidget(MyFile);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        listWidget_2 = new QListWidget(MyFile);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        horizontalLayout->addWidget(listWidget_2);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(MyFile);

        QMetaObject::connectSlotsByName(MyFile);
    } // setupUi

    void retranslateUi(QWidget *MyFile)
    {
        MyFile->setWindowTitle(QApplication::translate("MyFile", "Form", nullptr));
        index->setText(QApplication::translate("MyFile", "\351\246\226\351\241\265", nullptr));
        transform->setText(QApplication::translate("MyFile", "\344\274\240\350\276\223", nullptr));
        friend_2->setText(QApplication::translate("MyFile", "\345\245\275\345\217\213", nullptr));
        myself->setText(QApplication::translate("MyFile", "\346\210\221\347\232\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyFile: public Ui_MyFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFILE_H
