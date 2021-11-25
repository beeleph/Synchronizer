#ifndef DG645_H
#define DG645_H

#include <QDataStream>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSettings>
#include <QTimer>

#include <winsock2.h>
#include <stdio.h>

class dg645 : public QObject
{
    Q_OBJECT
public:
    explicit dg645(QString nameIn, QWidget *parent = nullptr);                                    // constructor
    QSettings *settings;//{QSettings::IniFormat, QSettings::UserScope,"JINR", "Synchronizer"};

signals:
    void dgSay(QString text);       // for debug info to show in GUI
    void settingsToUi(QVector<bool> chStatus, QVector<double> chDelay, QVector<QByteArray> V_names); // for passing readed settings to GUI controls

public slots:
    void init(bool needaStatus);
    void readSettings();                        // read from ini
    void writeSettings();                       // write to ini file
    void chOnOff(int chNum, bool status);       // turn onoff chNum channel
    void displayError(QAbstractSocket::SocketError socketError);
    void read();                                // automatically reads input buffa to debug window
    void askStatus();                           // asks INSR? for status
    void setDelay(int chNum, double chDelay);   // means that chDelay in Ms (microsec)
    void setDelayDuration(int chNum, double chDelay);   // sets the output instead of channel with fixed duration readed from ini
    void setFrequency(int frq);                 // sets frequency? in hz!
    void startStop(bool checked);               // when start button is pressed. we write all da settings including frq, delays, on/off to dg, turn off all da channels when stop button is pressed
    void triggerSwitch(bool internal);          // for extra safety with on/off


private:
    QString name;
    QString ip;                     // dg ip
    QTimer *statusTimer;
    QTcpSocket *tcpSocket = nullptr;
    bool chStatus[4];               // channels status. 0 - off, 1 - on. changing status using LAMP (switching amplitude to zero or 5V), applicable only to pair of channels. AB, CD, EF, GH
    bool uiStatus = false;          // ui status - start button. when UI enabled delays and onOff buttons immediately works with DG. otherwise only "memorize" their settings.
    double chDelay[8];              // channels delays in Ms microseconds.
    double outputDuration[4];           // duration of outputs. for using outputs with fixed ending. i0 - ch1 - outAB, i1 - ch3 - outCD, i2 - ch5 - outEF, i3- ch7 - outGH
    int frequency = 0;              // dg internal trigger frequency in HZ

    QVector<QByteArray> V_names{8};
    // yea, basically better to uistatus, frq and setting to be static. but it's more complicated and less convinient for me.


};

#endif // DG645_H
