#include "clock.h"
#include "ui_clock.h"
#include <QDebug>
Clock::Clock(QWidget *parent) :
    QLabel(parent),value(0),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    setText(QString::number(0));
    repaint();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

void Clock::start(unsigned ms){
    setText(QString::number(value));
    timer->start(ms);
}

Clock::~Clock()
{
    delete ui;
    delete timer;
}

void Clock::update()
{
    qDebug()<<value;
    setText(QString::number(++value));
    emit updated(value);
}
