#include "dg645.h"
#include "synchronizer.h"
//#include <QApplication>

/* Synchronizer v.1.2
 * Чтобы читались названия каналов в ini он должен быть в кодировке UTF-8-BOM
 * ip=...
 * Name1=...
 * Igor Zhironkin
 * isjironn@gmail.com / jironkin@jinr.ru
 * JINR, FLNP 2021
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Synchronizer w;
    QSettings *settings;
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, ".");
    settings = new QSettings("Synchronizer.ini", QSettings::IniFormat);
    // first
    dg645 firstDg("first");
    firstDg.settings = settings;
    QObject::connect(&firstDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&firstDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QByteArray>)), &w, SLOT(settingsToUiOne(QVector<bool>, QVector<double>, QVector<QByteArray>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &firstDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &firstDg, SLOT(setFrequency(int)));
    QObject::connect(&w, SIGNAL(delayChangedFirst(int,double)), &firstDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &firstDg, SLOT(writeSettings()));
    firstDg.init(0);
    // second
    dg645 secondDg("second");
    secondDg.settings = settings;
    QObject::connect(&secondDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&secondDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QByteArray>)), &w, SLOT(settingsToUiTwo(QVector<bool>, QVector<double>, QVector<QByteArray>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &secondDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &secondDg, SLOT(setFrequency(int)));
    QObject::connect(&w, SIGNAL(delayChangedSecond(int,double)), &secondDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &secondDg, SLOT(writeSettings()));
    secondDg.init(0);
    // third
    dg645 thirdDg("third");
    thirdDg.settings = settings;
    QObject::connect(&thirdDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&thirdDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QByteArray>)), &w, SLOT(settingsToUiThree(QVector<bool>, QVector<double>, QVector<QByteArray>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &thirdDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &thirdDg, SLOT(setFrequency(int)));
    QObject::connect(&w, SIGNAL(delayChangedThird(int,double)), &thirdDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &thirdDg, SLOT(writeSettings()));
    thirdDg.init(0);
    // fourth
    dg645 fourthDg("fourth");
    fourthDg.settings = settings;
    QObject::connect(&fourthDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&fourthDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QByteArray>)), &w, SLOT(settingsToUiFour(QVector<bool>, QVector<double>, QVector<QByteArray>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &fourthDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &fourthDg, SLOT(setFrequency(int)));
    QObject::connect(&w, SIGNAL(delayChangedFourth(int,double)), &fourthDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &fourthDg, SLOT(writeSettings()));
    fourthDg.init(0);
    w.show();
    return a.exec();
}
