#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "rbtree.h"
#include <QListWidget>
#include <QFile>
#include <QMessageBox>
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
    void readCSV(RBTree &rbTree);
    RBTree* getRBTree();
    void prefixSearch(Node* node, const QString& prefix, QList<QString>& results);
    void displayWordsWithCharacter(const QString& character, const QList<QString>& wordList);
    void traverseRBTree(Node* node, const QString& searchString, QList<QString>& results);
private slots:


    void on_allWords_itemClicked(QListWidgetItem *item);

    void on_searchWord_textChanged(const QString &searchText);

    void on_search_clicked();

private:
    Ui::Widget *ui;
    RBTree* rbtree;
};
#endif // WIDGET_H
