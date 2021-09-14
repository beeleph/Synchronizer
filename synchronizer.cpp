#include "synchronizer.h"
#include "ui_synchronizer.h"
#include "QFile"
#include "QTextStream"

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
void Synchronizer::loadTextFile()
{
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    ui->textEdit->append("Well, this shit");
    ui->textEdit->append("Should work");
    this->Say("and even this");
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}

void Synchronizer::on_startButton_toggled(bool checked)
{
    emit startButtonToggled(checked);
}

void Synchronizer::on_AB1EnableButton_toggled(bool checked)
{
    emit enableToggledFirst(0, checked);
}

void Synchronizer::on_CD1EnableButton_toggled(bool checked)
{
    emit enableToggledFirst(1, checked);
}

void Synchronizer::on_EF1EnableButton_toggled(bool checked)
{
    emit enableToggledFirst(2, checked);
}

void Synchronizer::on_GH1EnableButton_toggled(bool checked)
{
    emit enableToggledFirst(3, checked);
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

void Synchronizer::settingsToUiOne(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names){
    /*ui->AB1EnableButton->setChecked(chStatus[0]);
    ui->CD1EnableButton->setChecked(chStatus[1]);
    ui->EF1EnableButton->setChecked(chStatus[2]);
    ui->GH1EnableButton->setChecked(chStatus[3]);*/    // this feature is disabled
    ui->A1LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->C1LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->E1LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->G1LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->A1LineEdit->setText(V_names[0]);
    ui->C1LineEdit->setText(V_names[2]);
    ui->E1LineEdit->setText(V_names[4]);
    ui->G1LineEdit->setText(V_names[6]);
}

void Synchronizer::settingsToUiTwo(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names)
{
    /*ui->AB2EnableButton->setChecked(chStatus[0]);
    ui->CD2EnableButton->setChecked(chStatus[1]);
    ui->EF2EnableButton->setChecked(chStatus[2]);
    ui->GH2EnableButton->setChecked(chStatus[3]);*/
    ui->A2LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->C2LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->E2LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->G2LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->A2LineEdit->setText(V_names[0]);
    ui->C2LineEdit->setText(V_names[2]);
    ui->E2LineEdit->setText(V_names[4]);
    ui->G2LineEdit->setText(V_names[6]);
}

void Synchronizer::settingsToUiThree(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names)
{
    ui->A3LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->C3LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->E3LatencyDoubleSpinBox->setValue(chDelay[4]);
    ui->G3LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->A3LineEdit->setText(V_names[0]);
    ui->C3LineEdit->setText(V_names[2]);
    ui->E3LineEdit->setText(V_names[4]);
    ui->G3LineEdit->setText(V_names[6]);
}

void Synchronizer::settingsToUiFour(QVector<bool> chStatus, QVector<double> chDelay, QVector<QString> V_names)
{
    ui->A4LatencyDoubleSpinBox->setValue(chDelay[0]);
    ui->C4LatencyDoubleSpinBox->setValue(chDelay[2]);
    ui->E4LatencyDoubleSpinBox->setValue(chDelay[4]);
    //ui->G2LatencyDoubleSpinBox->setValue(chDelay[6]);
    ui->A4LineEdit->setText(V_names[0]);
    ui->C4LineEdit->setText(V_names[2]);
    ui->E4LineEdit->setText(V_names[4]);
    //ui->G2LineEdit->setText(V_names[6]);
}
void Synchronizer::on_comboBox_currentTextChanged(const QString &arg1)
{
    emit FRQchanged(arg1.toInt());
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

void Synchronizer::on_AB2EnableButton_toggled(bool checked)
{
    emit enableToggledSecond(0, checked);
}

void Synchronizer::on_CD2EnableButton_toggled(bool checked)
{
    emit enableToggledSecond(1, checked);
}

void Synchronizer::on_EF2EnableButton_toggled(bool checked)
{
    emit enableToggledSecond(2, checked);
}

void Synchronizer::on_GH2EnableButton_toggled(bool checked)
{
    emit enableToggledSecond(3, checked);
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
