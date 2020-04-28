#include "objects.h"

Rect::Rect(const double x,const double y,const double a, const double b)
{
    setGeo(x,y,a,b);
    pen.setColor(Qt::white);
    insertPoints();
    this->state=STATE::EMPTY;
}

void Rect::setGeo(const double _x, const double _y, const double _a, const double _b)
{
    this->shape=RECTANGLE;
    a=_a;
    b=_b;
    pointA->setX(_x);
    pointA->setY(_y);
    pointB->setX(_x+_a);
    pointB->setY(_y);
    pointC->setX(_x+_a);
    pointC->setY(_y+_b);
    pointD->setX(_x);
    pointD->setY(_y+_b);

    double xB= pointB->x();
    double yB = pointB->y();
    double xC= pointC->x();
    double yC = pointC->y();
    double xD= pointD->x();
    double yD = pointD->y();

    pointAB->setX(xB-((xB-_x)/2));
    pointAB->setY(_y);

    pointBC->setX(xC);
    pointBC->setY(yC-((yC-yB)/2));

    pointCD->setX(xD-((xD-xC)/2));
    pointCD->setY(yD);

    pointDA->setX(xD);
    pointDA->setY(yD-((yD-_y)/2));

    pointCenter->setX(pointAB->x());
    pointCenter->setY(pointBC->y());

    setPath();
}

void Rect::insertPoints()
{
    points.push_back(pointA);
    intPoints.push_back(1);
    points.push_back(pointB);
    intPoints.push_back(1);
    points.push_back(pointC);
    intPoints.push_back(1);
    points.push_back(pointD);
    intPoints.push_back(1);
    points.push_back(pointAB);
    intPoints.push_back(0);
    points.push_back(pointBC);
    intPoints.push_back(0);
    points.push_back(pointCD);
    intPoints.push_back(0);
    points.push_back(pointDA);
    intPoints.push_back(0);
    points.push_back(pointCenter);
    intPoints.push_back(-1);
}

void Rect::setPath()
{
    path = QPainterPath();
    bound = QPainterPath();

    double dx = 5;
    double dy = 5;
    path.moveTo(*pointA);
    double _a = pointB->x()-pointA->x();
    double _b = pointC->y()-pointB->y();
    path.addRect(pointA->x(),pointA->y(),_a,_b);
    if(a<0)
        dx *= (-1);
    if(b<0)
        dy *= (-1);
    bound.moveTo(pointA->x()-dx,pointA->y()-dy);
    bound.lineTo(pointB->x()+dx,pointB->y()-dy);
    bound.lineTo(pointC->x()+dx,pointC->y()+dy);
    bound.lineTo(pointD->x()-dx,pointD->y()+dy);
    bound.closeSubpath();

}

Circle::Circle(const double x, const double y, const double a)
{
    setGeo(x,y,a,b);
    insertPoints();
}

void Circle::setGeo(const double _x, const double _y, const double _a, const double _b)
{
    this->shape=CIRCLE;
    a=_a;
    b=_b;
    pointCenter->setX(_x);
    pointCenter->setY(_y);
    pointA->setX(_x+a);
    pointA->setY(_y);
    pointB->setX(_x);
    pointB->setY(_y+a);
    pointC->setX(_x-a);
    pointC->setY(_y);
    pointD->setX(_x);
    pointD->setY(_y-a);
    setPath();
}

void Circle::insertPoints()
{
    points.push_back(pointA);
    intPoints.push_back(0);
    points.push_back(pointB);
    intPoints.push_back(0);
    points.push_back(pointC);
    intPoints.push_back(0);
    points.push_back(pointD);
    intPoints.push_back(0);
    points.push_back(pointCenter);
    intPoints.push_back(-1);
}

