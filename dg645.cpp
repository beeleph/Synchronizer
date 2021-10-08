#include "dg645.h"

dg645::dg645(QString nameIn, QWidget *parent) : tcpSocket(new QTcpSocket(this))
{ 
    name = nameIn;
}
void dg645::init(bool needaStatus)
{
    readSettings();
    for (int i = 0; i < 4; ++i){
        if (outputDuration[i] != 0.0){
            chDelay[i*2+1] = chDelay[i*2] + outputDuration[i]; // mmmmm yeaaaaaaah))) you should get it.
        }
    }
    // yea. that's gonna be creepy. buuut. i can't either use QVector instead of default C arrays for some reason
    // and pass arrays (signal/slot) instead of QVector. sooo......
    QVector<bool> V_chStatus(4);
    QVector<double> V_chDelay(8);
    for (int i = 0; i < 4; ++i){
        V_chStatus[i] = chStatus[i];
    }
    for (int i = 0; i < 8; ++i){
        V_chDelay[i] = chDelay[i];
    }
    emit settingsToUi(V_chStatus, V_chDelay, V_names);   // passing settings to UI
    dgSay("Initialization connection...");
    connect(tcpSocket, &QIODevice::readyRead, this, &dg645::read);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),this, &dg645::displayError);    //smth changed here
    tcpSocket->connectToHost(QHostAddress(ip),5025);
    if (tcpSocket->waitForConnected(100)){
        dgSay(name + ": connected");
    }
    statusTimer = new QTimer(this);
    connect(statusTimer,  SIGNAL(timeout()), this, SLOT(askStatus()));
    if (needaStatus){
        statusTimer->start(1000);
    }
}
void dg645::readSettings(){
    settings->beginGroup(name);                  //needed for differ the dg's
    ip = settings->value("ip").toString();
    for (int i = 0; i < 4; ++i){
        chStatus[i] = settings->value("Output_" + QString::number(i) + "_status", false).toBool();
        outputDuration[i] = settings->value("Output_" + QString::number(i) + "_duration", 0).toDouble();
    }
    for (int i = 0; i < 8; ++i){
        chDelay[i] = settings->value("Channel_" + QString::number(i) + "_delay").toDouble();
        V_names[i] = settings->value("Name" + QString::number(i)).toByteArray();
    }
    settings->endGroup();
    dgSay(name + ": settings readed");
}
void dg645::writeSettings(){
    settings->beginGroup(name);
    for (int i = 0; i < 4; ++i){
        settings->setValue("Output_" + QString::number(i) + "_status", chStatus[i]);
    }
    for (int i = 0; i < 8; ++i){
        settings->setValue("Channel_" + QString::number(i) + "_delay", chDelay[i]);
    }
    settings->endGroup();
    dgSay(name + ": settings saved");
}
void dg645::displayError(QAbstractSocket::SocketError socketError)
{
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
      break;
  case QAbstractSocket::HostNotFoundError:
      dgSay(name + ": The host was not found. Please check the host name and port settings.");
      break;
  case QAbstractSocket::ConnectionRefusedError:
      dgSay(name + ": The connection was refused by the peer");
      break;
  default:
      dgSay(name + ": The following error occurred: " + tcpSocket->errorString());
  }
}
void dg645::askStatus(){
    //do not forget to timah
    QString write("INSR?\n");
    tcpSocket->write(write.toUtf8());
}
void dg645::read()
{
    QByteArray readBuffa = tcpSocket->readAll();
    dgSay(name + ": " + readBuffa);
}
void dg645::chOnOff(int chNum, bool status){
    if (status) {
        if (uiStatus) {
            QString write("lamp " + QString::number(chNum + 1) + ",5\n");   // set amplitude to five. dont forget that 0 output is T0,T1. So we need to +1                                                  // when start button is active.
            tcpSocket->write(write.toUtf8());                           // i dont know any better way
        }
        chStatus[chNum] = true;
    }
    else    {
        if (uiStatus){
            QString write("lamp " + QString::number(chNum + 1) + ",0.5\n");   // set amplitude to zero.
            tcpSocket->write(write.toUtf8());                           //
        }
        chStatus[chNum] = false;
    }
}
void dg645::setDelay(int chNum, double chDelay){
    if (uiStatus){
        QString write("dlay " + QString::number(chNum + 2) + ",0," + QString::number(chDelay/1000000) + "\n");  // set delay for chNum channel in seconds. don't forget that 0 channel is T0. A is 2 channel. so we need to +2.
        tcpSocket->write(write.toUtf8());
    }
    this->chDelay[chNum] = chDelay;
}
void dg645::setDelayDuration(int chNum, double chDelay){
    if (uiStatus){
        QString write("dlay " + QString::number(chNum + 2) + ",0," + QString::number(chDelay/1000000) + "\n");  // set delay for chNum channel in seconds. don't forget that 0 channel is T0. A is 2 channel. so we need to +2.
        tcpSocket->write(write.toUtf8());
        QString write2("dlay " + QString::number(chNum + 3) + ",0," + QString::number((chDelay+outputDuration[chNum/2])/1000000) + "\n");
        tcpSocket->write(write2.toUtf8());
    }
    this->chDelay[chNum] = chDelay;
    this->chDelay[chNum+1] = chDelay + outputDuration[chNum/2];
}
void dg645::setFrequency(int frq){
    if (uiStatus){
        QString write("trat " + QString::number(frq) + "\n");
        tcpSocket->write(write.toUtf8());
    }
    frequency = frq;
}
void dg645::startStop(bool checked){                                 // calling when startStop button is pushed
    if (checked){
        uiStatus = true;                                            // GUI should operate dg from this moment
        setFrequency(frequency);                              // frequency >>
        for (int i = 0; i < 8; i++){
            setDelay(i, chDelay[i]);                          // delays >>
        }
        for (int i = 0; i < 4; i++){
            chOnOff(i, chStatus[i]);                          // just in case
        }
        QString write("lamp " + QString::number(0) + ",5\n");       // activating To channel. seem's like we gonna use it too.
        tcpSocket->write(write.toUtf8());
        dgSay("Started");
    }
    else {
        uiStatus = false;                                           // GUI should not operate dg from this moment.
        for (int i = -1; i < 4; i++){    // yea. better using chCount instead of 4. but dg always have 4 outputs whatever what. we using -1 for To channel, seem's like we gonna use it too.
            QString write("lamp " + QString::number(i + 1) + ",0.5\n");   // set amplitude to zero.
            tcpSocket->write(write.toUtf8());
        }
        dgSay("All channels turned off");
    }
    //tcpSocket->disconnectFromHost();
    //dgSay("Disconnected");
}
