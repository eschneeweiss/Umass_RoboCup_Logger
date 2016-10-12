#ifndef ROBOTPLOT_H
#define ROBOTPLOT_H

#include <QWidget>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "qwt.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_text.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <QVector>
#include "robotcurve.h"
#include <limits>
#include "qwt_legend.h"

#include "qwt_legend_data.h"
Q_DECLARE_METATYPE(QList<QwtLegendData>)

class RobotPlot : public QwtPlot
{
    Q_OBJECT
public:
    explicit RobotPlot(QWidget *parent = 0);

    enum ObjectType {ball = 0, yellowBot, blueBot};

    void addObject(int id, enum ObjectType ot);
    void trimCurves(double currTime, enum ObjectType ot);
    bool removeObject(int id, enum ObjectType ot);
    void removeUnupdatedObjects(double currentTime, enum ObjectType ot);
    bool hideObject(int id, enum ObjectType ot);
    bool showObject(int id, enum ObjectType ot);
    void addPointToObject(double x, double y, double time, int id, enum ObjectType ot);
    void changeDataType(enum RobotCurve::dataType d);
    void setTimePeriod(double timePeriod);
    int getNumObjects(enum ObjectType ot);

    void updateSize();
    
private:
    QVector<RobotCurve*> *yellowBotCurves;
    QVector<RobotCurve*> *blueBotCurves;
    QVector<RobotCurve*> *ballCurves;
    RobotCurve::dataType currentDataType;
    double timePeriod = 0;

signals:
    
public slots:
};

#endif // ROBOTPLOT_H
