#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <QListWidget>
#include <QString>
#include <QtDebug>

enum Color{
    RED,
    BLACK
};

struct Node {
    QString english;
    QString translation;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(const QString eng, const QString trans)
        : english(eng), translation(trans), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree
{
public:
    RBTree();
    void insert(const QString& english, const QString& translation);
    void printInorderTraversal();
    Node* getRoot();
    void displayWordsInListWidget(QListWidget* listWidget);
    Node* findNode(const QString& englishWord) const;
private:
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void fixInsert(Node* node);
    void inorderTraversal(Node* node);
    void inorderTraversal(Node* node, QStringList& wordList);

private:
    Node* root;
};

#endif // RBTREE_H
