#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "obiekt.h"

class Rect : public Obiekt
{
public:
    Rect(const double x,const double y,const double a,const double b);
    virtual ~Rect(){};
    void setGeo(const double _x, const double _y, const double _a, const double _b) override;
    void insertPoints() override;
    void setPath() override;
};

class Circle : public Obiekt
{
public:
    Circle(const double x,const double y,const double a);
    virtual ~Circle(){};
    void setGeo(const double _x, const double _y, const double _a, const double _b) override;
    void insertPoints() override;
    void setPath() override;
    const QPointF getPos() override {return *pointCenter;};
};

class Lin : public Obiekt
{
public:
    Lin(const double x,const double y,const double a,const double b);
    virtual ~Lin(){};
    void setGeo(const double _x, const double _y, const double _a, const double _b) override;
    void insertPoints() override;
    void setPath() override;
};

class Cross : public Obiekt
{
public:
    Cross(const double x,const double y,const double a);
    virtual ~Cross(){};
    void setGeo(const double _x, const double _y, const double _a, const double _b = 0) override;
    void insertPoints() override;
    void setPath() override;
};

#endif // RECTANGLE_H
