#include "rbtree.h"

RBTree::RBTree()
    :root(nullptr)
{

}

void RBTree::insert(const QString& english, const QString& translation)
{
    Node* newNode = new Node(english, translation);
    Node* current = root;
    Node* parent = nullptr;
    while (current) {
        parent = current;
        if (english < current->english) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    newNode->parent = parent;
    if (!parent) {
        root = newNode;
    } else if (english < parent->english) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    fixInsert(newNode);
}

void RBTree::printInorderTraversal()
{
    inorderTraversal(root); // 使用类的成员访问运算符调用成员函数
}

void RBTree::leftRotate(Node *node)
{
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr)
        rightChild->left->parent = node;
    rightChild->parent = node->parent;
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}

void RBTree::rightRotate(Node *node)
{
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr)
        leftChild->right->parent = node;
    leftChild->parent = node->parent;
    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}

void RBTree::fixInsert(Node *node)
{
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::inorderTraversal(Node *node)
{
    if (node) {
        inorderTraversal(node->left);
        qDebug()<<node->english<<":"<<node->translation;
        inorderTraversal(node->right);
    }

}

void RBTree::inorderTraversal(Node *node, QStringList &wordList)
{
    if (node) {
        inorderTraversal(node->left, wordList);
        wordList.append(node->english);
        inorderTraversal(node->right, wordList);
    }
}

Node *RBTree::getRoot()
{
    return root;
}

void RBTree::displayWordsInListWidget(QListWidget *listWidget)
{
    // 创建 QStringList 存储英文单词
    QStringList wordList;

    // 遍历红黑树获取所有的英文单词
    inorderTraversal(root, wordList);

    // 清空 QListWidget
    listWidget->clear();

    // 将英文单词添加到 QListWidget
    listWidget->addItems(wordList);
}

Node *RBTree::findNode(const QString &englishWord) const
{
    Node* current = root;

    // 从根节点开始搜索
    while (current) {
        if (englishWord < current->english) {
            current = current->left;
        } else if (englishWord > current->english) {
            current = current->right;
        } else {
            // 找到匹配的节点
            return current;
        }
    }

    // 未找到匹配的节点
    return nullptr;
}


