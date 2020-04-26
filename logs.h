#ifndef LOGS_H
#define LOGS_H

#include "logs_library_global.h"
#include "watcher.h"
#include "FILE_STRUCT.h"
#include "sys_info.h"
#include <thread>
#include <mutex>
#include <QtConcurrent/QtConcurrent>
#include "iconnector.h"

/**
 * @brief Kontroler logow
 * @brief zawiera liste logow
 * @brief umozliwia zapis logow do pliku jak i przesylanie na serwer
 */

class LOGS_LIBRARY_EXPORT LOGS : public QObject
{
    Q_OBJECT
private:
    QString login, fileName,path,header,format,footer,type, *autologMessage;
    QVector<LOG> logs;
    QMap<QString,QString> customs;
    int autoSaveTime, autoLogTime, threadNum, isConnected;
    FILE_STRUCT* fs; // do ogarnięcia temat wycieku pamięci ewentualny
    SYS_INFO *si;
    bool autosaving, autologging, showSystemMemAvail,showSystemMemUsage, showProcMemUsage, showProcMemMax,
    showSysSummary, showLogNumber, showLogType, showLogDate, showLogHeader, isCustomLogSI;
    QVector<int> runningThreads;
    LOG *d, *cfg;
    IConnector *ic;
    QFuture<void> futureSave1, futureLog1;
    QMap<QString,Watcher*> watches;
    QMap<QString,QString> watchesValues;
    std::mutex mtx;

    void autosave(QString filePath, FILE_STRUCT *file_struct = nullptr);
    int autolog();
    template<typename T> void watching(T *val, QString name/*,RealWatcher<T> *rw*/,Watcher *w);
    template<typename T> QString decode_type(T *val, int &errorcode);
public:
    /**
     * @brief kontruktor bezparametrowy
     */
    LOGS();

    /**
     * @brief konstruktor z parametrem
     * @brief wykonuje najpierw konstruktor bezparametrowy, a nastepnie ustawia zmienna
     * @param fileName - nazwa pliku, do ktorego ma byc zapisany wynik
     */
    LOGS(QString fileName):LOGS() {this->fileName = fileName;};

    /**
     * @brief konstruktor z parametrami
     * @brief wykonuje najpierw konstruktor bezparametrowy, a nastepnie ustawia zmienne
     * @param fileName - nazwa pliku, do ktorego ma byc zapisany wynik
     * @param path - sciezka do katalogu, gdzie ma byc plik wynikowy
     */
    LOGS(QString fileName,QString path):LOGS() {this->fileName=fileName;this->path=path;};

    /**
     * @brief konstruktor z parametrami
     * @brief wykonuje najpierw konstruktor bezparametrowy, a nastepnie ustawia zmienna
     * @param logs - lita logow
     */
    LOGS(QVector<LOG> logs):LOGS() {this->logs = logs;};

    /**
     * @brief konstruktor z parametrami
     * @brief wykonuje najpierw konstruktor bezparametrowy, a nastepnie ustawia zmienne
     * @param fileName - nazwa pliku, do ktorego ma byc zapisany wynik
     * @param logs - lista logow
     */
    LOGS(QString fileName,QVector<LOG> logs):LOGS() {this->fileName = fileName;this->logs = logs;};

    /**
     * @brief dodaje do listy logow, log podany jako parametr
     * @param log
     */
    void add(LOG log);

    /**
     * @brief dodaje do listy logow nowy log utworzony z parametrow
     * @param header - naglowek logu
     * @param date - data logu w formie napisu
     * @param format - format daty
     * @param message - wiadomosc logu
     */
    void add(QString header,QString date,QString format,QString message);

    /**
     * @brief dodaje do listy logow nowy log utworzony z parametrow
     * @param header - naglowek logu
     * @param date - data logu jako obiekt QDateTime
     * @param message - wiadomosc logu
     */
    void add(QString header,QDateTime date,QString message);

    /**
     * @brief dodaje nowy log z wiadomoscia podana jako parametr
     * @brief do utworzenia logu wybiera domyslne parametry, ktore zostaly wczesniej ustawione przez uzytkownika lub automatycznie przy tworzeniu obiektu
     * @param message - wiadomosc logu
     */
    void add_msg(QString message);

