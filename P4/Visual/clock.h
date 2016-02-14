#ifndef CLOCK_H
#define CLOCK_H

#include <QLabel>
#include <QTimer>
namespace Ui {
class Clock;
}

class Clock : public QLabel
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = 0);
    void start(int ms=0);
    void resume();

    ~Clock();

private:
    unsigned value;
    QTimer *timer;
    int ms;
    bool paused;
    Ui::Clock *ui;
signals:
    void updated(unsigned value);
    void updated();
public slots:
    void pause();
    void updateValue();

};

#endif // CLOCK_H
