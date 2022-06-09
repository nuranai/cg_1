#include "area.h"
#include <QPainter>
#include <QTimerEvent>
#include <iostream>
#include "math.h"

using namespace std;

Area::Area(QWidget *parent):QWidget(parent)
{
    Coords **arrowCoords = new Coords*[6];
    arrowCoords[0] = new Coords(150, 150);
    arrowCoords[1] = new Coords(165, 70);
    arrowCoords[2] = new Coords(180, 70);
    arrowCoords[3] = new Coords(150, 0);
    arrowCoords[4] = new Coords(120, 70);
    arrowCoords[5] = new Coords(135, 70);

    arrow = new Shape(6, arrowCoords);

    setFixedSize(QSize(300, 300));
}

void Area::showEvent(QShowEvent *) {
}

void Area::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawLine(150, 150, 300, 150);
    painter.setPen(Qt::red);
    float **arrowMatrix = new float*[3];
    for (int i = 0; i < 3; i++) {
        arrowMatrix[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                arrowMatrix[i][j] = 1;
            }
            else {
                arrowMatrix[i][j] = 0;
            }
        }
    }
    float bamp = totalAngle != 0 ? 0.01f : 0;
    Coords *translateCoords = new Coords(-150, -150);
    translateShape(arrowMatrix, translateCoords);
    rotateShape(arrowMatrix, bamp);
    Coords *reverseCoords = new Coords(150, 150);
    translateShape(arrowMatrix, reverseCoords);
    setNewCoords(arrow, arrowMatrix);

    int arrowN = arrow->getN();
    for (int i = 0; i < arrowN; i++) {
        Coords* first = arrow->getCoords(i);
        Coords* second = arrow->getCoords((i + 1) % arrowN);
        painter.drawLine(first->getX(), first->getY(), second->getX(), second->getY());
    }
    for (int i = 0; i < 3; i++) {
        delete [] arrowMatrix[i];
    }
    delete [] arrowMatrix;
}

void Area::timerEvent(QTimerEvent *event) {
    if (event->timerId() == myTimer) // если наш таймер
    {
        totalAngle += 0.01f * 180 / M_PI;
        cout << totalAngle << endl;
        if (totalAngle >= stopAngle)
            killTimer(myTimer);
        else
            update();
    }
    else
        QWidget::timerEvent(event); // иначе передать для стандартной
    // обработки
}

void Area::hideEvent(QHideEvent *) {
}

void Area::start_prog() {
    myTimer = startTimer(50);
    cout << myTimer;
}

void Area::reset_prog() {
    killTimer(myTimer);
}

void Area::setNewCoords(Shape *shape, float** changeMatrix) {
    int n = shape->getN();
    Coords **coords = new Coords*[n];
    float **newMatrix = new float*[1];
    newMatrix[0] = new float[3];
    for (int i = 0; i < n; i++) {
        coords[i] = shape->getCoords(i);
    }
    for (int i = 0; i < n; i++) {
        newMatrix[0][0] = coords[i]->getX();
        newMatrix[0][1] = coords[i]->getY();
        newMatrix[0][2] = 1;
        matrixMultiplication(newMatrix, 1, 3, changeMatrix, 3, 3);
        shape->SetCoords(i, newMatrix[0][0], newMatrix[0][1]);
    }
    delete [] newMatrix[0];
    delete [] newMatrix;
    delete [] coords;
}

void Area::translateShape(float** oldMatrix, Coords* value) {
    float** newMatrix = new float*[3];
    for (int i = 0; i < 3; i++) {
        newMatrix[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[2][0] = value->getX();
    newMatrix[2][1] = value->getY();
    matrixMultiplication(oldMatrix, 3, 3, newMatrix, 3, 3);
    for (int i = 0; i < 3; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

void Area::rotateShape(float** oldMatrix, float angle) {
    float** newMatrix = new float*[3];
    for (int i = 0; i < 3; i++) {
        newMatrix[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[0][0] = cos(angle);
    newMatrix[0][1] = sin(angle);
    newMatrix[1][0] = -sin(angle);
    newMatrix[1][1] = cos(angle);
    matrixMultiplication(oldMatrix, 3, 3, newMatrix, 3, 3);
    for (int i = 0; i < 3; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

void Area::scaleShape(float** oldMatrix, float value) {
    float** newMatrix = new float*[3];
    for (int i = 0; i < 3; i++) {
        newMatrix[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[0][0] = value;
    newMatrix[1][1] = value;
    matrixMultiplication(oldMatrix, 3, 3, newMatrix, 3, 3);
    for (int i = 0; i < 3; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

void Area::matrixMultiplication(float **first, int firstRow, int firstColumn, float** second, int secondRow, int secondColumn) {
    float** matrixCopy = new float*[firstRow];

    for (int i = 0; i < firstRow; i++) {
        matrixCopy[i] = new float[firstColumn];
        for (int j = 0; j < firstColumn; j++) {
            matrixCopy[i][j] = first[i][j];
            first[i][j] = 0;
        }
    }
    for (int i = 0; i < firstRow; i++) {
        for (int j = 0; j < secondColumn; j++) {
            for (int k = 0; k < firstColumn; k++) {
                first[i][j] += matrixCopy[i][k] * second[k][j];
            }
        }
    }
    for (int i = 0; i < firstRow; i++) {
        delete [] matrixCopy[i];
    }
    delete [] matrixCopy;
}
