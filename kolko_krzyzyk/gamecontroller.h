#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <include/logs.h>
#include "obiekt.h"

class GameController : public QObject
{
    Q_OBJECT
private:
    LOGS log;
    int LEFT_TOP = 0, LEFT_CENT = 0, LEFT_BOT =0, CENT_TOP = 0, CENT_CENT = 0, CENT_BOT = 0, RIGHT_TOP = 0, RIGHT_CENT = 0, RIGHT_BOT = 0;
    QString playerName = "player_1";
    int gameNum=1;
public:
    GameController();
    int check();
    void stop_watches();
    void set_sign(POSITION pos);
    int value_pos();
    void change_player(bool isEmit = true);
    void reset();
signals:
    void stop(int res,QString playerName);
    void player(QString player);
};

#endif // GAMECONTROLLER_H
