#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include "logs_library_global.h"
#include <iostream>
#include <vector>
#include <cpuid.h>
#include <QSysInfo>
#include <QString>
#include <QStorageInfo>
#include <QMap>
#include <memory>
#include <QDataStream>

#ifdef __WIN32
    #include <sysinfoapi.h>
    #include <windef.h>
    #include <winbase.h>
    #include <psapi.h>
#endif

#ifdef __linux__
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <sys/sysinfo.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <fstream>
#endif

/**
 * @brief Struktura informacji o dyksu
 */
struct LOGS_LIBRARY_EXPORT DISK_INFO
{
    QString name;
    int number;
    qint64 totalSpace;
    qint64 usageSpace;
    qint64 freeSpace;
};

/**
 * @brief Klasa do zbierania informacji o systemie
 */
class LOGS_LIBRARY_EXPORT SYS_INFO
{
private:
    QMap<QString,bool> enabledInfos;
    QMap<QString,QString> infos;
    QString sysname,CPUname,arch,username;
    int cores;
    unsigned long long int maxMemory,availMemory,useMemory,procPeak,procCurr;
    QVector<DISK_INFO> disks;
public:
    /**
     * @brief konstruktor bezparametrowy
     */
    SYS_INFO();

    /**
     * @brief konstruktor tworzacy obiekt SYS_INFO z danymi od uzytkownika
     * @param enabledInfos - mapa nazw informacji i wartorsci, czy maja byc zbierane
     * @param infos - mapa nazw informacji i ich wartosci
     * @param sysname - nazwa systemu
     * @param CPUname - nazwa procesora
     * @param arch - architektura systemu
     * @param username - nazwa uzytkownika
     * @param cores - liczba rdzeni
     * @param maxMemory - zainstalowana pamiec w systemie
     * @param availMemory - wolna pamiec w systemie
     * @param useMemory - ilosc uzytej pamieci
     * @param procPeak - maksymalna ilosc pamieci jakiej potrzebowal proces logujacy
     * @param procCurr - obecna ilosc pamieci uzywanej przez proces logujacy
     * @param disks - lista dyskow
     */
    SYS_INFO(QMap<QString,bool> enabledInfos,QMap<QString,QString> infos,
             QString sysname,QString CPUname,QString arch, QString username,int cores,
             quint64 maxMemory, quint64 availMemory, quint64 useMemory,quint64 procPeak,
             quint64 procCurr, QVector<DISK_INFO> disks);

    /**
     * @brief zwraca nazwe systemu
     * @return QString - nazwa systemu
     */
    QString get_sysname() const {return sysname;};

    /**
     * @brief zwraca nazwe procesora
     * @return QString - nazwa procesora
     */
    QString get_cpuname() const {return CPUname;};

    /**
     * @brief zwraca architekture systemu
     * @return QString - architektura systemu
     */
    QString get_arch() const {return arch;};

    /**
     * @brief zwraca nazwe uzytkownika
     * @return QString - nazwa uzytkownika
     */
    QString get_username() const {return username;};

    /**
     * @brief zwraca liczbe rdzeni procesora
     * @return int - liczba rdzeni
     */
    int get_cores() const {return cores;};

    /**
     * @brief zwraca mape nazw informacji i wartosci, czy sa monitorowane
     * @return QMap<QString,boo>
     */
    QMap<QString,bool> get_enabled_infos() {return enabledInfos;};

    /**
     * @brief zwraca ilosc pamieci zainstalowanej w systemie
     * @return unsigned long long int - ilosc pamieci w B
     */
    unsigned long long int get_max_memory() const {return maxMemory;} ;

    /**
     * @brief zwraca ilosc pamieci wolnej w systemie
     * @return unsigned long long int - ilosc pamieci w B
     */
    unsigned long long int get_avail_memory() const {return availMemory;};

    /**
     * @brief zwraca ilosc pamieci zajetej w systemie
     * @return unsigned long long int - ilosc pamieci w B
     */
    unsigned long long int get_use_memory() const {return useMemory;};

    /**
     * @brief zwraca maksymalna ilosc pamieci jaka potrzebowal proces logujacy
     * @return unsigned long long int - ilosc pamieci w B
     */
    unsigned long long int get_proc_peak() const {return procPeak;};

    /**
     * @brief zwraca ilosc pamieci jaka obecnie uzywa proces logujacy
     * @return unsigned long long int - ilosc pamieci w B
     */
    unsigned long long int get_proc_curr() const {return procCurr;};

    /**
     * @brief zwraca liste dyskow
     * @return QVector<DISK_INFO> - lista dyskow
     * @see   DISK_INFO
     */
    QVector<DISK_INFO> get_disks_info() const {return disks;};

    /**
     * @brief aktualizuje informacje o nazwie systemu
     */
    void gather_sysname();

    /**
     * @brief aktualizuje informacje o nazwie procesora
     */
    void gather_CPUname();

    /**
     * @brief aktualizuje informacje o architekturze systemu
     */
    void gather_arch();

