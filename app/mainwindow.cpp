#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->checkBox_setting, &QCheckBox::stateChanged, ui->frame, &QFrame::setVisible);
    ui->frame->hide();

     ui->checkBox_setting->hide();
    // ui->sl_scale->hide();

    angle = 5;

    sizeA = 90;
    ui->horizontalSlider_A->setValue(sizeA);
    ui->spinBox_a->setValue(sizeA);
    connect(ui->horizontalSlider_A, &QSlider::valueChanged, ui->spinBox_a, &QSpinBox::setValue);
    connect(ui->horizontalSlider_A, &QSlider::valueChanged, this, &MainWindow::setSizeA);



    sizeB = 70;
    ui->horizontalSlider->setValue(sizeB);
    ui->horizontalSlider->setMaximum(sizeA);
    ui->spinBox_b->setValue(sizeB);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox_b, &QSpinBox::setValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::setLenghtB);

    sizeC = 213;
    ui->horizontalSlider_C->setValue(sizeC);
    ui->spinBox_c->setValue(sizeC);
    connect(ui->horizontalSlider_C, &QSlider::valueChanged, ui->spinBox_c, &QSpinBox::setValue);
    connect(ui->horizontalSlider_C, &QSlider::valueChanged, this, &MainWindow::setSizeC);

    sizeD = 193;
    ui->horizontalSlider_D->setValue(sizeD);
    ui->spinBox_d->setValue(sizeD);
    connect(ui->horizontalSlider_D, &QSlider::valueChanged, ui->spinBox_d, &QSpinBox::setValue);
    connect(ui->horizontalSlider_D, &QSlider::valueChanged, this, &MainWindow::setSizeD);

    bY = -7;
    ui->horizontalSlider_PC->setValue(bY);
    ui->spinBox_pc->setValue(bY);
    connect(ui->horizontalSlider_PC, &QSlider::valueChanged, ui->spinBox_pc, &QSpinBox::setValue);
    connect(ui->horizontalSlider_PC, &QSlider::valueChanged, this, &MainWindow::setPointC);


    showHelpers = true;
    ui->checkBox_helpers->setChecked(showHelpers);
    connect(ui->checkBox_helpers, &QCheckBox::stateChanged, this, &MainWindow::setShowHelpers);

    showLabel = false;
    ui->checkBox_labels->setChecked(showLabel);
    connect(ui->checkBox_labels, &QCheckBox::stateChanged, this, &MainWindow::setShowLabels);

    speed = 5;
    ui->horizontalSlider_Speed->setValue(speed);
    ui->spinBox_s->setValue(speed);
    connect(ui->horizontalSlider_Speed, &QSlider::valueChanged, ui->spinBox_s, &QSpinBox::setValue);
    connect(ui->horizontalSlider_Speed, &QSlider::valueChanged, this, &MainWindow::setSpeed);


    connect(ui->pushButton_run, &QPushButton::clicked, this, &MainWindow::run);
    connect(ui->pushButton_stop, &QPushButton::clicked, this, &MainWindow::stop);

    scene = new QGraphicsScene();
    ui->graphicsView_A->setScene(scene);
    ui->graphicsView_A->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_A->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePosition);
    timer->start(speed);

    ui->sl_scale->setValue(50);
    ui->l_scale->setText("x 1.5");
    ui->graphicsView_A->scale(scale, scale);
    connect(ui->sl_scale, &QSlider::valueChanged, this, &MainWindow::setScaleX);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updatePosition()
{
    scene->clear();

    angle = (angle + 1) % 360;

    QPointF startB(0, 0);
    QPointF startA(0, sizeA);

    QPointF pointA = getPointA(angle, sizeB);
    QPointF pointB = getPointB(pointA);

    QPointF pointC(pointB.x(), pointB.y() - sizeD);



    // drawHelpLine(QPointF(-100, sizeA), QPointF(300, sizeA));
    // drawHelpLine(QPointF(-100, pointB.y() - sizeD), QPointF(300, pointB.y() - sizeD));

    //** tunel
    int sX = sizeD;
    int fX = sizeD + 150;
    QPointF pHA_1(sX, pointB.y() + 20);
    QPointF pHA_2(fX, pointB.y() + 20);
    QPointF pHB_1(sX, pointB.y() - 20);
    QPointF pHB_2(fX, pointB.y() - 20);
    drawHelpLine(pHA_1, pHA_2);
    drawHelpLine(pHB_1, pHB_2);



    for (int x = 5; x < (fX-sX); x+=7){
        QPointF p1(sX + x, pointB.y() + 30);
        QPointF p2(sX + x + 5, pointB.y() + 20);
        drawHelpLine(p1, p2);
    }
    for (int x = 5; x < (fX-sX); x+=7){
        QPointF p1(sX + x + 5, pointB.y() - 30);
        QPointF p2(sX + x, pointB.y() - 20);
        drawHelpLine(p1, p2);
    }


    if (showHelpers){
        drawHelpCircle(sizeB);
    }

    //** base
    // drawLine(startA, startB, "#009aa6", "a");
    QPointF pSA(-30, 60);
    QPointF pSB(30, 60);

    drawLine(startB, pSA, "#cbd6cb");
    drawLine(startB, pSB, "#cbd6cb");
    drawLine(pSA, pSB, "#cbd6cb");

    QPointF pH_1(-50, 60);
    QPointF pH_2(50, 60);
    drawHelpLine(pH_1, pH_2);

    for (int x = 5; x < 100; x+=7){
        QPointF p1(-50 + x, 60 + 10);
        QPointF p2(-50 + x + 5, 60);
        drawHelpLine(p1, p2);
    }


    //** hand
    drawLine(startB, pointA, "#009aa6", "b");
    drawLine(pointA, pointB, "#ff8fa0", "c");
    // drawLine(pointB, pointC, "#009aa6", "d");

    //** rect
    drawRect(pointB);




    // drawPoint(startA, 10, clr_point);
    drawPoint(startB, 10, clr_point);
    drawPoint(pointA, 10, clr_point);
    drawPoint(pointB, 10, clr_point);
    // drawPoint(pointC, 10, clr_point);


    scene->update();
}

