#ifndef LOG_H
#define LOG_H

#include "logs_library_global.h"
#include <QDateTime>
#include <QMap>
#include <QDataStream>
#include "sys_info.h"

/**
 * @brief Klasa reprezentuje pojednczy log
 */
class LOGS_LIBRARY_EXPORT LOG
{
private:
    QString header,message,type,format;
    QDateTime date;
    SYS_INFO si;

public:
    /**
     * @brief konstruktor bezparametrowy
     * @brief ustawia domyslne wartosci
     * @brief data jest ustawiana automatycznie
     */
    LOG();

    /**
     * @brief konstruktor z jednym parametrem - date
     * @brief wykonywany jest najpierw konstruktor bezparametrowy
     * @param date - data LOGu
     * @see   LOG
     */
    LOG(QDateTime date);

    /**
     * @brief konstruktor z dwoma parametrami - header oraz message
     * @brief wykonywany jest najpierw konstruktor bezparametrowy
     * @param header - naglowek logu
     * @param message - wiadomosc logu
     * @see   LOG
     */
    LOG(QString header,QString message);//,QMap<QString,QString> custom);

    /**
     * @brief ustawia wiadomosc logu
     * @param message - wiadomosc logu
     */
    void set_message(QString message)   {this->message=message;};

    /**
     * @brief dodaje obiekt typu SYS_INFO
     * @brief wykorzystac go mozna, jesli jest domyslne informacje o systemie sa niewystarczajace
     * @param si - obiekt typu SYS_INFO
     * @see   SYS_INFO
     */
    void add_sys_info(SYS_INFO si){this->si=si;};

    /**
     * @brief ustawia date logu
     * @param date - data w postaci napisu
     * @param format - format daty, w jakim jest podana data w pierwszym parametrze, ustawiany jest jako domyslny
     */
    void set_date(QString date,QString format);

    /**
     * @brief ustawia date logu
     * @param date - data w postaci typu QDateTime
     * @see   <a href="https://doc.qt.io/qt-5/qdatetime.html">QDateTime</a>
     */
    void set_date(QDateTime date)   {this->date=date;};

    /**
     * @brief ustawia domyslny format daty
     * @param format - format daty w postaci napisu
     */
    void set_date_format(QString format) {this->format=format;};

    /**
     * @brief ustawia naglowek logu
     * @param header - naglowek logu
     */
    void set_header(QString header) {this->header=header;};

    /**
     * @brief ustawia typ logu
     * @param type - typ
     */
    void set_type(QString type) {this->type=type;};

    /**
     * @brief zwraca mape nazw i ich wartosci
     * @brief basic - to podstawowe dane:
     * @brief heder, date, message
     * @return QMap<QString,QString> - mapa nazw i ich wartosci
     * @see <a href="https://doc.qt.io/qt-5/qmap.html">QDataStream</a>
     */
    QMap<QString,QString> get_basic();

    /**
     * @brief zwraca mape nazw i ich wartosci
     * @brief sys_info - to dane przechowywane przez obiekt SYS_INFO
     * @return QMap<QString,QString> - mapa nazw i ich wartosci
     * @see   SYS_INFO
     */
    QMap<QString,QString> get_sys_info_map();

    /**
     * @brief zwraca wskaźnik na obiekt typu SYS_INFO
     * @brief umożliwia edycje generacji informacji o systemie
     * @return SYS_INFO* - wskaźnik
     * @see   SYS_INFO
     */
    SYS_INFO *get_sys_info() {return &si;};

    /**
     * @brief zwraca wiadomosc logu w formie napisu
     * @return QString - wiadomosc
     */
    QString get_message()  {return this->message;};

    /**
     * @brief zwraca date logu w formie napisu w podanym formacie
     * @param format - format daty
     * @return QString - data w podanym formacie
     */
    QString get_date(QString format);

    /**
     * @brief zwraca date logu jako obiekt QDateTime
     * @return QDateTime - data logu
     */
    QDateTime get_date();

    /**
     * @brief zwraca naglowek logu w formie napisu
     * @return QString - naglowek logu
     */
    QString get_header() {return this->header;};

    /**
     * @brief zwraca typ logu w formie napisu
     * @return QString - typ logu
     */
    QString get_type() {return this->type;};

    /**
     * @brief zwraca format daty logu w formie napisu
     * @return QString - format daty
     */
    QString get_date_format() {return this->format;};
};

/**
 * @brief operator>> odpowiada za odbieranie danych z wejscia QDataStream
 * @brief umozliwia przesylanie typu LOG przez siec przy wykorzystaniu QDataStream
 * @param in - referencja do obiektu QDataStream, z ktorego pobierane sa dane
 * @param fs - referencja do obiektu LOG, do którego zapisywane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOG
 */
LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,LOG &fs);

/**
 * @brief operator<< odpowiada za wysylanie danych do wyjscia QDataStream
 * @brief umozliwia przesylanie typu LOG przez siec przy wykorzystaniu QDataStream
 * @param out - referencja do obiektu QDataStream, do ktorego wysylane sa dane
 * @param fs - referencja do obiektu LOG, z którego wysylane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOG
 */
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,LOG fs);

/**
 * @brief operator>> odpowiada za odbieranie danych z wejscia QDataStream
 * @brief umozliwia przesylanie typu QVector<LOG> przez siec przy wykorzystaniu QDataStream
 * @param in - referencja do obiektu QDataStream, z ktorego pobierane sa dane
 * @param list - referencja do obiektu QVector<LOG>, do którego zapisywane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOG
 */
LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,QVector<LOG> &list);

/**
 * @brief operator<< odpowiada za wysylanie danych do wyjscia QDataStream
 * @brief umozliwia przesylanie typu QVector<LOG> przez siec przy wykorzystaniu QDataStream
 * @param out - referencja do obiektu QDataStream, do ktorego wysylane sa dane
 * @param list - referencja do obiektu QVector<LOG>, z którego wysylane sa dane
 * @return QDataStream
 * @see    <a href="https://doc.qt.io/qt-5/qdatastream.html">QDataStream</a>
 * @see   LOG
 */
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,QVector<LOG> list);

#endif // LOG_H
