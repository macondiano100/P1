#include "clock.h"
#include "ui_clock.h"
#include <QDebug>
Clock::Clock(QWidget *parent) :
    QLabel(parent),value(0),
    ms(0),
    paused(true),
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
    paused=false;
    this->ms=ms;
    timer->start(ms);
}

void Clock::resume()
{
    if(paused)timer->start(ms);
    paused=false;
}

Clock::~Clock()
{
    delete ui;
}

void Clock::pause()
{
    paused=true;
    timer->stop();
}

void Clock::updateValue()
{
    qDebug()<<value;
    setText(QString::number(++value));
    emit updated(value);
}
