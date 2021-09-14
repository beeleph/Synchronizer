#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <QWidget>
#include <QVector>
#include <QApplication>
#include <QTimer>

namespace Ui {
class Synchronizer;
}

class Synchronizer : public QWidget
{
    Q_OBJECT

public:
    explicit Synchronizer(QWidget *parent = nullptr);
    ~Synchronizer();

signals:
    void startButtonToggled(bool checked);
    void FRQchanged(int frq);
    void enableToggledFirst(int chNum, bool checked);
    void enableToggledSecond(int chNum, bool checked);
    void delayChangedFirst(int ch,double delayMs);
    void delayChangedSecond(int ch,double delayMs);
    void delayChangedThird(int ch,double delayMs);
    void delayChangedFourth(int ch,double delayMs);
    void saveButtonClicked();

private slots:
    // this actually needed for debug info to show. and to protect the ui itself
    void Say(QString text);

    void settingsToUiOne(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names);

    void settingsToUiTwo(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names);

    void settingsToUiThree(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names);

    void settingsToUiFour(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names);

    void on_startButton_toggled(bool checked);

    void on_A1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_AB1EnableButton_toggled(bool checked);

    void on_CD1EnableButton_toggled(bool checked);

    void on_EF1EnableButton_toggled(bool checked);

    void on_GH1EnableButton_toggled(bool checked);

    void on_B1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_C1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_D1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_E1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_F1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_G1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_H1LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_exitButton_clicked();

    void on_saveButton_clicked();


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_A2LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_C2LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_E2LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_G2LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_AB2EnableButton_toggled(bool checked);

    void on_CD2EnableButton_toggled(bool checked);

    void on_EF2EnableButton_toggled(bool checked);

    void on_GH2EnableButton_toggled(bool checked);

    void timeToStop();

    void on_A3LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_C3LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_E3LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_G3LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_A4LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_C4LatencyDoubleSpinBox_valueChanged(double arg1);

    void on_E4LatencyDoubleSpinBox_valueChanged(double arg1);

private:
    Ui::Synchronizer *ui;
    void loadTextFile();
    
};

#endif // SYNCHRONIZER_H
