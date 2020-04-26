#ifndef WATCHER_H
#define WATCHER_H
#include "logs_library_global.h"
#include <QDebug>
#include <thread>
#include <typeinfo>

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
        return 0;
    }

    void set_watched(bool val) {isWatched = val;};
    bool is_watched() {return isWatched;};
    T get_value() {return lastVal;};
};


class LOGS_LIBRARY_EXPORT Watcher// : public QObject
{
//Q_OBJECT
private:
    std::thread *th;//=nullptr;
    std::thread *th2;//=nullptr;
    bool stop;// = false;
public:
    Watcher(){};

    template<typename T> int watch(T* as, RealWatcher<T> *rw)
    {
        //T* currval = as;
        T lastVal = *as;
        rw->set_watched(true);
        while(!stop)
        {
            if(*as!=lastVal)
            {
               // *tmp = *currval;
                rw->set_val(*as);
            }
        }

        rw->set_watched(false);
        return 0;
    };

    void set_first_thread(std::thread *th){this->th=th;};
    void set_second_thread(std::thread *th){this->th2=th;};
    void stopWatch(){stop = true;}
    bool is_running(){return !stop;};
};

#endif // WATCHER_H