    /**
     * @brief dodaje nowy log z wiadomoscia i typem podanymi jako parametry
     * @brief do utworzenia logu wybiera domyslne parametry, ktore zostaly wczesniej ustawione przez uzytkownika lub automatycznie przy tworzeniu obiektu
     * @param message - wiadomosc logu
     * @param type - typ logu
     */
    void add_msg(QString message,QString type);

    /**
     * @brief dodaje nowe logi z listy podanej jako parametr
     * @brief parametrem moze byc dowolny kontener, ktory obsluguje iterator
     * @param log - lista logow do dodania w formie kontenera<LOG>
     */
    template<template<typename> class C> void add(C<LOG> log);

    /**
     * @brief ustawia, czy w pliku wynikowym ma byc pokazane podsumowanie informacji o systemie
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_sys_summary(bool val) {showSysSummary=val; this->fs->show_sys_summary(val);};

    /**
     * @brief ustawia, czy w pliku wynikowym ma byc pokazana data utworzenia pliku
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_file_date(bool val) {this->fs->show_file_date(val);};

    /**
     * @brief ustawia, czy w pliku wynikowym ma byc wyswietlany numer pojedynczego logu
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_number(bool val) {showLogNumber=val;this->fs->show_log_number(val);};

    /**
     * @brief ustawia, czy w pliku wynikowym ma byc wyswietlany typ pojedynczego logu
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_type(bool val) {showLogType=val;this->fs->show_log_type(val);};

    /**
     * @brief ustawia, czy w pliku wynikowym ma byc wyswietlana data pojedynczego logu
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_date(bool val) {showLogDate=val;this->fs->show_log_date(val);};

    /**
     * @brief ustawia, czy w pliku wynikowym ma byc wyswietlany naglowek pojedynczego logu
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_header(bool val) {showLogHeader=val;this->fs->show_log_header(val);};

    /**
     * @brief ustawia, czy w pliku wynikowym, w pojedynczym logu ma byc wyswietlana informacja o dostepnej pamieci
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_memory_avail(bool val){showSystemMemAvail=val;};

    /**
     * @brief ustawia, czy w pliku wynikowym, w pojedynczym logu ma byc wyswietlana informacja o uzywanej pamieci
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_memory_usage(bool val){showSystemMemUsage=val;};

    /**
     * @brief ustawia, czy w pliku wynikowym, w pojedynczym logu ma byc wyswietlana informacja o uzywanej pamieci przez proces logujacy
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_proc_memory_usage(bool val){showProcMemUsage=val;};

    /**
     * @brief ustawia, czy w pliku wynikowym, w pojedynczym logu ma byc wyswietlana informacja o najwiekszej ilosci pamieci uzytej przez proces logujacy
     * @param val - true - pokazuje, false - nie pokazuje
     */
    void show_log_proc_memory_max(bool val){showProcMemMax=val;};

    /**
     * @brief usuwa log o podanym indexie
     * @param index - index logu
     */
    void remove(int index);

    /**
     * @brief usuwa log lub wiele logow o podanej wiadomosci
     * @brief jesli parametr all jest true, reszta nie jest brana pod uwage
     * @brief jesli paramter first jest true, parametr last nie jest brany pod uwage
     * @param message - wiadomosc logu
     * @param all - czy maja byc usuniete wszystkie - true jesli tak, false jesli nie, domyslnie true
     * @param first - czy ma byc usuniety tylko pierwszy znaleziony - true jesli tak, false jesli nie, domyslnie false
     * @param last - czy ma byc usuniety tylko ostatni znaleziony - true jesli tak, false jesli nie, domyslnie false
     */
    void remove(QString message, bool all=true, bool first=false,bool last=false);

