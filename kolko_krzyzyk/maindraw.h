#ifndef MAINDRAW_H
#define MAINDRAW_H
#include <QFrame>
#include <QtCore>
#include <QtGui>
#include <QPainter>
#include <QLineF>
#include "objects.h"
#include <QKeyEvent>
#include "gamecontroller.h"

class MainDraw : public QFrame
{
    Q_OBJECT

public:
    MainDraw(QWidget* parent=nullptr);
    void addObject(SHAPE shape,double x,double y, double a,double b=0, POSITION p=LEFT_TOP);
    void changeShape(SHAPE shape);
    void clear();
    void draw_board();

private:
    Obiekt *ob,*tmp;

    QList<Obiekt*> vObjectList;

    QPointF mouseClick,mouseMove,begin,second;
    GameController gc;
    QPointF* changing;

    SHAPE shape;

    bool pressed;

    double changeX,changeY;
    QPainter painter;
    int paintSize;
    double distance(double x1,double y1, double x2, double y2);

public slots:
    void someoneClicked();
    void edit(double x,double y,double a,double b);
    //void fill(QColor color);
    void deleteObiekt();
    //void tekst(int d);
  // void setBoundColor(QColor color);
    void reset();
protected:
    void paintEvent(QPaintEvent* event);
 //   void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
//    void mouseReleaseEvent(QMouseEvent* event);


signals:
    //void change(int shape,double x,double y,double a, double b=0);
    void player(QString name);
    void finish(int res,QString playerName);

};

#endif // MAINDRAW_H
