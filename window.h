#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QPushButton>
#include <QObject>
#include "area.h"

class Window: public QWidget
{
    Q_OBJECT
protected:
    Area * area;
    QPushButton * startBtn;
    QPushButton * resetBtn;
    QPushButton * exitBtn;
public:
    Window();
public slots:
    void start_prog();
    void end_prog();
};

#endif // WINDOW_H
