#include "obiekt.h"
#include <QMessageBox>
#include <QPainter>
#include <iostream>
#include <QDebug>
#include <cmath>

Obiekt::Obiekt()
{
    pointA = new QPointF();
    pointB = new QPointF();
    pointC = new QPointF();
    pointD = new QPointF();
    pointAB = new QPointF();
    pointBC = new QPointF();
    pointCD = new QPointF();
    pointDA = new QPointF();
    pointCenter = new QPointF();
    marked = nullptr;
    pen = QPen();
   // color = QColor();
}
Obiekt::Obiekt(const double x,const double y,const double a,const double b)
    :Obiekt()
{

}

QPainterPath Obiekt::getPath()
{
    return this->path;
}

SHAPE Obiekt::getShape()
{
    return this->shape;
}

const QPointF Obiekt::getPos()
{
    return *pointA;
}

void Obiekt::clear()
{
    path = QPainterPath();
    bound = QPainterPath();
    delete pointA;
    delete pointB;
    delete pointC;
    delete pointD;
    delete pointAB;
    delete pointBC;
    delete pointCD;
    delete pointDA;

    pointA = new QPointF();
    pointB = new QPointF();
    pointC = new QPointF();
    pointD = new QPointF();
    pointAB = new QPointF();
    pointBC = new QPointF();
    pointCD = new QPointF();
    pointDA = new QPointF();
    a=0;
    b=0;
    //shape=NONE;
}

bool Obiekt::isInPath(QPointF point)
{
    return bound.contains(point);
}

const QPointF Obiekt::getCenterPoint()
{
    return *pointCenter;
}

const QPointF Obiekt::getPoint(int index)
{
        return *points[index];
}

QPen& Obiekt::getPen()
{
    return this->pen;
}