void MainWindow::drawLine(QPointF start, QPointF finish, QString clr, QString label)
{
    QPen pen;
    pen.setBrush(QBrush(QColor(clr)));
    pen.setWidth(6);

    QGraphicsLineItem *line = new QGraphicsLineItem(start.x(), start.y(), finish.x(), finish.y());
    line->setPen(pen);
    scene->addItem(line);

    if (showLabel){

        QGraphicsTextItem *text = new QGraphicsTextItem();
        text->setPlainText(label);
        text->setPos(((finish.x() + start.x()) / 2) + 10, ((finish.y() + start.y()) / 2) - 10);
        scene->addItem(text);
    }
}

void MainWindow::drawHelpLine(QPointF start, QPointF finish)
{
    QPen pen;
    pen.setBrush(QBrush(Qt::black));
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);

    QGraphicsLineItem *line = new QGraphicsLineItem(start.x(), start.y(), finish.x(), finish.y());
    line->setPen(pen);
    scene->addItem(line);
}

void MainWindow::drawHelpCircle(int radius)
{
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::black);

    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem();
    circle->setRect(-radius, -radius, 2*radius, 2*radius);
    circle->setPen(pen);
    circle->setBrush(QBrush(Qt::NoBrush));

    scene->addItem(circle);
}

void MainWindow::drawText(QString label)
{
    QGraphicsTextItem *txt = new QGraphicsTextItem();
    txt->setPlainText(label);
    // txt->setPos()

    scene->addItem(txt);
}

void MainWindow::drawRect(QPointF point)
{
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);

    QGraphicsRectItem *rect = new QGraphicsRectItem(point.x() - 25, point.y() - 15, 50, 30);
    rect->setPen(pen);
    rect->setBrush(QBrush(Qt::NoBrush));
    scene->addItem(rect);

}


void MainWindow::drawPoint(QPointF pointX, int radius, QString clr)
{
    QGraphicsEllipseItem *point = new QGraphicsEllipseItem(pointX.x() - (radius / 2), pointX.y() - (radius / 2), radius, radius);
    point->setBrush(QBrush(QColor(clr)));
    scene->addItem(point);
}



QPointF MainWindow::getPointA(int angle, int radius)
{
    float rad = angle * M_PI / 180;

    float x = radius * cos(rad);
    float y = radius * sin(rad);

    return QPointF(x, y);
}

QPointF MainWindow::getPointB(QPointF pointA)
{
    float bX = 0;
    if (bX == pointA.x()){
        bX = pointA.x() + sizeC;
    } else {
        float catA = pointA.y() - bY;
        float catB = qSqrt(qPow(sizeC, 2) - qPow(catA, 2));
        bX = pointA.x() + catB;
    }
    return QPointF(bX, bY);
}

void MainWindow::setLenghtB(int value)
{
    sizeB = value;
}

void MainWindow::setSizeA(int value)
{
    sizeA = value;
}

void MainWindow::setSizeC(int value)
{
    sizeC = value;
}

void MainWindow::setSizeD(int value)
{
    sizeD = value;
}

void MainWindow::setShowLabels(bool value)
{
    showLabel = value;
}

void MainWindow::setShowHelpers(bool value)
{
    showHelpers = value;
}

void MainWindow::setSpeed(int value)
{
    timer->stop();
    speed = value;
    timer->start(speed);
}

void MainWindow::setScaleX(int value)
{
    //scale
    scale = 1 + float(value * 0.01);
    ui->graphicsView_A->resetTransform();
    ui->graphicsView_A->scale(scale, scale);
    ui->l_scale->setText(QString("x %0").arg(scale));
}

void MainWindow::setPointC(int value)
{
    bY = value;
}

void MainWindow::run()
{
    timer->start(speed);
}

void MainWindow::stop()
{
    timer->stop();
}





