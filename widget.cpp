#include "widget.h"

#include <QChart>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QPainter>
#include <QPalette>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QPushButton>



ChartView::ChartView(double koef, double offset, const QColor &clr, QWidget *parent)
    : QChartView (parent)
{

    m_koef = koef;
    m_offset = offset;

    m_lastX = 0;

    m_updateTimer = new QTimer(this);

    setChart(new QChart());
    chart()->createDefaultAxes();

    m_sinSer = new QLineSeries(chart());

    m_sinSer->setColor(clr);

    auto timeAxis = new QDateTimeAxis(this); //new
    


    //    chart()->legend()->close();


    //    for(int i=0;i<1000;++i){
    //        *sinSer<<QPointF(i, qSin(i * koef) + offset);
    //    }


    chart()->addSeries(m_sinSer);

    chart()->legend()->close();

    chart()->addAxis(timeAxis, Qt::AlignBottom);
    m_sinSer->attachAxis(timeAxis);

    chart()->createDefaultAxes();

    chart()->axisY()->setRange(offset - 1, offset + 1);

    QPen mypen = m_sinSer->pen();
    mypen.setWidth(5);
    m_sinSer->setPen(mypen);





    connect(m_updateTimer, &QTimer::timeout, this, &ChartView::updateGraph);

    //    m_timerId = startTimer(1000);


    m_updateTimer->start(1000);

}

ChartView::~ChartView()
{

}

void ChartView::disableBackground()
{
    chart()->setBackgroundVisible(false);

    auto customPalette = palette();

    customPalette.setColor(QPalette::Window, Qt::transparent);

    setAutoFillBackground(true);

    setPalette(customPalette);
}

void ChartView::updateGraph()
{
    setUpdatesEnabled(false);


    static int timerRange = 0;

    for(int i = 0; i < 100; ++i){

        double xVal = m_lastX + i;

        *m_sinSer<<QPointF(xVal, qSin(xVal*m_koef)+ m_offset);
    }

    chart()->axisX()->setRange(timerRange, timerRange + 10);
    chart()->axisX()->setTitleVisible(false);


    m_lastX += 100;

    timerRange += 1;
    m_sinSer->remove(0);

    setUpdatesEnabled(true);

    update();
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setMinimumSize(640, 360);

    QTimer *timer = new QTimer(this);
    timer->callOnTimeout(this,&Widget::timeUpdate);
    timer->start(1000);

    dataTime = new QLabel(this);
    dataTime->setStyleSheet("font-size: 24px;");
    auto Graph = new QLabel(this);
    Graph->setStyleSheet("font-size: 35px;color: darkBlue; font-family: Arial;");
    Graph->setText("Graph");
    stopWatch= new QLabel(this);
    stopWatch->setStyleSheet("font-size: 24px;");
    stopWatch->setText(QString::number(h)+":"+QString::number(m)+":"+QString::number(s));

    dataTime->setText(QTime::currentTime().toString("hh:mm"));

    auto buttonHome = new QPushButton();
    buttonHome->setIcon(QIcon(":/resources/image/reverse"));
    buttonHome->setIconSize(QSize(80,80));
    buttonHome->setFixedSize(80,80);
    buttonHome->setFlat(true);

    auto buttonSettings = new QPushButton();
    buttonSettings->setIcon(QIcon(":/resources/image/settings"));
    buttonSettings->setIconSize(QSize(80,80));
    buttonSettings->setFixedSize(80,80);
    buttonSettings->setFlat(true);

    auto mainLay = new QVBoxLayout(this);
    auto buttonLay = new QGridLayout(this);

    auto chartView = new ChartView(0.01, 0, Qt::blue, this);
    auto chartView2 = new ChartView(0.1, 5,Qt::red, this);
    auto chartView3 = new ChartView(0.5, 5, Qt::yellow, this);
    auto chartView4 = new ChartView(0.5, 5,Qt::cyan, this);


    chartView->disableBackground();
    chartView2->disableBackground();
    chartView3->disableBackground();
    chartView4->disableBackground();

    mainLay->addLayout(buttonLay);
    buttonLay->setContentsMargins(50,10,50,10);
    buttonLay->setSpacing(20);

    buttonLay->addWidget(dataTime,0,0);
    buttonLay->addWidget(stopWatch,0,2);
    buttonLay->addWidget(Graph,0,1,Qt::AlignHCenter);
    buttonLay->addWidget(buttonHome,1,0);
    buttonLay->addWidget(buttonSettings,1,2);

    mainLay->setContentsMargins(1,50,1,0);
    mainLay->addWidget(chartView);
    mainLay->addWidget(chartView2);
    mainLay->addWidget(chartView3);
    mainLay->addWidget(chartView4);

}


void Widget::timeUpdate()
{
    dataTime->setText(QTime::currentTime().toString("hh:mm"));
    dataTime->update();

    s++;
    if(s>=60){
        s=0;
        m++;}
    if(m>=60){
        m=0;
        h++;}

    stopWatch->setText(QString::number(h)+":"+QString::number(m)+":"+QString::number(s));
    stopWatch->update();
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *e)
{

    QWidget::paintEvent(e);

    QPainter p(this);
    QPainter Py(this);

    p.save();
    Py.save();

    int x = 0; // Новая позиция по оси X
    int y = 0; // Новая позиция по оси Y
    int width = 200; // Новая ширина
    int height = 1000; // Новая высота

    QRect rectY(x, y, width, height);


    p.drawPixmap(rect(), QPixmap(":resources/image/back"));
    Py.drawPixmap(QRect(rectY), QPixmap(":resources/image/Yzor"));

    p.restore();
    Py.restore();


}