void Circle::setPath()
{
    path = QPainterPath();
    bound = QPainterPath();

    double dx = 5;
    path.moveTo(*pointA);
    path.addEllipse(*pointCenter,pointA->x()-pointCenter->x(),pointB->y()-pointCenter->y());
    double _a=pointA->x()-pointCenter->x();
    if(_a<0)
        dx *= (-1);
    _a+=(dx*2);
    bound.addEllipse(*pointCenter,_a,_a);
    bound.closeSubpath();
}

Lin::Lin(const double x,const double y,const double a,const double b)
{
    setGeo(x,y,a,b);
    insertPoints();
}

void Lin::setGeo(const double _x, const double _y, const double _a, const double _b)
{
    this->shape=LINE;
    a=_a;
    b=_b;
    pointA->setX(_x);
    pointA->setY(_y);
    pointB->setX(a);
    pointB->setY(b);
    pointCenter->setX(a-((a-pointA->x())/2));
    pointCenter->setY(b-((b-pointA->y())/2));
    setPath();
}

void Lin::insertPoints()
{
    points.push_back(pointA);
    intPoints.push_back(1);
    points.push_back(pointB);
    intPoints.push_back(1);
    points.push_back(pointCenter);
    intPoints.push_back(-1);
}

void Lin::setPath()
{
    path = QPainterPath();
    bound = QPainterPath();

    double dx = 5;
    double dy = 5;

    path.moveTo(*pointA);
    dx+=4;
    dy+=4;

    path.lineTo(*pointB);
    if(pointB->x()-pointA->x()<0)
        dx *=(-1);
    if(pointB->y()-pointA->y()<0)
        dy *=(-1);
    bound.moveTo(pointA->x()+dx,pointA->y()-dy);
    bound.lineTo(pointA->x()-dx,pointA->y()+dy);
    bound.lineTo(pointB->x()-dx,pointB->y()+dy);
    bound.lineTo(pointB->x()+dx,pointB->y()-dy);
    bound.closeSubpath();
}

Cross::Cross(const double x, const double y, const double a)
{
    setGeo(x,y,a);
    insertPoints();
}

void Cross::setGeo(const double _x, const double _y, const double _a, const double _b )
{
    this->shape=CROSS;
    a=_a;
    pointA->setX(_x-(_a/2));
    pointA->setY(_y-(_a/2));
    pointB->setX(_x+(_a/2));
    pointB->setY(_y+(_a/2));
    pointC->setX(_x-(_a/2));
    pointC->setY(_y+(_a/2));
    pointD->setX(_x+(_a/2));
    pointD->setY(_y-(_a/2));
    pointCenter->setX(_x);
    pointCenter->setY(_y);

    setPath();
}

void Cross::insertPoints()
{
    points.push_back(pointA);
    intPoints.push_back(1);
    points.push_back(pointB);
    intPoints.push_back(1);
    points.push_back(pointC);
    intPoints.push_back(1);
    points.push_back(pointD);
    intPoints.push_back(1);
    points.push_back(pointCenter);
    intPoints.push_back(-1);
}

void Cross::setPath()
{
    path = QPainterPath();
    bound = QPainterPath();

    double dx = 5;
    double dy = 5;
    path.moveTo(*pointA);
    path.lineTo(*pointB);
   // path.closeSubpath();

    path.moveTo(*pointC);
    path.lineTo(*pointD);
  //  path.closeSubpath();
    if(pointB->x()-pointA->x()<0)
        dx *=(-1);
    if(pointB->y()-pointA->y()<0)
        dy *=(-1);

    if(pointC->x()-pointD->x()<0)
        dx *=(-1);
    if(pointD->y()-pointC->y()<0)
        dy *=(-1);

    bound.moveTo(pointA->x()-dx,pointA->y()-dy);
    bound.lineTo(pointB->x()+dx,pointB->y()-dy);
    bound.lineTo(pointC->x()+dx,pointC->y()+dy);
    bound.lineTo(pointD->x()-dx,pointD->y()+dy);
    bound.closeSubpath();
}
