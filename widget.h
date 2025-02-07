#ifndef WIDGET_H
#define WIDGET_H

#include <QChartView>
#include <QLineSeries>
#include <QLabel>

class QTimer;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using namespace  QtCharts;
#endif


class ChartView : public QChartView
{
    Q_OBJECT

public:
    explicit ChartView(double koef, double offset = 0, const QColor &clr = Qt::black, QWidget *parent = nullptr);
    virtual ~ChartView() override;


    void disableBackground();


protected:


private slots:

    void updateGraph();


private:

    int m_lastX;

    double m_koef;
    double m_offset;

    QTimer *m_updateTimer;
    QLineSeries *m_sinSer;
};



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget() override;


protected:

    virtual void paintEvent(QPaintEvent *e) override;

public slots:
    void timeUpdate();

private:
    QLabel *dataTime;
    QLabel *stopWatch;
    int s=0;
    int m=0;
    int ms=0;
    int h=0;
};

#endif // WIDGET_H
