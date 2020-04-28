#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maindraw.h"
#include <QLineEdit>
#include <QColorDialog>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_shapeNone_2_clicked(bool checked);
    void player_changed(QString name);
    void game_finished(int res,QString playerName);

signals:
    void zmien(double x,double y,double a, double b);
    void fill(QColor color);
    void deleteObiekt();
    void tekst(int d);
    void border(QColor color);
private:
    Ui::MainWindow *ui;
    MainDraw* mainDraw;
    QLineEdit *line1,*line2,*line3,*line4;
    QColorDialog *pickColor;
    QColor sColor;
    double r,g,b;
    double c,m,y,k;
};

#endif // MAINWINDOW_H
