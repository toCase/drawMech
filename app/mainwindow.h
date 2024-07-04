#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include "math.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsScene *scene;
    QTimer *timer;

    int angle = 0;
    float bY = -50;

    int sizeB;
    int sizeA;
    int sizeC;
    int sizeD;


    QString clr_point = "#e0218a";

    int speed;
    float scale = 1.5;


private:
    Ui::MainWindow *ui;

    void updatePosition();

    void drawLine(QPointF start, QPointF finish, QString clr, QString label = QString());

    void drawHelpLine(QPointF start, QPointF finish);
    void drawHelpCircle(int radius);
    void drawText(QString label);
    void drawRect(QPointF point);

    void drawPoint(QPointF pointX, int radius, QString clr);


    QPointF getPointA(int angle, int radius);
    QPointF getPointB(QPointF pointA);

    void setScaleX(int value);


};
#endif // MAINWINDOW_H
