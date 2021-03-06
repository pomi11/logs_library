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
/**
 * @brief Klasa do monitorowania zmiennych
 */
class LOGS_LIBRARY_EXPORT Watcher// : public QObject
{
//Q_OBJECT
private:
    std::thread *th;//=nullptr;
   // std::thread *th2;//=nullptr;
    QVariant *value = nullptr;
    bool stop = false;// = false;
    bool additionalConversion = false;
public:
    /**
     * @brief konstruktor bezparametrowy
     */
    Watcher(){value = nullptr;};

    ~Watcher()
    {
        delete value;
        delete th;
    };

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
    void stopWatch()
    {
        stop = true;
        th->join();
        delete this->th;
        delete this->value;
        this->value = nullptr;
        th = nullptr;
    }
    /**
     * @brief zwraca informacje, czy proces trwa
     * @return true - proces jest wciaz uruchomiony
     * @return false - proces sie zakonczyl
     */
    bool is_running(){return !stop;};

    template<typename T> void set_value(T val)
    {
        if(this->value!=nullptr)
            delete this->value;
        this->value = new QVariant(val);
    }

    QString get_value()
    {
        QString res;
        //potrzebna konwersja typu float
        //jednoczesnie trzeba zablokowac bledna konwersje z typu char
        if(additionalConversion)
        {
            res = QString::number(qvariant_cast<float>(*value));
        }
        else
            res = value->toString();
        return res;
    }

    void set_add_conversion(bool val) {this->additionalConversion=val;};
};

#endif // WATCHER_H
