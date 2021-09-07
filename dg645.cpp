#include "dg645.h"

dg645::dg645(QString nameIn, QWidget *parent) : tcpSocket(new QTcpSocket(this))
{ 
    this->name = nameIn;
}
void dg645::init(bool needaStatus)
{
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, ".");
    settings = new QSettings("Synchronizer.ini", QSettings::IniFormat);
    readSettings();
    for (int i = 0; i < 4; ++i){
        if (this->outputDuration[i] != 0.0){
            this->chDelay[i*2+1] = this->chDelay[i*2] + this->outputDuration[i]; // mmmmm yeaaaaaaah))) you should get it.
        }
    }
    dgSay("1 channel is - " + QString::number(this->chDelay[1]));
    // yea. that's gonna be creepy. buuut. i can't either use QVector instead of default C arrays for some reason
    // and pass arrays (signal/slot) instead of QVector. sooo......
    QVector<bool> V_chStatus(4);
    QVector<double> V_chDelay(8);
    for (int i = 0; i < 4; ++i){
        V_chStatus[i] = this->chStatus[i];
    }
    for (int i = 0; i < 8; ++i){
        V_chDelay[i] = this->chDelay[i];
    }
    emit settingsToUi(V_chStatus, V_chDelay, this->V_names);   // passing settings to UI
    dgSay("Initialization connection...");
    connect(tcpSocket, &QIODevice::readyRead, this, &dg645::read);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &dg645::displayError);
    tcpSocket->connectToHost(QHostAddress(this->ip),5025);
    if (tcpSocket->waitForConnected(100)){
        dgSay(this->name + ": connected");
        //setDelay(0,0);
        //chOn(0);
        //tcpSocket->write(QByteArray("lerr?\n"));
    }
    statusTimer = new QTimer(this);
    connect(statusTimer,  SIGNAL(timeout()), this, SLOT(askStatus()));
    if (needaStatus){
        statusTimer->start(1000);
    }
    //tcpSocket->disconnectFromHost();
    //tcpSocket->abort();
    /* get identification string
     * dg_write("*idn?\n");
     * load default settings
     * dg_write("*rst\n");
     * Set internal triggering
     * dg_write("tsrc 0\n");
     * Set trigger rate to 10hz
     * dg_write("trat 10\n");
     * Make sure all commands have executed before closing connection
     * dg_write("*opc?\n");
     */
}
void dg645::readSettings(){
    this->settings->beginGroup(this->name);                  //needed for differ the dg's.
    this->ip = this->settings->value("ip").toString();
    for (int i = 0; i < 4; ++i){
        this->chStatus[i] = this->settings->value("Output_" + QString::number(i) + "_status", FALSE).toBool();
        this->outputDuration[i] = this->settings->value("Output_" + QString::number(i) + "_duration", 0).toDouble();
    }
    for (int i = 0; i < 8; ++i){
        this->chDelay[i] = this->settings->value("Channel_" + QString::number(i) + "_delay").toDouble();
        this->V_names[i] = this->settings->value("Name" + QString::number(i)).toString();
    }
    this->settings->endGroup();
    dgSay(this->name + ": settings readed");
}
void dg645::writeSettings(){
    this->settings->beginGroup(this->name);
    for (int i = 0; i < 4; ++i){
        this->settings->setValue("Output_" + QString::number(i) + "_status", this->chStatus[i]);
    }
    for (int i = 0; i < 8; ++i){
        this->settings->setValue("Channel_" + QString::number(i) + "_delay", this->chDelay[i]);
    }
    this->settings->endGroup();
    dgSay(this->name + ": settings saved");
}
void dg645::displayError(QAbstractSocket::SocketError socketError)
{
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
      break;
  case QAbstractSocket::HostNotFoundError:
      dgSay(this->name + ": The host was not found. Please check the host name and port settings.");
      break;
  case QAbstractSocket::ConnectionRefusedError:
      dgSay(this->name + ": The connection was refused by the peer");
      break;
  default:
      dgSay(this->name + ": The following error occurred: " + tcpSocket->errorString());
  }
}
void dg645::askStatus(){
    //do not forget to timah
    QString write("INSR?\n");
    tcpSocket->write(write.toUtf8());
}
void dg645::read()
{
/*    dgSay("ReadyRead triggered");
    in.startTransaction();

    QString readBuffa;
    in >> readBuffa;
*/
    /*if (!in.commitTransaction())
        return;*/
    QByteArray readBuffa = tcpSocket->readAll();
    dgSay(this->name + ": " + readBuffa);
}
void dg645::chOnOff(int chNum, bool status){
    if (status) {
        if (uiStatus) {
            QString write("lamp " + QString::number(chNum + 1) + ",5\n");   // set amplitude to five. dont forget that 0 output is T0,T1. So we need to +1                                                  // when start button is active.
            tcpSocket->write(write.toUtf8());                           // i dont know any better way
        }
        this->chStatus[chNum] = TRUE;
    }
    else    {
        if (uiStatus){
            QString write("lamp " + QString::number(chNum + 1) + ",0.5\n");   // set amplitude to zero.
            tcpSocket->write(write.toUtf8());                           //
        }
        this->chStatus[chNum] = FALSE;
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
        QString write2("dlay " + QString::number(chNum + 3) + ",0," + QString::number((chDelay+this->outputDuration[chNum/2])/1000000) + "\n");
        tcpSocket->write(write2.toUtf8());
    }
    this->chDelay[chNum] = chDelay;
}
void dg645::setFrequency(int frq){
    if (uiStatus){
        QString write("trat " + QString::number(frq) + "\n");
        tcpSocket->write(write.toUtf8());
    }
    this->frequency = frq;
}
void dg645::startStop(bool checked){                                 // calling when startStop button is pushed
    if (checked){
        uiStatus = TRUE;                                            // GUI should operate dg from this moment
        setFrequency(this->frequency);                              // frequency >>
        for (int i = 0; i < 8; i++){
            setDelay(i, this->chDelay[i]);                          // delays >>
        }
        for (int i = 0; i < 4; i++){
            chOnOff(i, this->chStatus[i]);                          // just in case
        }
        dgSay("Started");
    }
    else {
        uiStatus = FALSE;                                           // GUI should not operate dg from this moment.
        for (int i = 0; i < 4; i++){    // yea. better using chCount instead of 4. but dg always have 4 outputs whatever what.
            QString write("lamp " + QString::number(i + 1) + ",0.5\n");   // set amplitude to zero.
            tcpSocket->write(write.toUtf8());
        }
        dgSay("All channels turned off");
    }
    //tcpSocket->disconnectFromHost();
    //dgSay("Disconnected");
}
