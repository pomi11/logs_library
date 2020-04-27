#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include "logs_library_global.h"
#include <iostream>
#include <vector>
#include <map>
#include "LOG.h"

/**
 * @brief interfejs generatora pliku
 */
class LOGS_LIBRARY_EXPORT FILE_STRUCT
{
public:
    /**
     * @brief ustawia, czy w pliku ma byc pokazane ogolne podsumowanie systemu
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_sys_summary(bool val) =0;

    /**
     * @brief ustawia, czy ma byc widoczny numer pojedynczego logu
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_number(bool val) =0;

    /**
     * @brief ustawia, czy ma byc widoczny typ pojedynczego logu
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_type(bool val) =0;

    /**
     * @brief ustawia, czy ma byc widoczna data pojedynczego logu
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_date(bool val) =0;

    /**
     * @brief ustawia, czy ma byc widoczny naglowek pojedynczego logu
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_header(bool val) =0;

    /**
     * @brief ustawia, czy ma byc widoczna data utworzenia pliku
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_file_date(bool val) =0;

    /**
     * @brief ustawia, czy ma byc widoczny opis pliku
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_file_descr(bool val) =0;

    /**
     * @brief ustawia, czy w pojedynczym logu ma byc widoczna ilosc dostepnej pamieci RAM
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_memory_avail(bool val) =0;

    /**
     * @brief ustawia, czy w pojedynczym logu ma byc widoczna ilosc uzywanej pamieci RAM
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_memory_usage(bool val) =0;

    /**
     * @brief ustawia, czy w pojedynczym logu ma byc widoczna ilosc uzywanej pamieci RAM przez proces logujacy
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_proc_memory_usage(bool val) =0;

    /**
     * @brief ustawia, czy w pojedynczym logu ma byc widoczna najwieksza ilosc pamieci RAM uzytej przez proces logujacy
     * @param val - true - wlacza, false wylacza
     */
    virtual void show_log_proc_memory_max(bool val) =0;

    /**
     * @brief generuje poczatek pliku, automatycznie generuje date, jesli jest wlaczona
     * @param description - opis pliku, ktory ma byc umieszczony na poczatku
     * @return std::string - zwraca paczatek pliku
     */
    virtual std::string start_file(QString description) = 0;

    /**
     * @brief generuje sekcje logow w pliku
     * @param logs - wektor map logow, jeden wpis to jedna mapa nazw sekcji LOGu oraz mapy nazw zmiennych i ich wartosci
     * @return std::string - zwraca wygenerowana sekcje logow
     */
    virtual std::string log(QVector<QMap<QString,QMap<QString,QString>>> logs) = 0;

    /**
     * @brief generuje koniec pliku
     * @return std::string - zwraca wygenerowany koniec pliku
     */
    virtual std::string end_file() = 0;
};

/**
 * @brief Implementacja interjesu FILE_STRUCT
 * @brief Generuje plik xml
 */
class XML: public FILE_STRUCT
{
private:
    QVector<QString> tags;
    bool showSystemMemAvail = false,showSystemMemUsage = false, showProcMemUsage = false, showProcMemMax = false, showSysSummary = true,
                showLogNumber = true, showLogType = true, showLogDate = true, showLogHeader = false, showFileDate = true, showFileDescr=false;
public:
   // XML(QString header,QString footer);
    XML();
    virtual ~XML(){};
    std::string log(QVector<QMap<QString,QMap<QString,QString>>> logs)  override;
    std::string end_file() override;
    std::string start_file(QString description) override;

    void show_sys_summary(bool val) override {showSysSummary=val;} ;
    void show_log_number(bool val) override  {showLogNumber=val;};
    void show_log_type(bool val) override  {showLogType=val;};
    void show_log_date(bool val) override {showLogDate=val;};
    void show_log_header(bool val) override {showLogHeader=val;};

    void show_log_memory_avail(bool val) override {showSystemMemAvail=val;};
    void show_log_memory_usage(bool val) override {showSystemMemUsage=val;};
    void show_log_proc_memory_usage(bool val) override {showProcMemUsage=val;};
    void show_log_proc_memory_max(bool val) override {showProcMemMax=val;};

    void show_file_date(bool enable) override {showFileDate=enable;};
    void show_file_descr(bool enable) override {showFileDescr=enable;};
};

/*
class TXT: public FILE_STRUCT
{
public:
    TXT(QString header,QString footer);
    TXT();
    std::string log(QVector<QMap<QString,QMap<QString,QString>>> logs) override;
    std::string end_file() override;
    std::string start_file(QString description) override;
};
*/
#endif // FILE_STRUCT_H
