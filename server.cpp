#include "server.h"

server::server(QObject *parent)
    : QObject{parent}
{
    started = false;
    frequency = 0;
}

void server::initServer(){
    tcpServer = new QTcpServer(this); // need to explicitly set port?
    if (!tcpServer->listen(QHostAddress::Any, 52550)) {
        // say --> (this, tr("Fortune Server"),tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        serverSay(tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    // say --> tr("The server is running on\n\nIP: %1\nport: %2\n\n""Run the Fortune Client example now.").arg(ipAddress).arg(tcpServer->serverPort()));
    serverSay(tr("The server is running on\n\nIP: %1\nport: %2\n\n").arg(ipAddress).arg(tcpServer->serverPort()));
    connect(tcpServer, &QTcpServer::newConnection, this, &server::sendShitBack);
}

void server::freqChanging(int freq){
    frequency = freq;
}

void server::statusChanging(bool status){
    started = status;
}

void server::sendShitBack()
{
    QJsonObject jsonObj;
    if (!started)
        jsonObj["frequency"] = 0;
    else
        jsonObj["frequency"] = frequency;
    jsonObj["status"] = started;
    QJsonDocument jdman(jsonObj);
    QByteArray jsonData = jdman.toJson(QJsonDocument::Indented);

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(jsonData);
    clientConnection->waitForBytesWritten();
    clientConnection->disconnectFromHost();
}