    /**
     * @brief usuwa log lub wiele logow o podanej dacie i podanym formacie
     * @brief jesli parametr all jest true, reszta nie jest brana pod uwage
     * @brief jesli paramter first jest true, parametr last nie jest brany pod uwage
     * @param date - data logu
     * @param format - format daty logu
     * @param all - czy maja byc usuniete wszystkie - true jesli tak, false jesli nie, domyslnie true
     * @param first - czy ma byc usuniety tylko pierwszy znaleziony - true jesli tak, false jesli nie, domyslnie false
     * @param last - czy ma byc usuniety tylko ostatni znaleziony - true jesli tak, false jesli nie, domyslnie false
     */
    void remove_by_date(QString date, QString format, bool all=true, bool first=false,bool last=false);

    /**
     * @brief usuwa log lub wiele logow o podanej dacie jako QDateTime
     * @brief jesli parametr all jest true, reszta nie jest brana pod uwage
     * @brief jesli paramter first jest true, parametr last nie jest brany pod uwage
     * @param date - data typu QDateTime
     * @param all - czy maja byc usuniete wszystkie - true jesli tak, false jesli nie, domyslnie true
     * @param first - czy ma byc usuniety tylko pierwszy znaleziony - true jesli tak, false jesli nie, domyslnie false
     * @param last - czy ma byc usuniety tylko ostatni znaleziony - true jesli tak, false jesli nie, domyslnie false
     */
    void remove_by_date(QDateTime date, bool all=true, bool first=false,bool last=false);

    /**
     * @brief zmienia wiadomosc logu o podanym indeksie
     * @param index - indeks logu
     * @param newMessage - nowa wiadomosc logu
     */
    void change_message(int index, QString newMessage);

    /**
     * @brief zwraca wskaznik na log o podanym indeksie
     * @param index - indeks  logu
     * @return LOG* - wskaznik na typ log
     */
    LOG* get_LOG(int index);

    /**
     * @brief zwraca pierwszy wskaznik na log o podanej wiadomosci
     * @param message - wiadomosc logu
     * @param reverse - true, jesli szukac od konca, domyslnie false
     * @return LOG* - wskaznik na typ log
     */
    LOG* get_LOG(QString message, bool reverse=false);

    /**
     * @brief zwraca pierwszy wskaznik na log o podanej dacie i podanym formacie
     * @param date - data logu jako napis
     * @param format - format daty logu
     * @param reverse - true, jesli szukac od konca, domyslnie false
     * @return LOG* - wskaznik na typ log
     */
    LOG* get_LOG(QString date,QString format, bool reverse=false);

    /**
     * @brief zwraca pierwszy wskaznik na log o podanej dacie
     * @param date - data logu jako typ QDateTime
     * @param reverse - true, jesli szukac od konca, domyslnie false
     * @return LOG* - wskaznik na typ log
     */
    LOG* get_LOG(QDateTime date, bool reverse=false);

    /**
     * @brief zwraca wszystkie logi znajdujace sie w tym obiekcie
     * @return QVector<LOG> - lista logow
     */
    QVector<LOG> get_LOGs();

    /**
     * @brief zwraca wszystkie logi z podanego zakresu indeksow
     * @param indexFrom - poczatkowy indeks
     * @param indexTo - koncowy indeks
     * @return QVector<LOG> - lista logow
     */
    QVector<LOG> get_LOGs(int indexFrom = 0, int indexTo = 0);

    /**
     * @brief zwraca wszystkie logi o podanej wiadomosci
     * @param message - wiadomosc logu
     * @return QVector<LOG> - lista logow
     */
    QVector<LOG> get_LOGs(QString message);

    /**
     * @brief zwraca wszystkie logi o podanej dacie i podanym formacie
     * @param date - data logu jako napis
     * @param format - format daty logu
     * @return QVector<LOG> - lista logow
     */
    QVector<LOG> get_LOGs_by_date(QString date,QString format);

    /**
     * @brief zwraca wszystkie logi o podanej dacie i podanym formacie
     * @param date - data jako typ QDateTime
     * @return QVector<LOG> - lista logow
     */
    QVector<LOG> get_LOGs_by_date(QDateTime date);

    /**
     * @brief zwraca nazwe pliku, do ktorego bedzie zapisywany wynik
     * @return QString - nazwa pliku
     */
    QString get_file_name() {return fileName;};

