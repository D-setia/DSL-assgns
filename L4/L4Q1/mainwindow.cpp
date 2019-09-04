#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputField->setPlaceholderText("Your word");
    connect(ui->inputField, SIGNAL(returnPressed()),ui->searchButton, SIGNAL(clicked()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(onClickSearch()));
}

    void MainWindow:: onClickSearch(){
        QString word=ui->inputField->text();
        QString meaning=search(word);
        ui->displayMeaning->setPlainText(meaning);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: insert(QString word, QString wordMeaning){
    word = word.toLower();
    wordMeaning = wordMeaning.toLower();
    Node* node=root;
    for(int i=0;i<word.length();i++)
    {
        int letter=word[i].toLatin1()- 97;
        if(!node->child[letter])
        {
            Node* newNode=new Node();
            node->child[letter]=newNode;
        }
        node=node->child[letter];
    }
    node->wordEnd=true;
    node->wordMeaning=wordMeaning;
}


QString MainWindow:: search(QString word)
{
    Node* node=root;
    for(int i=0;i<word.length();i++)
    {
        int letter=word[i].toLatin1()- 97;
        if(!node->child[letter])
            return "Word not found";
        node=node->child[letter];
    }
    if(node->wordEnd){
        QString temp;
        temp = node->wordMeaning;
        return temp;
    }else{
        return "Word not found";
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString word=ui->inputField->text();
    QString meaning=search(word);
    ui->displayMeaning->setPlainText(meaning);
}
