#include "robotcurve.h"

RobotCurve::RobotCurve(QwtPlot *parent, int id, double timePeriod, dataType d, QColor color)
{
    setTitle(QString::number(id));
    this->id = id;
    attach(parent);
    this->timePeriod = timePeriod;
    currentDataType = d;
    setLegendAttribute(QwtPlotCurve::LegendShowLine);
    setPen(color);
}

void RobotCurve::addDataPoint(double x, double y, double time){
    if (timeData.isEmpty() || time > timeData.last()){
        xData.push_back(x);
        yData.push_back(y);
        timeData.push_back(time);
        speedData.push_back(calcSpeed());
        accelData.push_back(calcAccel());
        std::cout<<"pushed back Data point"<<std::endl;
    }
    else {
        for (int i = 0; i < timeData.size() - 1; i++){
            if (timeData.data()[i] >= time){
                if (time == timeData[i]){
                    std::cout<<"Time-match found at time = "<<time<<", index = "<<i<<std::endl;
                    break;
                }
                xData.insert(i, x);
                yData.insert(i, y);
                timeData.insert(i, time);
                speedData.insert(i, calcSpeed());
                accelData.insert(i, calcAccel());
                std::cout<<"Data point inserted at time = "<<time<<", index = "<<i<<std::endl;
                break;
            }
        }
    }
    trimData(time);
    update();
}

void RobotCurve::show(){
    this->update();
    QwtPlotCurve::show();
}

void RobotCurve::trimData(double currTime){
    if (currTime == -1){
        if (timeData.size() == 0){
            return;
        }
        currTime = timeData.last();
    }

    while(currTime - timeData.first() >= timePeriod){
        std::cout<<"trimmed graph"<<std::endl;
        xData.removeFirst();
        yData.removeFirst();
        speedData.removeFirst();
        accelData.removeFirst();
        timeData.removeFirst();
        std::cout<<"graph holds "<<timeData.size()<<" data points"<<std::endl;
    }
    while(timeData.last() - currTime >= timePeriod){
        std::cout<<"trimmed graph backwards"<<std::endl;
        xData.removeLast();
        yData.removeLast();
        speedData.removeLast();
        accelData.removeLast();
        timeData.removeLast();
        std::cout<<"graph holds "<<timeData.size()<<" data points"<<std::endl;
    }
}

double RobotCurve::calcSpeed(){
    if(xData.size() <= 1 && yData.size() <= 1){
        return 0;
    }
    return hypot(xData.data()[xData.size() - 1] - xData.data()[xData.size() - 2], yData.data()[yData.size() - 1] - yData.data()[yData.size() - 2])/(timeData.data()[timeData.size() - 1] - timeData.data()[timeData.size() - 2]);
}

double RobotCurve::calcAccel(){
    if(speedData.size() <= 1){
        return 0;
    }
    return (speedData.data()[speedData.size() - 1] - speedData.data()[speedData.size() - 2])/(timeData.data()[timeData.size() - 1] - timeData.data()[timeData.size() - 2]);
}

void RobotCurve::changeDataType(enum dataType d){
    if (d == currentDataType){
        return;
    }
    currentDataType = d;
    update();
}

void RobotCurve::setTimePeriod(double timePeriod){
    if (timePeriod > 0){
        this->timePeriod = timePeriod;
        trimData();
        update();
    }
}

double RobotCurve::comparePoint(double x, double y, double time){
    if (timeData.last() == time){
        return -1;
    }
    return hypot(xData.last() - x, yData.last() - y);
}

int RobotCurve::getId(){
    return id;
}

double RobotCurve::getCurrentTime(){
    return timeData.last();
}

void RobotCurve::update(){
    if (currentDataType == x){
        this->setSamples(timeData, xData);
    }
    else if (currentDataType == y){
        this->setSamples(timeData, yData);
    }
    else if (currentDataType == speed){
        this->setSamples(timeData, speedData);
    }
    else if (currentDataType == acceleration){
        this->setSamples(timeData, accelData);
    }
    else{
        std::cout<<"defaulting to x"<<std::endl;
        currentDataType = x;
        update();
    }
}