    /**
     * @brief zwraca sciezke, w ktorym zostanie utworzony plik
     * @return QString - sciezka do katalogu
     */
    QString get_file_path() {return path;};

    /**
     * @brief zwraca domyslny format daty jaki jest ustawiony
     * @return QString - format daty
     */
    QString get_date_format() {return format;};

    /**
     * @brief zwraca domyslny typ logu jaki jest ustawiony
     * @return QString - typ logu
     */
    QString get_default_type() {return type;};

    /**
     * @brief zwraca wskaźnik na obiekt typu FILE_STRUCT
     * @brief umożliwia edycje generatora pliku
     * @return FILE_STRUCT* - wskaźnik
     * @see    FILE_STRUCT
     */
    FILE_STRUCT *get_file_struct() {return fs;};

    /**
     * @brief ustawia nazwe pliku, do ktorego bedzie zapisany wynik
     * @param fileName - nazwa pliku
     */
    void set_file_name(QString fileName) {this->fileName=fileName;};

    /**
     * @brief ustawia sciezke do katalogu, gdzie bedzie zapisany plik wynikowy
     * @param path - sciezka do katalogu
     */
    void set_file_path(QString path) {this->path=path;};

    /**
     * @brief ustawia domyslny format daty logow
     * @param format - format daty
     */
    void set_date_format(QString format) {this->format=format;this->d->set_date_format(format);};

    /**
     * @brief ustawia domyslny naglowek logow
     * @param header - naglowek logow
     */
    void set_default_header(QString header);

    /**
     * @brief ustawia obiekt o informacji o systemie na obiekt utworzony i skonfigurowany przez uzytkownika
     * @param si - obiekt SYS_INFO
     * @see   SYS_INFO
     */
    void set_custom_log_sys_info(SYS_INFO si) {this->d->add_sys_info(si);isCustomLogSI=true;};

    /**
     * @brief ustawia domyslny typ logow
     * @param type - typ logow
     */
    void set_default_type(QString type) {this->type=type;this->d->set_type(type);};

    /**
     * @brief zapisuje logi do pliku, lub wysyla do serwera, jesli jest ustanowione polaczenie
     * @return 0 - wszystko zakonczylo sie pomyslnie
     * @return -1 - brak dostepu do zapisu do pliku lub katalogu ustawionego
     * @return 1,2 - jesli problem jest z polaczeniem do serwera
     * @see    IConnector::send_data
     */
    int save();

    /**
     * @brief zapisuje logi do pliku, lub wysyla do serwera, jesli jest ustanowione polaczenie
     * @brief dodatkowo ustawia generatora pliku na tego podanego w parametrze
     * @param file_struct - wskaznik na generator pliku
     * @return 0 - wszystko zakonczylo sie pomyslnie
     * @return -1 - brak dostepu do zapisu do pliku lub katalogu ustawionego
     * @return 1,2 - jesli problem jest z polaczeniem do serwera
     * @see    IConnector::send_data
     */
    int save(FILE_STRUCT *file_struct);
    /**
    * @brief zapisuje logi do pliku, lub wysyla do serwera, jesli jest ustanowione polaczenie
    * @brief wymaga podania scezki do pliku, do ktorego bedzie wykonany zapis przy uzyciu tej metody
    * @brief nie nadpisuje domyslnej sciezki
    * @brief dodatkowo ustawia nowy generator pliku, jesli podano
    * @param filePath - pelna sciezka(sciezka+nazwa pliku)
    * @param file_struct - wskaznik na generator pliku, domyslnie nullptr
    * @return 0 - wszystko zakonczylo sie pomyslnie
    * @return -1 - brak dostepu do zapisu do pliku lub katalogu ustawionego
    * @return 1,2 - jesli problem jest z polaczeniem do serwera
    * @see    IConnector::send_data
    */
    int save(QString filePath, FILE_STRUCT *file_struct = nullptr);

    /**
     * @brief rozpoczyna automatyczne zapisywanie, uzywa wczesniej ustawionych parametrow
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autosave jest juz uruchomiony
     */
    int autosave_start();

