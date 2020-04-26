#ifndef DIRECTSERVER_H
#define DIRECTSERVER_H

#include "logs_library_global.h"
#include <QtNetwork/QtNetwork>
#include "logs.h"

/**
 * @brief Typ enumeryczny ustawiajacy sposob generowania nazwy plikow
 */
enum FILE_EXT
{
    NUMBERS,
    DATE,
    NONE
};
/**
 * @brief Klasa serwera
 */
class LOGS_LIBRARY_EXPORT DirectServer : public QObject
{
    Q_OBJECT
private:
    int logNum;
    QTcpServer *control, *data;
    QVector<QTcpSocket*> clients, acceptedClients;
  //  QVector<QTcpSocket*> dataClients;
    QString saveDir,username,password, fileName,userTMP,passTMP;
    LOGS *logs;
    FILE_STRUCT *fs;
    FILE_EXT fe;
    QString currentCMD;
    int save();
    bool isAccepted(QString sck);
    qint16 controlPort,dataPort;
public:
    /**
     * @brief konstruktor bezparametrowy
     */
    DirectServer();

    /**
     * @brief  ustawia folder zapisu
     * @param dir - miejce na dysku, gdzie ma byc zapisany plik
     */
    void set_save_dir(QString dir) {saveDir=dir;};

    /**
     * @brief ustawia nazwe uzytkownika
     * @param username - nazwa uzytkownika
     */
    void set_user(QString username) {this->username=username;};

    /**
     * @brief ustawia haslo
     * @param pwd - haslo
     */
    void set_pwd(QString pwd) {password=pwd;};

    /**
     * @brief ustawia nazwe pliku
     * @param file - nazwa pliku
     */
    void set_file_name(QString file) {fileName=file;};

    /**
     * @brief ustawia generator pliku
     * @param fileStruct - wskaznik na generator pliku
     * @see   FILE_STRUCT
     */
    void set_file_struct(FILE_STRUCT *fileStruct) {fs=fileStruct;};

    /**
     * @brief ustawia rozszerzenie nazwy pliku generowanego
     * @param fe - typ rozszerzenia(data, numer lub brak rozszrzenia)
     * @see   FILE_EXT
     */
    void set_file_ext(FILE_EXT fe) {this->fe=fe;};

    /**
     * @brief ustawia port, na ktory beda przychodzily komendy sterujace komunikacja
     * @param port - numer portu
     */
    void set_control_port(quint16 port) {controlPort=port;control->close();control->listen(QHostAddress::Any,port);};

    /**
     * @brief ustawia port, na ktory beda przychodzily dane od klienta
     * @param port - numer portu
     */
    void set_data_port(quint16 port) {dataPort=port;control->close();data->listen(QHostAddress::Any,port);};

    /**
     * @brief zwraca generator pliku
     * @return FILE_STRUCT* - wskaznik do obiektu FILE_STRUCT
     * @see   FILE_STRUCT
     */
    FILE_STRUCT *get_file_struct() {return fs;};


public slots:
    /**
     * @brief slot Qt, wywolywany w przypadku przyjscia sygnalu - instrkukcji sterujacej od klienta
     * @brief obsluguje instrukcje
     */
    void controlService();

    /**
     * @brief slot Qt, wywolywany w przypadku przyjscia sygnalu - danych od klienta
     * @brief obsluguje przychodzace dane
     */
    void dataService();

    /**
     * @brief slot Qt, wywolywany w przypadku przyjscia sygnalu - rozlaczenia sie klienta
     * @brief zamyka i usuwa nieaktywne socekty
     */
    void disconnectedSocket();

    /**
     * @brief slot Qt, wywolywany w przypadku przyjscia sygnalu - rozpoczecia polaczenia klienta
     * @brief obsluguje polaczenie
     */
    void newControlConn();

    /**
     * @brief slot Qt, wywolywany w przypadku przyjscia sygnalu - rozpoczecia polaczenia klienta w celu przeslania danych
     * @brief obsluguje polaczenie
     */
    void newDataConn();
};
#endif // DIRECTSERVER_H
