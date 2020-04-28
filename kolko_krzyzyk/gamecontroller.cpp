#include "gamecontroller.h"

GameController::GameController()
{
    log.set_file_name("game_result.xml");
    log.set_file_path(QDir::homePath()+"/");
    log.show_file_date(true);
    log.show_sys_summary(false);
    log.show_log_header(false);
    reset();
}

int GameController::check()
{
    int sum_top = LEFT_TOP+CENT_TOP+RIGHT_TOP;
    int sum_cent_hor = LEFT_CENT+CENT_CENT+RIGHT_CENT;
    int sum_bot = LEFT_BOT+CENT_BOT+RIGHT_BOT;
    int sum_left = LEFT_TOP+LEFT_CENT+LEFT_BOT;
    int sum_cent_vert = CENT_TOP+CENT_CENT+CENT_BOT;
    int sum_right = RIGHT_TOP+RIGHT_CENT+RIGHT_BOT;

    int diagonally_1 = RIGHT_BOT+CENT_CENT+LEFT_TOP;
    int diagonally_2 = LEFT_BOT+CENT_CENT+RIGHT_TOP;

    if(sum_top == 3 || sum_top == -3 || sum_cent_hor == 3 || sum_cent_hor == -3 || sum_bot ==3 || sum_bot == -3 ||
            sum_left == 3 || sum_left == -3 || sum_cent_vert == 3 || sum_cent_vert == -3 || sum_right == 3 || sum_right == -3 ||
            diagonally_1 ==3 || diagonally_1 == -3 || diagonally_2 == 3 || diagonally_2 == -3)
    {
       // stop_watches();
        log.add_msg("Wygrywa gracz "+this->playerName);
        log.save();

        emit stop(1,playerName);
      //  change_player(false);


        return 1;
    }
    if(LEFT_BOT!=0 && LEFT_TOP !=0 && LEFT_CENT !=0 &&
            CENT_BOT!=0 && CENT_TOP !=0 && CENT_CENT !=0 &&
            RIGHT_BOT!=0&&RIGHT_TOP !=0 && RIGHT_CENT !=0)
    {
       // stop_watches();

        log.add_msg("Gra zakonczona remisem");

        log.save();
        emit stop(2,"");
        //change_player(false);

        return 2;
    }
    return 0;
}

void GameController::stop_watches()
{
    log.stop_watch("LEFT_TOP");
    log.stop_watch("LEFT_CENT");
    log.stop_watch("LEFT_BOT");
    log.stop_watch("RIGHT_TOP");
    log.stop_watch("RIGHT_CENT");
    log.stop_watch("RIGHT_BOT");
    log.stop_watch("CENT_TOP");
    log.stop_watch("CENT_CENT");
    log.stop_watch("CENT_BOT");
    log.stop_watch("PlayerName");
}

void GameController::set_sign(POSITION pos)
{
    QString polozenie;
    switch(pos)
    {
    case POSITION::LEFT_TOP:
        LEFT_TOP+=value_pos();
        polozenie = "w lewym gornym polu";
        break;
    case POSITION::LEFT_BOT:
        LEFT_BOT+=value_pos();
        polozenie = "w lewym dolnym polu";
        break;
    case POSITION::LEFT_CENT:
        LEFT_CENT+=value_pos();
        polozenie = "w lewym srodkowym polu";
        break;
    case POSITION::RIGHT_BOT:
        RIGHT_BOT+=value_pos();
        polozenie = "w prawym dolnym polu";
        break;
    case POSITION::RIGHT_TOP:
        RIGHT_TOP+=value_pos();
        polozenie = "w prawym gornym polu";
        break;
    case POSITION::RIGHT_CENT:
        RIGHT_CENT+=value_pos();
        polozenie = "w prawym srodkowym polu";
        break;
    case POSITION::CENT_BOT:
        CENT_BOT+=value_pos();
        polozenie = "w dolnym srodkowym polu";
        break;
    case POSITION::CENT_CENT:
        CENT_CENT+=value_pos();
        polozenie = "w srodkowym polu";
        break;
    case POSITION::CENT_TOP:
        CENT_TOP+=value_pos();
        polozenie = "w gornym srodkowym polu";
        break;
    }
    log.add_msg(playerName+" postawil znak "+(value_pos()==1 ? "X" : "O")+" "+polozenie);
    check();
    change_player();
}

int GameController::value_pos()
{
    if(playerName=="player_1")
        return 1;
    else
        return -1;
}

void GameController::change_player(bool isEmit)
{
    if(playerName=="player_1")
        playerName = "player_2";
    else
        playerName = "player_1";

    log.add_msg("Ruch wykonuje "+playerName);
    if(isEmit)
        emit player(playerName);
}

void GameController::reset()
{
    gameNum++;
    log.set_file_name("game_result_"+QString::number(gameNum)+".xml");

    LEFT_TOP=0;
    LEFT_CENT=0;
    LEFT_BOT=0;
    CENT_TOP=0;
    CENT_CENT=0;
    CENT_BOT=0;
    RIGHT_TOP=0;
    RIGHT_CENT=0;
    RIGHT_BOT=0;

    playerName="player_1";
}

