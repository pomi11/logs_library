#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->addMenu("test");
    mainDraw = new MainDraw(this);
    connect(mainDraw,&MainDraw::player,this,&MainWindow::player_changed);
    connect(mainDraw,&MainDraw::finish,this,&MainWindow::game_finished);
    QRect tst = this->geometry();
    tst.setHeight(tst.height()-21);
    tst.moveTop(21);
    mainDraw->setGeometry(tst);
    mainDraw->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shapeNone_2_clicked(bool checked)
{
    mainDraw->clear();
}

void MainWindow::player_changed(QString name)
{
    QMessageBox(QMessageBox::Warning,"",name+", czas na twoj ruch!",QMessageBox::Ok,this).exec();
}
void MainWindow::game_finished(int res,QString playerName)
{
    if(res==1)
        QMessageBox(QMessageBox::Warning,"",playerName+" wygral!",QMessageBox::Ok,this).exec();
    else
       QMessageBox(QMessageBox::Warning,"","Nikt nie wygral!",QMessageBox::Ok,this).exec();

    mainDraw->clear();
    mainDraw->reset();
}
