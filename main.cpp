#include "dg645.h"
#include "synchronizer.h"
//#include <QApplication>

/* Synchronizer v.0.2
 * Чтобы читались названия каналов в ini он должен быть в кодировке UTF-8-BOM
 * ip=...
 * Name1=...
 * Igor Zhironkin
 * isjironn@gmail.com
 * JINR, FLNP 2020
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Synchronizer w;
    w.show();
    // first
    dg645 firstDg("first");
    QObject::connect(&firstDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&firstDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QString>)), &w, SLOT(settingsToUiOne(QVector<bool>, QVector<double>, QVector<QString>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &firstDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &firstDg, SLOT(setFrequency(int)));
    //QObject::connect(&w, SIGNAL(enableToggledFirst(int, bool)), &firstDg, SLOT(chOnOff(int, bool)));
    QObject::connect(&w, SIGNAL(delayChangedFirst(int,double)), &firstDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &firstDg, SLOT(writeSettings()));
    firstDg.init(1);
    // second
    dg645 secondDg("second");
    QObject::connect(&secondDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&secondDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QString>)), &w, SLOT(settingsToUiTwo(QVector<bool>, QVector<double>, QVector<QString>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &secondDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &secondDg, SLOT(setFrequency(int)));
    //QObject::connect(&w, SIGNAL(enableToggledSecond(int, bool)), &secondDg, SLOT(chOnOff(int, bool)));
    QObject::connect(&w, SIGNAL(delayChangedSecond(int,double)), &secondDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &secondDg, SLOT(writeSettings()));
    secondDg.init(1);
    // third
    dg645 thirdDg("third");
    QObject::connect(&thirdDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&thirdDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QString>)), &w, SLOT(settingsToUiThree(QVector<bool>, QVector<double>, QVector<QString>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &thirdDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &thirdDg, SLOT(setFrequency(int)));
    QObject::connect(&w, SIGNAL(delayChangedThird(int,double)), &thirdDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &thirdDg, SLOT(writeSettings()));
    thirdDg.init(1);
    // fourth
    dg645 fourthDg("fourth");
    QObject::connect(&fourthDg, SIGNAL(dgSay(QString)), &w, SLOT(Say(QString)));
    QObject::connect(&fourthDg, SIGNAL(settingsToUi(QVector<bool>, QVector<double>, QVector<QString>)), &w, SLOT(settingsToUiFour(QVector<bool>, QVector<double>, QVector<QString>)));
    QObject::connect(&w, SIGNAL(startButtonToggled(bool)), &fourthDg, SLOT(startStop(bool)));
    QObject::connect(&w, SIGNAL(FRQchanged(int)), &fourthDg, SLOT(setFrequency(int)));
    QObject::connect(&w, SIGNAL(delayChangedFourth(int,double)), &fourthDg, SLOT(setDelayDuration(int,double)));
    QObject::connect(&w, SIGNAL(saveButtonClicked()), &fourthDg, SLOT(writeSettings()));
    fourthDg.init(1);
    return a.exec();
}

/* ToDo:
 *
 * Запуск останов?
 * при выходе не выключает синхронизатор. не успевает.
 * Чтобы реализовать вывод ширины на ГУЙ надо вычислять разность задержек соседних каналов
 */

/* to commit
 * Deprecated *error* removed
 * +third and fourth Dg's
 * +DelayChanged
 * +two more dg's to GUI
 * !build is not tested though
 */
