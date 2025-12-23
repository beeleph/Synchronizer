#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include <QtNetwork>

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    void initServer();

signals:
    void serverSay(QString text);   // for display debug info at GUI.

public slots:
    void sendShitBack();
    void freqChanging(int freq);
    void statusChanging(bool status);

private:

    QTcpServer *tcpServer = nullptr;

    int frequency;
    bool started;
};

#endif // SERVER_H
