#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Node{
public:
    Node* child[26];
    bool wordEnd;
    QString wordMeaning;

    Node(){
        this->wordEnd = false;
        for(int i = 0; i< 26; i++){
            this->child[i] = nullptr;
        }
    }
};

class Trie{
public:
    Node* root = nullptr;
    QString searchResult = nullptr;

    Trie(){
        root = new Node();
        searchResult = "";
    }
};

class MainWindow : public QMainWindow,public Node, public Trie
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void insert(QString word, QString wordMeaning);
    QString search(QString word);


private slots:
    void onClickSearch();

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
