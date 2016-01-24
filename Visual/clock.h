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
    void start(unsigned ms);

    ~Clock();

private:
    QTimer* timer;
    unsigned value;
    Ui::Clock *ui;
signals:
    void updated(unsigned value);
public slots:
    void update();

};

#endif // CLOCK_H
