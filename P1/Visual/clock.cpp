#include "clock.h"
#include "ui_clock.h"
#include <QDebug>
Clock::Clock(QWidget *parent) :
    QLabel(parent),value(0),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateValue()));
    setText(QString::number(0));
    repaint();
}

void Clock::start(int ms){
    setText("0");
    timer->start(ms);
}

Clock::~Clock()
{
    delete ui;
}

void Clock::updateValue()
{
    qDebug()<<value;
    setText(QString::number(++value));
    emit updated(value);
}
