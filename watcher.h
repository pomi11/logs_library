#ifndef WATCHER_H
#define WATCHER_H
#include "logs_library_global.h"
#include <QDebug>
#include <thread>
#include <typeinfo>
/*
template<class T>
class LOGS_LIBRARY_EXPORT RealWatcher
{
private:
    T* currval;
    T lastVal;
    bool isWatched = false;

  public:
    RealWatcher(T* val)
    {
        this->currval=val;
        this->lastVal=*val;
    };

    int set_val(T val)
    {
        lastVal = val;
    }

    void set_watched(bool val) {isWatched = val;};
    bool is_watched() {return isWatched;};
    T get_value() {return lastVal;};
};

*/
class LOGS_LIBRARY_EXPORT Watcher// : public QObject
{
//Q_OBJECT
private:
    std::thread *th;//=nullptr;
   // std::thread *th2;//=nullptr;
    bool stop;// = false;
public:
    /**
     * @brief konstruktor bezparametrowy
     */
    Watcher(){};

/*    template<typename T> int watch(T* as, RealWatcher<T> *rw)
    {
        //T* currval = as;
        T lastVal = *as;
        rw->set_watched(true);
        while(!stop)
        {
            if(*as!=lastVal)
            {
                rw->set_val(*as);
            }
        }

        rw->set_watched(false);
        return 0;
    };*/

    /**
     * @brief przypisuje wskaznik na watek
     * @param th - wskaznik na watek
     */
    void set_first_thread(std::thread *th){this->th=th;};

    /*
    void set_second_thread(std::thread *th){this->th2=th;};*/

    /**
     * @brief zatrzymuje proces monitorowania
     */
    void stopWatch(){stop = true;}

    /**
     * @brief zwraca informacje, czy proces trwa
     * @return true - proces jest wciaz uruchomiony
     * @return false - proces sie zakonczyl
     */
    bool is_running(){return !stop; delete this->th; th = nullptr;};
};

#endif // WATCHER_H