    /**
     * @brief rozpoczyna automatyczne zapisywanie co jakis czas, podany jako parametr
     * @param autoSaveTime
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autosave jest juz uruchomiony
     */
    int autosave_start(int autoSaveTime);

    /**
     * @brief rozpoczyna automatyczne zapisywanie generujac plik przy uzycie generatora podanego jako parametr
     * @param file_struct - wskaznik na obiekt generatora pliku
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autosave jest juz uruchomiony
     */
    int autosave_start(FILE_STRUCT *file_struct);

    /**
     * @brief rozpoczyna automatyczne zapisywanie
     * @brief czas i miejsce zapisu podane jako parametry
     * @brief domyslnie bierze generator pliku ustawiony wczesniej, chyba, ze podano jako paramter
     * @param autoSaveTime - czas, co jaki ma byc wykonany automatyczny zapis
     * @param filePath - pelna sciezka(sciezka+nazwa pliku)
     * @param file_struct - wskaznik na obiekt typu FILE_STRUCT*, domyslnie nullptr
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autosave jest juz uruchomiony
     */
    int autosave_start(int autoSaveTime,QString filePath, FILE_STRUCT *file_struct = nullptr);

    /**
     * @brief rozpoczyna automatyczne zapisywanie
     * @brief  miejsce zapisu podane jako parametry
     * @brief domyslnie bierze generator pliku ustawiony wczesniej, chyba, ze podano jako paramter
     * @param filePath - pelna sciezka(sciezka+nazwa pliku)
     * @param file_struct - wskaznik na obiekt typu FILE_STRUCT*, domyslnie nullptr
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autosave jest juz uruchomiony
     */
    int autosave_start(QString filePath, FILE_STRUCT *file_struct = nullptr);

    /**
     * @brief rozpoczyna automatyczne logowanie
     * @brief dodaje nowe wpisy do listy logow
     * @param autoLogTime - czas pomiedzy utworzeniem kolejnych logow
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autolog jest juz uruchomiony
     */
    int autolog_start(int autoLogTime= 10);

    /**
     * @brief rozpoczyna automatyczne logowanie
     * @brief dodaje nowe wpisy do listy logow
     * @param cfg - wskaznik na obiekt LOG, pobierana jest z niego konfiguracja pojedynczego logu
     * @param si - wskaznik na obiekt SYS_INFO, domyslnie nullptr, jesli podano - jest bazowym obiektem o informacjach o systemie
     * @return 0 - jesli wszystko jest ok
     * @return -1 - jesli autolog jest juz uruchomiony
     */
    int autolog_start(LOG *cfg, SYS_INFO *si = nullptr);

    /**
     * @brief ustawia wskaznik na wiadomosc, ktora ma byc automatycznie dodawana
     * @brief zamysl tego jest, ze podczas autologowania, funkcja pobiera wartosc na jaka wskazuje
     * @brief tak, ze w przypadku zmiany wartosci, nowa zostanie zapisana
     * @param m - wskaznik do wiadomosci
     */
    void set_autolog_message(QString *m){autologMessage = m;};

    /**
     * @brief zatrzymuje autosave
     */
    void autosave_stop();

    /**
     * @brief zatrzymuje autologowanie
     */
    void autolog_stop();

    /**
     * @brief ustawia czas, co ile ma byc wykonany autosave
     * @param time - czas w sekundach
     */
    void set_autosave_time(int time) {this->autoSaveTime=time;};

    /**
     * @brief ustawia czas, co ile ma byc wykonany autolog
     * @param time - czas w sekundach
     */
    void set_autolog_time(int time) {this->autoLogTime=time;};

    /**
     * @brief ustawia domyslne polaczenie sieciowe
     * @param conn - wskaznik do obiektu implementujacego interfejs IConnector
     * @see   IConnector
     */
    void set_connection(IConnector *conn) {this->ic = conn;isConnected=ic->is_connected();};

