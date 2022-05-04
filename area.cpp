#include "area.h"
#include <QPainter>
#include <QTimerEvent>
#include <iostream>

using namespace std;

Area::Area(QWidget *parent):QWidget(parent)
{
    Coords** triangleCoords = new Coords*[3];
    triangleCoords[0] = new Coords(100, 100);
    triangleCoords[1] = new Coords(150, 200);
    triangleCoords[2] = new Coords(200, 150);
    Coords** squareCoords = new Coords*[4];
    squareCoords[0] = new Coords(100, 100);
    squareCoords[1] = new Coords(200, 100);
    squareCoords[2] = new Coords(200, 200);
    squareCoords[3] = new Coords(100, 200);
    triangle = new Shape(3, triangleCoords);
    square = new Shape(4, squareCoords);
    setFixedSize(QSize(300, 300));
}

void Area::showEvent(QShowEvent *) {
//    update();
}

void Area::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::red);
    float **triangleMatrix = new float*[3];
    float **squareMatrix = new float*[3];
    for (int i = 0; i < 3; i++) {
        triangleMatrix[i] = new float[3];
        squareMatrix[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                triangleMatrix[i][j] = 1;
                squareMatrix[i][j] = 1;
            }
            else {
                triangleMatrix[i][j] = 0;
                squareMatrix[i][j] = 0;
            }
        }
    }
    float bamp = 0.1f;
    float centerX = 0, centerY = 0;
    for (int i = 0; i < 3; i++) {
        centerX += triangle->getCoords(i)->getX();
        centerY += triangle->getCoords(i)->getY();
    }
    Coords* triangleCenter = new Coords(-centerX / 3, -centerY / 3);
    centerX = 0;
    centerY = 0;
    for (int i = 0; i < 4; i++) {
        centerX += square->getCoords(i)->getX();
        centerY += square->getCoords(i)->getY();
    }
    Coords* squareCenter = new Coords(-centerX / 4, -centerY / 4);
    // triangle
    translateShape(triangleMatrix, triangleCenter);
    scaleShape(triangleMatrix, 0.95f);
    rotateShape(triangleMatrix, bamp);
    Coords* reverseCenter = new Coords(-triangleCenter->getX(), -triangleCenter->getY());
    translateShape(triangleMatrix, reverseCenter);
    setNewCoords(triangle, triangleMatrix);
    //square
    translateShape(squareMatrix, squareCenter);
    scaleShape(squareMatrix, 1.01f);
    Coords* reverseCenterSquare = new Coords(-squareCenter->getX(), -squareCenter->getY());
    translateShape(squareMatrix, reverseCenterSquare);
    setNewCoords(square, squareMatrix);

    int triangleN = triangle->getN();
    for (int i = 0; i < triangleN; i++) {
        Coords* first = triangle->getCoords(i);
        Coords* second = triangle->getCoords((i + 1) % triangleN);
        painter.drawLine(first->getX(), first->getY(), second->getX(), second->getY());
    }
    int squareN = square->getN();
    for (int i = 0; i < squareN; i++) {
        Coords* first = square->getCoords(i);
        Coords* second = square->getCoords((i + 1) % squareN);
        painter.drawLine(first->getX(), first->getY(), second->getX(), second->getY());
    }
    for (int i = 0; i < 3; i++) {
        delete [] triangleMatrix[i];
    }
    delete [] triangleMatrix;
}

void Area::timerEvent(QTimerEvent *event) {
    if (event->timerId() == myTimer) // если наш таймер
    {
        Coords * first = triangle->getCoords(0);
        Coords * second = triangle->getCoords(1);
        float x1 = first->getX();
        float x2 = second->getX();
        float y1 = first->getY();
        float y2 = second->getY();
        double length = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        if (length < 0.5)
            killTimer(myTimer);
        else
            update(); // обновить внешний вид
    }
    else
        QWidget::timerEvent(event); // иначе передать для стандартной
    // обработки
}

void Area::hideEvent(QHideEvent *) {
//    killTimer(myTimer);
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
