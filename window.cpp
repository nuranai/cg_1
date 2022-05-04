#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Window::Window()
{
    area = new Area( this ); //создаем холст
    startBtn = new QPushButton("Start", this);
    resetBtn = new QPushButton("Reset", this);
    exitBtn = new QPushButton("Exit",this ); //создаем кнопку
    QHBoxLayout *Hlayout = new QHBoxLayout();
//    QVBoxLayout *layout1 = new QVBoxLayout();
//    QVBoxLayout *layout2 = new QVBoxLayout();
    QVBoxLayout *layout = new QVBoxLayout(this);
    Hlayout->addWidget(startBtn);
    Hlayout->addWidget(resetBtn);
    layout->addWidget(area);
    layout->addLayout(Hlayout);
    layout->addWidget(exitBtn);
//    layout->addLayout(layout1);
//    layout->addLayout(layout2);
    connect(exitBtn,SIGNAL(clicked(bool)), this,SLOT(close()));
    connect(startBtn,SIGNAL(clicked(bool)), area,SLOT(start_prog()));
}

void Window::start_prog() {
    area->start_prog();
}

void Window::end_prog() {
    area->reset_prog();
}
