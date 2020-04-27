#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "logs_library_global.h"
#include <QtNetwork/QtNetwork>
#include "LOG.h"
#include "sys_info.h"

/**
 * @brief Interfejs IConnectror
 */
class LOGS_LIBRARY_EXPORT IConnector
{
protected:
    /**
     * @brief przetwarza odpowiedz serwera tekstowa na typ int
     * @param response - tekstowa odpowiedz serwera
     * @return int - zwraca liczbowa reprezentacje odpowiedzi serwera
     */

    virtual int decode_response(QString response) = 0;

public:
    /**
     * @brief   umozliwia utworzenie polaczenia sieciowego, uzywa wczesniej ustawionych danych
     * @brief   jesli uzytkownik i/lub haslo nie zostaly wczesniej podane, a serwer ich wymaga, ustanawia polaczenie bez logowania
     * @return  0 - polaczono i zalogowano
     * @return  1 - podany uzytkownik zostal odrzucony przez serwer
     * @return  2 - podany uzytkownik zostal zaakceptowany, serwer czeka na haslo
     * @return  3 - podane haslo jest nieprawidlowe
     * @return  4 - uzytkownik nie zostal podany
     * @return -1 - blad polaczenia
     * @return -2 - brak hosta
     */
    virtual int connect() = 0;

    /**
     * @brief umozliwia utworzenie polaczenia sieciowego, wymaga podania przynajmniej adresu hosta
     * @brief pozostale parametry sa opcjonalne
     * @brief jesli host nie uzywa domyslnych ustawien, konieczne jest ich podanie, w przeciwnym wypadku polaczenie nie dojdzie do skutku
     * @param host - adres hosta
     * @param port - adres portu hosta, domyslnie 1616
     * @param user - nazwa uzytkownika, domyslnie brak
     * @param password - haslo, domyslnie brak
     * @return  0 - polaczono i zalogowano
     * @return  1 - podany uzytkownik zostal odrzucony przez serwer
     * @return  2 - podany uzytkownik zostal zaakceptowany, serwer czeka na haslo
     * @return  3 - podane haslo jest nieprawidlowe
     * @return  4 - uzytkownik nie zostal podany
     * @return -1 - blad polaczenia
     * @return -2 - brak hosta
     * @see   connect
     */
    virtual int connect(QString host,quint16 port = 1616,QString user="",QString password="") = 0;

    /**
     * @brief wysyla komende wraz z parametrami do serwera
     * @param cmd - komenda i parametry w formie napisu QString
     */
    virtual void send_cmd(QString cmd) = 0;

    /**
     * @brief zwraca wartosc polaczenia
     * @return  0 - polaczono i zalogowano
     * @return  1 - podany uzytkownik zostal odrzucony przez serwer
     * @return  2 - podany uzytkownik zostal zaakceptowany, serwer czeka na haslo
     * @return  3 - podane haslo jest nieprawidlowe
     * @return  4 - uzytkownik nie zostal podany
     * @return -1 - blad polaczenia
     * @return -2 - brak hosta
     *
     * @see connect
     */
    virtual int is_connected() = 0;

    /**
     * @brief wysyla logi na serwer
     * @param log - vector logow do wyslania
     * @return 0 - zakonczono pomyslnie
     *         1 - nie udalo sie polaczyc z serwerem na port danych
     *         2 - wystapil problem z przesylaniem danych
     */
    virtual int send_data(QVector<LOG> &log) =0;

    /**
     * @brief zamyka i usuwa polaczenie
     */
    virtual void close() = 0;
};

/**
 * @brief Implementacja IConnector do polaczenia z serwerem z tej biblioteki
 */

class LOGS_LIBRARY_EXPORT DirectConnection : public QObject, public IConnector
{
    Q_OBJECT

private:
    QString server, password, username;
    int isConnected;
    QTcpSocket *controlSocket,*dataSocket;
    quint16 controlPort, dataPort;
    QString serverNo, serverResponse;

protected:
     int decode_response(QString response) override;

public:
    /**
     * @brief konstruktor bezparametrowy, ustawia domyslne wartosci pol
     */
    DirectConnection();

    /**
     * @brief konstruktor z parametrem host
     * @brief wywoluje konstruktor bezparametrowy, a nastepnie ustawia adres hosta
     * @param host - adres hosta
     */
    DirectConnection(QString host);

    /**
     * @brief konstruktor z dwoma parametrami - host, port
     * @brief wywoluje konstruktor bezparametrowy, a nastepnie ustawia adres i port hosta
     * @param host - adres hosta
     * @param port - port hosta
     */
    DirectConnection(QString host,quint16 port);

    /**
     * @brief konstruktor z trzema parametrami - host, port, user
     * @brief wywoluje konstruktor bezparametrowy, a nastepnie ustawia adres i port hosta oraz nazwe uzytkownika
     * @param host - adres hosta
     * @param port - port hosta
     * @param user - nazwa uzytkownika
     */
    DirectConnection(QString host,quint16 port, QString user);

    /**
     * @brief konstruktor z trzema parametrami - host, port, user, password
     * @brief wywoluje konstruktor bezparametrowy, a nastepnie ustawia adres i port hosta oraz nazwe i haslo uzytkownika
     * @param host - adres hosta
     * @param port - port hosta
     * @param user - nazwa uzytkownika
     * @param password - haslo uzytkownika
     */
    DirectConnection(QString host,quint16 port, QString user,QString password);


    int is_connected() override {return isConnected;};
    int connect() override;
    int connect(QString host,quint16 port = 1616,QString user="",QString password="") override;
    void send_cmd(QString cmd) override;


    void close() override;
    virtual int send_data(QVector<LOG> &log) override;
    /**
     * @brief ustawia port, na ktorym odbywac sie ma komunikacja z serwerem
     * @param port - port serwera
     */
    void set_control_port(quint16 port) {controlPort=port;};

    /**
     * @brief ustawia port, na ktorym odbywac sie ma transfer danych do serwera
     * @param port danych serwera
     */
    void set_data_port(quint16 port) {dataPort=port;};
};

#endif // ICONNECTOR_H