    /**
     * @brief aktualizuje informacje o nazwie uzytkownika
     */
    void gather_username();

    /**
     * @brief aktualizuje informacje o liczbie rdzeni
     */
    void gather_cores();

    /**
     * @brief aktualizuje informacje o ilosci pamieci zainstalowanej w systemie
     */
    void gather_max_memory();

    /**
     * @brief aktualizuje informacje o ilosci wolnej pamieci w systemie
     */
    void gather_avail_memory();

    /**
     * @brief aktualizuje informacje o ilosci uzytej pamieci w systemie
     */
    void gather_use_memory();

    /**
     * @brief aktualizuje informacje o maksymalnej ilosci uzytej pamieci przez proces logujacy
     */
    void gather_proc_peak();

    /**
     * @brief aktualizuje informacje o obecnym uzyciu pamieci przez procesor logujacy
     */
    void gather_proc_curr();

    /**
     * @brief aktualizuje informacje o dyskach w systemie
     */
    void gather_disks_info();

    /**
     * @brief aktualizuje wszystkie informacje o systemie
     */
    void gather_info();

    /**
     * @brief zwraca wartosc podanej informacji o systemie
     * @param infoName - nazwa informacji, ktorej wartosc ma byc zwrocona
     * @return QString - wartosc informacji w postaci napisu
     */
    QString get_info(QString infoName);

    /**
     * @brief zwraca liste wartosci informacji o systemie
     * @brief jesli nie podano parametru wejsciowego - zwracana sa wszystkie informacje, ktore zostaly oznaczone jako wlaczone
     * @param infoNames - QVector<QString> - lista nazw informacji potrzebnych. Wartosci zwracane sa w takiej samej kolejnosci jak podane nazwy.
     * @return QVector<QString> - lista wartosci
     * @see   set_enabled
     * @see   disable_all
     */
    QVector<QString> get_info(QVector<QString> infoNames = QVector<QString>());

    /**
     * @brief zwraca mape nazw informacji i ich wartosci
     * @brief zwracana sa wszystkie informacje, ktore zostaly oznaczone jako wlaczone
     * @return QMap<QString,QString> - mapa nazw i ich wartosci
     */
    QMap<QString,QString> get_info_map();

    /**
     * @brief zwraca mape nazw informacji i ich wartosci
     * @param infoNames - lista nazw informacji do pobrania
     * @return QMap<QString,QString> - mapa nazw i ich wartosci
     */
    QMap<QString,QString> get_info_map(QVector<QString> infoNames);

    /**
     * @brief wylacza wszystkie informacje
     */
    void disable_all();

    /**
     * @brief wlacza lub wylacza informacje
     * @param infoname - nazwa informacji
     * @param enable - true - wlacza, false - wylacza
     */
    void set_enabled(QString infoname, bool enable=true);

    /**
     * @brief wlacza lub wylacza informacje
     * @param infoNames - lista nazw informacji, jesli nie podano, wszystkie informacje zostana wlaczone
     * @param enable - true - wlacza, false - wylacza
     */
    void set_enabled(QVector<QString> infoNames= QVector<QString>(),bool enable=true);

    /**
     * @brief zwraca liste dostepnych informacji
     * @return QVector<QString> - lista nazw informacji
     */
    static QVector<QString> listInfo();
};

/**
 * @brief operator>> odpowiada za odbieranie danych z wejscia QDataStream
 * @brief umozliwia przesylanie typu SYS_INFO przez siec przy wykorzystaniu QDataStream
 * @param in - referencja do obiektu QDataStream, z ktorego pobierane sa dane
 * @param fs - referencja do obiektu SYS_INFO, do którego zapisywane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   SYS_INFO
 */
LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,SYS_INFO &fs);

/**
 * @brief operator<< odpowiada za wysylanie danych do wyjscia QDataStream
 * @brief umozliwia przesylanie typu SYS_INFO przez siec przy wykorzystaniu QDataStream
 * @param out - referencja do obiektu QDataStream, do ktorego wysylane sa dane
 * @param fs - referencja do obiektu SYS_INFO, z którego wysylane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOG
 */
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,SYS_INFO fs);

/**
 * @brief operator>> odpowiada za odbieranie danych z wejscia QDataStream
 * @brief umozliwia przesylanie typu DISK_INFO przez siec przy wykorzystaniu QDataStream
 * @param in - referencja do obiektu QDataStream, z ktorego pobierane sa dane
 * @param fs - referencja do obiektu DISK_INFO, do którego zapisywane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   SYS_INFO
 */
LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,DISK_INFO &fs);

/**
 * @brief operator<< odpowiada za wysylanie danych do wyjscia QDataStream
 * @brief umozliwia przesylanie typu DISK_INFO przez siec przy wykorzystaniu QDataStream
 * @param out - referencja do obiektu QDataStream, do ktorego wysylane sa dane
 * @param fs - referencja do obiektu DISK_INFO, z którego wysylane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOG
 */
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,DISK_INFO const fs);

#endif // SYSTEM_INFO_H
