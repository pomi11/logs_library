#ifndef OBIEKT_H
#define OBIEKT_H
#include <QMap>
#include <QWidget>
#include <QPen>

enum SHAPE{LINE,RECTANGLE,CIRCLE,CROSS};

enum STATE{X,O,EMPTY};

enum POSITION
{
    LEFT_TOP,
    CENT_TOP,
    RIGHT_TOP,
    LEFT_CENT,
    CENT_CENT,
    RIGHT_CENT,
    LEFT_BOT,
    CENT_BOT,
    RIGHT_BOT
};

class Obiekt
{
public:
    Obiekt();
    virtual ~Obiekt(){};
    virtual QPainterPath getPath();
    virtual void clear();
    virtual void setPath(){};
    virtual void setGeo(const double _x,const double _y,const double _a,const double _b){};
    virtual SHAPE getShape();

    virtual const QPointF getCenterPoint();
    virtual const QPointF getPos();
    virtual const QPointF getPoint(int index);
    virtual bool isInPath(QPointF point);
    virtual void set_state(STATE s) {this->state = s;};
    virtual STATE get_state() {return state;};
    virtual POSITION get_pos() {return this->pos;};
    virtual void set_pos(POSITION p){this->pos = p;};

    virtual void insertPoints(){};

    virtual QPen& getPen();
    Obiekt(const double x,const double y,const double a,const double b=0); // dla każdej klasy oddzielnie
private:



protected:

   //void mousePressEvent(QMouseEvent* event);
    double a,b;
    QList<int> intPoints;
     QList<QPointF*> points;//L,pointsR,pointsC;
     QPainterPath path;
     QPainterPath bound;
     QPointF *pointA,*pointB,*pointC,*pointD,*pointAB,*pointBC,*pointCD,*pointDA,*pointCenter,*marked;
     SHAPE shape;
  //   QColor color;
     POSITION pos;
     QPen pen;
     STATE state;
  //   int penSize;
};




#endif // OBIEKT_H
