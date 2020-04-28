#include "maindraw.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <math.h>

MainDraw::MainDraw(QWidget* parent)
    :QFrame (parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    this->setMouseTracking(true);
    paintSize = QPen().width();
    qDebug()<<"asdsa"<<paintSize;
    pressed=false;
    ob = nullptr;
    changing = nullptr;
    //shape=NONE;

    tmp = new Obiekt();
    draw_board();

    connect(&gc,&GameController::player,this,&MainDraw::player);
    connect(&gc,&GameController::stop,this,&MainDraw::finish);
}

void MainDraw::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
  /*  QBrush brushTmp = painter.brush();
    QPen temp = painter.pen();
    temp.setWidth(paintSize);*/
    for(Obiekt* v : vObjectList)
    {
        QPen temp1 = v->getPen();
        painter.setPen(temp1);
        painter.drawPath(v->getPath());

    }
    /*painter.setPen(temp);
    painter.setBrush(brushTmp);
    tmp->setPenSize(temp.width());
    painter.drawPath(tmp->getPath());*/
    painter.end();
}

void MainDraw::mousePressEvent(QMouseEvent *event)
{
 //  QFrame::mousePressEvent(event);
    mouseClick = QPointF(event->localPos().x(),event->localPos().y());
    if(event->button()==Qt::LeftButton)
    {
        bool founded=false;
        pressed=true;
        //if(this->shape==NONE)
        {
            for(Obiekt* v : vObjectList)
            { 
                if(v->getShape()!=SHAPE::RECTANGLE)
                    continue;
                if(v->isInPath(QPointF(event->pos().x(),event->pos().y())))
                {
                    ob = v;
                    founded = true;
                }
                if(founded)
                {
                    if(ob->get_state()!=STATE::EMPTY)
                    {
                        QMessageBox(QMessageBox::Warning,"","To pole jest juz zaznaczone",QMessageBox::Ok,this).exec();
                        ob=nullptr;
                        break;
                    }
                    {
                        SHAPE s;
                        int r;
                        if(gc.value_pos()==1)
                        {
                            s=SHAPE::CROSS;
                            r=50;
                        }
                        else
                        {
                            s=SHAPE::CIRCLE;
                            r=25;
                        }

                         this->addObject(s,ob->getCenterPoint().x(),ob->getCenterPoint().y(),25);
                         ob->set_state(STATE::X);
                         gc.set_sign(ob->get_pos());
                         ob=nullptr;
                         break;
                    }

                  /*  emit change(ob->getShape(),ob->getPos().x(),ob->getPos().y(),ob->getA(),ob->getB());
                    QPointF* asd = ob->markPoint(QPointF(mouseClick.x(),mouseClick.y()));
                    if(asd!=nullptr)
                    {
                        begin = *asd;
                    }
                    else
                    {
                        begin = ob->getPos();
                        second = ob->getPoint(1);
                    }
                    break;*/
                }
            }
        }
        if(!founded)
        {
            ob=nullptr;
            //emit none();
        }
    }
}

//void MainDraw::mouseReleaseEvent(QMouseEvent* event)


//void MainDraw::mouseMoveEvent(QMouseEvent* event)


void MainDraw::addObject(SHAPE shape,double x,double y,double a,double b,POSITION p)
{
    Obiekt* now = nullptr;
    switch(shape)
    {
        case RECTANGLE:
            now = new Rect(x,y,a,b);
        break;
        case CIRCLE:
            now = new Circle(x,y,a);
        break;
        case CROSS:
            now = new Cross(x,y,a);
        break;
        case LINE:
            now = new Lin(x,y,a,b);
        break;
    }

    if(now!=nullptr)
    {
        now->set_pos(p);
        vObjectList.push_back(now);
        update();
    }
}

void MainDraw::changeShape(SHAPE shape)
{
    this->shape=shape;
}

void MainDraw::clear()
{
    for(Obiekt* v : vObjectList)
    {
        delete (v);
    }
    tmp->clear();
    vObjectList.clear();
    draw_board();
    update();
}

double MainDraw::distance(double x1,double y1, double x2,double y2)
{
    return sqrt(((x2-x1)*(x2-21))+((y2-y1)*(y2-y1)));
}

void MainDraw::someoneClicked()
{
    QMessageBox(QMessageBox::Information,"","",QMessageBox::Ok,this).exec();
}

void MainDraw::edit(double x,double y,double a,double b)
{
    //ob->setGeo(ob->getShape(),x,y,a,b);
    update();
}

/*
void MainDraw::fill(QColor color)
{
    if(ob!=nullptr)
        ob->setColor(color);
    update();
}*/

/*void MainDraw::setBoundColor(QColor color)
{
    if(ob!=nullptr)
        ob->getPen().setColor(color);
    update();
}*/

void MainDraw::deleteObiekt()
{
    if(ob!=nullptr)
        for(int i=0;i<vObjectList.length();i++)
        {
            if(vObjectList[i]==ob)
            {
                delete vObjectList[i];
                vObjectList.removeAt(i);
                ob = nullptr;
                break;
            }
        }
    update();
}

/*void MainDraw::tekst(int d)
{
    if(ob!=nullptr)
        ob->setPenSize(d);
    paintSize=d;
    update();
}*/

void MainDraw::reset()
{
    gc.reset();
}

void MainDraw::draw_board()
{
    this->addObject(SHAPE::RECTANGLE,100,100,100,100,LEFT_TOP);
    this->addObject(SHAPE::RECTANGLE,202,100,100,100,CENT_TOP);
    this->addObject(SHAPE::RECTANGLE,304,100,100,100,RIGHT_TOP);
    this->addObject(SHAPE::LINE,100,201,404,201);

    this->addObject(SHAPE::RECTANGLE,100,202,100,100,LEFT_CENT);
    this->addObject(SHAPE::RECTANGLE,202,202,100,100,CENT_CENT);
    this->addObject(SHAPE::RECTANGLE,304,202,100,100,RIGHT_CENT);
    this->addObject(SHAPE::LINE,100,303,404,303);

    this->addObject(SHAPE::RECTANGLE,100,304,100,100,LEFT_BOT);
    this->addObject(SHAPE::RECTANGLE,202,304,100,100,CENT_BOT);
    this->addObject(SHAPE::RECTANGLE,304,304,100,100,RIGHT_BOT);

    this->addObject(SHAPE::LINE,303,100,303,405);
    this->addObject(SHAPE::LINE,201,100,201,405);
}