    /**
     * @brief laczy sie do serwera uzywajac domyslnego polaczenia
     * @brief domyslnym polaczeniem jest polaczenie DirectConnection
     * @param host - adres hosta
     * @param port - port hosta
     * @param username - nazwa uzytkownika
     * @param password - haslo uzytkownika
     * @return  0 - polaczono i zalogowano
     * @return  1 - podany uzytkownik zostal odrzucony przez serwer
     * @return  2 - podany uzytkownik zostal zaakceptowany, serwer czeka na haslo
     * @return  3 - podane haslo jest nieprawidlowe
     * @return  4 - uzytkownik nie zostal podany
     * @return -1 - blad polaczenia
     * @return -2 - brak hosta
     * @see IConnector
     * @see DirectConnection
     */
    int connect_to_log_serv(QString host,quint16 port,QString username="",QString password="");

    /**
     * @brief zatrzymuje monitorowanie zmiennej
     * @param name - nazwa zmiennej
     */
    void stop_watch(QString name);

    /** @brief rozpoczyna monitorowanie zmiennej
     *  @param name - nazwa zmiennej
     *  @param val  - wskaznik na zmienna
     */
    template<typename T> void watch(QString name, T *val/*,RealWatcher<T> *rw*/);
};

template<template<typename> class C> void LOGS::add(C<LOG> log)
{
    for(auto it = log.begin();it!=log.end();it++)
    {
        this->logs.push_back(*it);
    }
}

template<typename T> void LOGS::watch(QString name, T *val/*,RealWatcher<T> *rw*/)
{
    Watcher *tmp = new Watcher();
    this->watches[name]=tmp;
    int res = 0;
    QString helper = watchesValues[name] = decode_type(val,res);
    this->add_msg("starting watching value "+name+" = "+helper);

    std::thread *tx=new std::thread(&LOGS::watching<T>,this,val,name/*,rw*/,tmp);
    tmp->set_first_thread(tx);

    QThread::sleep(2);
    qDebug()<<"Watching started";
};

template<typename T> void LOGS::watching(T *val, QString name,/*RealWatcher<T> *rw,*/Watcher *w)
{
    LOG tmp = *d;
    QVector<LOG> threadLogs;
    T lastVal = *val;

    while(w->is_running())
    {
        int t=*val;
        if(t!=lastVal)
        {
            int c =1;
            lastVal = t;
            this->watchesValues[name]=decode_type(&lastVal,c);
            tmp.set_message("value changed :"+name+" on "+watchesValues[name]);
            tmp.set_date(QDateTime::currentDateTime());
            threadLogs.push_back(tmp);

            if(mtx.try_lock())
            {
                this->add(threadLogs);
                mtx.unlock();
                threadLogs.clear();
            }
        }
    }
};

template<typename T> QString LOGS::decode_type(T *val, int &errorcode)
{
    if(std::is_convertible<T,int>())
    {
        errorcode=0;
        //int d = static_cast<T>(val);
        int *ds = reinterpret_cast<int*>(val);
        QString res = QString::number(*ds);
        return res;
    }
    /*
    if(std::cout<<std::is_convertible<T,QString>())
    {
        errorcode=0;
        return QString(val);
    }

    if(std::cout<<std::is_convertible<T,std::string>())
    {
        errorcode=0;
        return QString::fromStdString(val);
    }

    if(std::cout<<std::is_convertible<T,char*>())
    {
        errorcode=0;
        char *plik = "asd";
        std::string as = std::string(plik);
        return QString::fromStdString(as);
    }*/

    errorcode=-1;
    return "Cannot conver variable!";
}
/**
 * @brief operator>> odpowiada za odbieranie danych z wejscia QDataStream
 * @brief umozliwia przesylanie typu LOGS przez siec przy wykorzystaniu QDataStream
 * @param in - referencja do obiektu QDataStream, z ktorego pobierane sa dane
 * @param fs - referencja do obiektu LOGS, do którego zapisywane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOGS
 */
LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,LOGS &fs);

/**
 * @brief operator<< odpowiada za wysylanie danych do wyjscia QDataStream
 * @brief umozliwia przesylanie typu LOGS przez siec przy wykorzystaniu QDataStream
 * @param out - referencja do obiektu QDataStream, do ktorego wysylane sa dane
 * @param fs - referencja do obiektu LOGS, z którego wysylane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOGS
 */
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,LOGS &fs);

#endif // LOGS_H
