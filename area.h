#ifndef AREA_H
#define AREA_H
#include <QWidget>
#include <shape.h>

class Area : public QWidget
{
    Q_OBJECT
private:
    Shape* arrow;
    int myTimer;
    float stopAngle = 90;
    float totalAngle = 0;
//    float alpha;
    void setNewCoords(Shape* shape, float**);
    void translateShape(float** oldMatrix, Coords* value);
    void rotateShape(float** oldMatrix, float angle);
    void scaleShape(float** oldMatrix, float value);
    void matrixMultiplication(float**, int, int, float**, int, int);
public:
    Area(QWidget *parent = 0);
    ~Area() {
        delete arrow;
    };
public slots:
    void start_prog();
    void reset_prog();
protected:
    //обработчики событий
    void paintEvent(QPaintEvent *event); //событие перерисовки
    void timerEvent(QTimerEvent *event); //событие таймера
    void showEvent(QShowEvent *event); // событие начала
    void hideEvent(QHideEvent *event); // событие конца
};

#endif // AREA_H
