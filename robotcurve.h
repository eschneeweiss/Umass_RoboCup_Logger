#ifndef ROBOTCURVE_H
#define ROBOTCURVE_H

#include <QWidget>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_text.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <QVector>

class RobotCurve : public QwtPlotCurve
{
    //Q_OBJECT
public:
    enum dataType {x = 0, y, speed, acceleration};

    explicit RobotCurve(QwtPlot *parent, int id, double timePeriod, dataType d, QColor color);

    void addDataPoint(double x, double y, double time);
    void show();
    void changeDataType(enum dataType d);
    void update();
    void setTimePeriod(double timePeriod);
    double comparePoint(double x, double y, double time);
    int getId();
    double getCurrentTime();

private:

    void trimData(double currTime = -1);
    double calcSpeed();
    double calcAccel();

    double timePeriod;
    int id;
    dataType currentDataType;
    QVector<double> xData;
    QVector<double> yData;
    QVector<double> speedData;
    QVector<double> accelData;
    QVector<double> timeData;

signals:
    
public slots:
    
};

#endif // ROBOTCURVE_H
