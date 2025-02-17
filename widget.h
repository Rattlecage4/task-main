#ifndef WIDGET_H
#define WIDGET_H

#include <QChartView>
#include <QLineSeries>
#include <QLabel>
#include <QKeyEvent>

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
    void keyPressEvent(QKeyEvent *m_press) override;


private slots:

    void updateGraph();


private:

    int m_lastX;

    double m_koef;
    double m_offset;

    QTimer *m_updateTimer;
    QTimer *m_updateGraphTimer;
    QLineSeries *m_sinSer;
    QLineSeries *leftMarker;

    float timerRange = 0;
};



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget() override;


protected:

    virtual void paintEvent(QPaintEvent *e) override;
    void buttonShowSetting();
    void buttonHomeSetting();

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
