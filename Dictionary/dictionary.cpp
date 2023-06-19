#include "dictionary.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    rbtree=new RBTree;
    readCSV(*rbtree);
    rbtree->displayWordsInListWidget(ui->allWords);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readCSV(RBTree &rbTree)
{
    // 创建文件对象，用于打开并读取文件
    QFile file(":/EnWords.csv");

    // 根据文件名打开对应的文件，以只读和文本模式读取
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "导入单词信息", "导入单词信息失败！");
        return;
    }

    // in 用来从文本中读取数据
    QTextStream in(&file);

    // 读取数据直到文件末尾
    while (!in.atEnd())
    {
        // 读取一行数据并存储到 line 变量中
        QString line = in.readLine();

        // CSV 文件中的单词和汉译是以逗号分隔的，将这行文本根据逗号分隔开
        QStringList fields = line.split(',');

        // 列表的大小是否是2（单词-汉译）
        if (fields.size() == 2)
        {
            // 分别得到单词和汉译
            QString word = fields.at(0).trimmed();
            QString translation = fields.at(1).trimmed();
            // 去除单词和汉译中的双引号
            word.remove('"');
            translation.remove('"');
            // 插入单词和汉译到红黑树
            rbTree.insert(word, translation);
        }
    }

    file.close();
    QMessageBox::information(nullptr, "导入单词信息", "导入单词信息成功！");
}


RBTree *Widget::getRBTree()
{
    return rbtree;
}

void Widget::prefixSearch(Node *node, const QString &prefix, QList<QString> &results)
{
    //qDebug()<<"滴滴滴滴滴滴滴滴"<<"prefixSearch";
    //qDebug()<<prefix;
    if (!node)
        return ;

    // 判断当前节点是否与前缀匹配
    if (node->english.startsWith(prefix, Qt::CaseInsensitive))
    {
        //qDebug()<<"滴滴滴滴滴滴滴滴"<<"append";
        results.append(node->english);
    }

    // 递归搜索左子树和右子树
    prefixSearch(node->left, prefix, results);
    prefixSearch(node->right, prefix, results);
}

void Widget::displayWordsWithCharacter(const QString &character, const QList<QString> &wordList)
{
    // 清空 QListWidget
    ui->allWords->clear();

    // 遍历单词列表
    for (const QString& word : wordList) {
        // 检查单词是否包含输入字符
        if (word.contains(character, Qt::CaseInsensitive)) {
            // 创建 QListWidgetItem 并添加到 QListWidget
            QListWidgetItem* item = new QListWidgetItem(word);
            ui->allWords->addItem(item);
        }
    }
}

void Widget::traverseRBTree(Node *node, const QString &searchString, QList<QString> &results)
{
    if (!node)
        return;

    // 判断当前节点的单词是否包含搜索字符串
    if (node->english.contains(searchString, Qt::CaseInsensitive))
        results.append(node->english);

    // 递归遍历左子树和右子树
    traverseRBTree(node->left, searchString, results);
    traverseRBTree(node->right, searchString, results);
}


void Widget::on_allWords_itemClicked(QListWidgetItem *item)
{
    QString englishWord = item->text();

    // 在红黑树中查找对应的节点
    Node* node = rbtree->findNode(englishWord);
    if (node) {
        QString chineseTranslation = node->translation;

        // 更新 Label 和 Text Browser 的文本
        ui->english->setText(englishWord);
        ui->translate->setText(chineseTranslation);
    }
}

//这里处理模糊查询，每输入一个字母都会给出具体的模糊查询
void Widget::on_searchWord_textChanged(const QString &searchText)
{
    if(searchText.isEmpty())
    {
        rbtree->displayWordsInListWidget(ui->allWords);
        //ui->allWords->show();
    }
    else
    {
        qDebug()<<searchText;
        qDebug()<<"滴滴滴滴滴滴滴滴"<<"on_searchWord_textChanged";
        ui->allWords->clear();
        QList<QString> results;
        prefixSearch(rbtree->getRoot(), searchText, results);

        // 创建一个新的容器进行遍历
        QList<QString> resultsCopy = results;

        for (const QString& word : resultsCopy) {
            QListWidgetItem *item = new QListWidgetItem(word);
            ui->allWords->addItem(item);
        }
    }
}


void Widget::on_search_clicked()
{
    QString search = ui->searchWord->text();
//    if(search.isEmpty())
//    {
//        ui->allWords->show();
//    }
    // 创建一个用于存储结果的列表
    QList<QString> results;

    // 遍历红黑树并将包含搜索字符串的单词添加到结果列表中
    traverseRBTree(rbtree->getRoot(), search, results);

    // 清空 QListWidget
    ui->allWords->clear();

    // 将结果列表中的单词添加到 QListWidget 中显示
    for (const QString& word : results) {
        QListWidgetItem* item = new QListWidgetItem(word);
        ui->allWords->addItem(item);
    }
}

