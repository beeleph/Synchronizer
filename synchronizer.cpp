#include "synchronizer.h"
#include "ui_synchronizer.h"
#include "QFile"

Synchronizer::Synchronizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Synchronizer)
{
    ui->setupUi(this);
}

Synchronizer::~Synchronizer()
{
    delete ui;
}

void Synchronizer::Say(QString text)
{
    ui->textEdit->append(text);
}

void Synchronizer::on_startButton_toggled(bool checked)
{
    emit startButtonToggled(checked);
    if (checked)
        ui->startButton->setText("Стоп");
    else
        ui->startButton->setText("Запуск");
}

void Synchronizer::on_A1LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFirst(0, arg1);
}

void Synchronizer::on_C1LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFirst(2, arg1);
}

void Synchronizer::on_E1LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFirst(4, arg1);
}

void Synchronizer::on_G1LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFirst(6, arg1);
}

void Synchronizer::on_exitButton_clicked()
{
    emit startButtonToggled(0); // turning off all da channels. the easiest way
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeToStop()));
    timer->start(100);          // sry for timer. it's not working with catching events. and i don't want to add two more slots/signals just for exiting.
}

void Synchronizer::timeToStop()
{
    QCoreApplication::exit();
}

void Synchronizer::on_saveButton_clicked()
{
    emit saveButtonClicked();
}

void Synchronizer::settingsToUiOne(QVector<bool> chStatus, QVector<double> chDelay, QVector<QByteArray> V_names){
    ui->A1LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->A1DurationSpinBox->setValue(chDelay[1] - chDelay[0]);
    ui->C1LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->C1DurationSpinBox->setValue(chDelay[3] - chDelay[2]);
    ui->E1LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->E1DurationSpinBox->setValue(chDelay[5] - chDelay[4]);
    ui->G1LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->G1DurationSpinBox->setValue(chDelay[7] - chDelay[6]);
    ui->A1LineEdit->setText(V_names[0]);
    ui->C1LineEdit->setText(V_names[2]);
    ui->E1LineEdit->setText(V_names[4]);
    ui->G1LineEdit->setText(V_names[6]);
}

void Synchronizer::settingsToUiTwo(QVector<bool> chStatus, QVector<double> chDelay, QVector<QByteArray> V_names)
{
    ui->A2LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->A2DurationSpinBox->setValue(chDelay[1] - chDelay[0]);
    ui->C2LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->C2DurationSpinBox->setValue(chDelay[3] - chDelay[2]);
    ui->E2LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->E2DurationSpinBox->setValue(chDelay[5] - chDelay[4]);
    ui->G2LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->G2DurationSpinBox->setValue(chDelay[7] - chDelay[6]);
    ui->A2LineEdit->setText(V_names[0]);
    ui->C2LineEdit->setText(V_names[2]);
    ui->E2LineEdit->setText(V_names[4]);
    ui->G2LineEdit->setText(V_names[6]);
}

void Synchronizer::settingsToUiThree(QVector<bool> chStatus, QVector<double> chDelay, QVector<QByteArray> V_names)
{
    ui->A3LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->A3DurationSpinBox->setValue(chDelay[1] - chDelay[0]);
    ui->C3LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->C3DurationSpinBox->setValue(chDelay[3] - chDelay[2]);
    ui->E3LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->E3DurationSpinBox->setValue(chDelay[5] - chDelay[4]);
    ui->G3LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->G3DurationSpinBox->setValue(chDelay[7] - chDelay[6]);
    ui->A3LineEdit->setText(V_names[0]);
    ui->C3LineEdit->setText(V_names[2]);
    ui->E3LineEdit->setText(V_names[4]);
    ui->G3LineEdit->setText(V_names[6]);
}

void Synchronizer::settingsToUiFour(QVector<bool> chStatus, QVector<double> chDelay, QVector<QByteArray> V_names)
{
    ui->A4LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->A4DurationSpinBox->setValue(chDelay[1] - chDelay[0]);
    ui->C4LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->C4DurationSpinBox->setValue(chDelay[3] - chDelay[2]);
    ui->E4LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->E4DurationSpinBox->setValue(chDelay[5] - chDelay[4]);
    ui->G4LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->G4DurationSpinBox->setValue(chDelay[7] - chDelay[6]);
    ui->A4LineEdit->setText(V_names[0]);
    ui->C4LineEdit->setText(V_names[2]);
    ui->E4LineEdit->setText(V_names[4]);
    ui->G4LineEdit->setText(V_names[6]);
}

void Synchronizer::on_A2LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedSecond(0, arg1);
}

void Synchronizer::on_C2LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedSecond(2, arg1);
}

void Synchronizer::on_E2LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedSecond(4, arg1);
}

void Synchronizer::on_G2LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedSecond(6, arg1);
}

void Synchronizer::on_A3LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedThird(0, arg1);
}

void Synchronizer::on_C3LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedThird(2, arg1);
}

void Synchronizer::on_E3LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedThird(4, arg1);
}

void Synchronizer::on_G3LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedThird(6, arg1);
}

void Synchronizer::on_A4LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFourth(0, arg1);
}

void Synchronizer::on_C4LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFourth(2, arg1);
}

void Synchronizer::on_E4LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFourth(4, arg1);
}

void Synchronizer::on_G4LatencyDoubleSpinBox_valueChanged(double arg1)
{
    emit delayChangedFourth(6, arg1);
}

void Synchronizer::on_spinBox_valueChanged(int arg1)
{
    emit FRQchanged(arg1);
}
