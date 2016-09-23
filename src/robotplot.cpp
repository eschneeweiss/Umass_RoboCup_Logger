#include "robotplot.h"

RobotPlot::RobotPlot(QWidget *parent) : QwtPlot(parent)
{
    //TODO (Eddy) when back tracking delete past
    qRegisterMetaType<QList<QwtLegendData> >();

    setAutoReplot(true);

    setCanvasBackground(* new QBrush(Qt::black));

    setAxisScale(QwtPlot::xBottom, 0.0, timePeriod);
    setAxisAutoScale(QwtPlot::yLeft, true);

    ballCurves = new QVector<RobotCurve*>;
    yellowBotCurves = new QVector<RobotCurve*>;
    blueBotCurves = new QVector<RobotCurve*>;

    changeDataType(RobotCurve::speed);//default
    setAxisTitle(QwtPlot::yLeft, "Speed: cm/s");
    setAxisTitle(QwtPlot::xBottom, "Time: seconds");

    QwtLegend *plotLegend = new QwtLegend(this);
    insertLegend(plotLegend, QwtPlot::RightLegend);
}

void RobotPlot::addObject(int id, enum ObjectType ot){
    if (ot == yellowBot){
        RobotCurve *Object = new RobotCurve(this, id, timePeriod, currentDataType, QColor("yellow"));
        yellowBotCurves->push_back(Object);
    }
    else if (ot == blueBot){
        RobotCurve *Object = new RobotCurve(this, id, timePeriod, currentDataType, QColor("blue"));
        blueBotCurves->push_back(Object);
    }
    else {
        RobotCurve *Object = new RobotCurve(this, id, timePeriod, currentDataType, QColor("orange"));
        ballCurves->push_back(Object);
    }
}

bool RobotPlot::removeObject(int id, enum ObjectType ot){
    if (ot == yellowBot){
        for (int i = 0; i < yellowBotCurves->size(); i++){
            if(yellowBotCurves->data()[i]->getId() == id){
                yellowBotCurves->remove(i);
                return true;
            }
        }
        return false;
    }
    else if (ot == blueBot){
        for (int i = 0; i < blueBotCurves->size(); i++){
            if(blueBotCurves->data()[i]->getId() == id){
                blueBotCurves->remove(i);
                return true;
            }
        }
        return false;
    }
    else {
        for (int i = 0; i < ballCurves->size(); i++){
            if(ballCurves->data()[i]->getId() == id){
                ballCurves->remove(i);
                return true;
            }
        }
        return false;
    }
}

bool RobotPlot::hideObject(int id, enum ObjectType ot){
    if (ot == yellowBot){
        for (int i = 0; i < yellowBotCurves->size(); i++){
            if(yellowBotCurves->data()[i]->getId() == id){
                yellowBotCurves->data()[i]->hide();
                return true;
            }
        }
        return false;
    }
    else if (ot == blueBot){
        for (int i = 0; i < blueBotCurves->size(); i++){
            if(blueBotCurves->data()[i]->getId() == id){
                blueBotCurves->data()[i]->hide();
                return true;
            }
        }
        return false;
    }
    else {
        for (int i = 0; i < ballCurves->size(); i++){
            if(ballCurves->data()[i]->getId() == id){
                ballCurves->data()[i]->hide();
                return true;
            }
        }
        return false;
    }
}

bool RobotPlot::showObject(int id, enum ObjectType ot){
    if (ot == yellowBot){
        for (int i = 0; i < yellowBotCurves->size(); i++){
            if(yellowBotCurves->data()[i]->getId() == id){
                yellowBotCurves->data()[i]->show();
                return true;
            }
        }
        return false;
    }
    else if (ot == blueBot){
        for (int i = 0; i < blueBotCurves->size(); i++){
            if(blueBotCurves->data()[i]->getId() == id){
                blueBotCurves->data()[i]->show();
                return true;
            }
        }
        return false;
    }
    else {
        for (int i = 0; i < ballCurves->size(); i++){
            if(ballCurves->data()[i]->getId() == id){
                ballCurves->data()[i]->show();
                return true;
            }
        }
        return false;
    }
}

void RobotPlot::addPointToObject(double x, double y, double time, int id, enum ObjectType ot){
    if (time > (this->axisScaleDiv(QwtPlot::xBottom)).upperBound()){
        this->setAxisScale(QwtPlot::xBottom, time - timePeriod, time);
    }
    else if (time < (this->axisScaleDiv(QwtPlot::xBottom)).lowerBound()){
        this->setAxisScale(QwtPlot::xBottom, time, time + timePeriod);
    }

    if (ot == ball){
        if (ballCurves->size() <= 1){
            // only one curve exists, add this datapoint to the curve
            if (ballCurves->size() == 1){
                ballCurves->first()->addDataPoint(x, y, time);
            } else {
                // no ball curves yet exist; create a new ball cuve, and
                addObject(-1, ball);
                // Add this datapoint to this new ball curve
                ballCurves->last()->addDataPoint(x, y, time);
            }
        } else {    // more than one ball curve already exists
            // initialize variables for determining which ball curve
            //    should receive this datapoint
            int mlb = -1;
            double currDist;
            double minDist = std::numeric_limits<double>::max();
            // for each ball curve in list of ball curve
            for (int i = 0; i < ballCurves->size(); i++){
                // calculate the distance between this datapoint and the last
                //   datapoint of each ball curve
                currDist = ballCurves->data()[i]->comparePoint(x, y, time);
                // if the datapoint is a valid new datapoint, AND its distance
                //   from the last datapoint of the current curve is less than
                //   the previous minimum distance between the datapoint and
                //   the last datapoint of the previously checked ball curves
                if (currDist >= 0 && currDist < minDist){
                    // update value of previous minimum distance, and indicator
                    //   to most appropriate curve to receive datapoint
                    minDist = currDist;
                    mlb = i;
                }
            }
            // if "Best fitting" ball curve is found
            if (mlb >= 0){
                // Add this datapoint to the ball curve
                ballCurves->data()[mlb]->addDataPoint(x, y, time);
            }
            else {      // Otherwise, (no "best fiiting" ball curve was found)
                int newID = -1;
                //  add comment here
                for (int i = 0; i < ballCurves->size(); i++){
                    if (ballCurves->data()[i]->getId() == newID){
                        i = 0;
                        newID--;
                    }
                }
                // Create a new ball curve, and
                addObject(newID, ball);
                // Add this datapoint to this new ball curve
                ballCurves->last()->addDataPoint(x, y, time);
            }
        }       // end of "if more than one ball curve already exits"
    }
    else if (ot == yellowBot){
        if (id < 0){
            int mlyb = -1;
            double currDist;
            double minDist = std::numeric_limits<double>::max();
            for (int i = 0; i < yellowBotCurves->size(); i++){
                if (yellowBotCurves->data()[i]->getId() < 0){
                    currDist = yellowBotCurves->data()[i]->comparePoint(x, y, time);
                    if (currDist < minDist){
                        minDist = currDist;
                        mlyb = i;
                    }
                }
            }
            if (mlyb >= 0){
                yellowBotCurves->data()[mlyb]->addDataPoint(x, y, time);
            }
            else {
                int newID = -1;
                for(int i = 0; i < yellowBotCurves->size(); i++){
                    if (yellowBotCurves->data()[i]->getId() < 0 && yellowBotCurves->data()[i]->getId() == newID){
                        i = 0;
                        newID--;
                    }
                }
                addObject(newID, yellowBot);
                yellowBotCurves->last()->addDataPoint(x, y, time);
            }
        }
        else {
            bool robotFound = false;
            for (int i = 0; i < yellowBotCurves->size(); i++){
                if (yellowBotCurves->data()[i]->getId() == id){
                    yellowBotCurves->data()[i]->addDataPoint(x, y, time);
                    robotFound = true;
                    break;
                }
            }
            if (!robotFound){
                addObject(id, yellowBot);
                yellowBotCurves->last()->addDataPoint(x, y, time);
            }
        }
    }
    else if (ot == blueBot){
        if (id < 0){
            int mlbb = -1;
            double currDist;
            double minDist = std::numeric_limits<double>::max();
            for (int i = 0; i < blueBotCurves->size(); i++){
                if (blueBotCurves->data()[i]->getId() < 0){
                    currDist = blueBotCurves->data()[i]->comparePoint(x, y, time);
                    if (currDist < minDist){
                        minDist = currDist;
                        mlbb = i;
                    }
                }
            }
            if (mlbb >= 0){
                blueBotCurves->data()[mlbb]->addDataPoint(x, y, time);
            }
            else {
                int newID = -1;
                for(int i = 0; i < blueBotCurves->size(); i++){
                    if (blueBotCurves->data()[i]->getId() < 0 && blueBotCurves->data()[i]->getId() == newID){
                        i = 0;
                        newID--;
                    }
                }
                addObject(newID, blueBot);
                blueBotCurves->last()->addDataPoint(x, y, time);
            }
        }
        else {
            bool robotFound = false;
            for (int i = 0; i < blueBotCurves->size(); i++){
                if (blueBotCurves->data()[i]->getId() == id){
                    blueBotCurves->data()[i]->addDataPoint(x, y, time);
                    robotFound = true;
                    break;
                }
            }
            if (!robotFound){
                addObject(id, blueBot);
                blueBotCurves->last()->addDataPoint(x, y, time);
            }
        }
    }
}

void RobotPlot::trimCurves(double currTime, enum ObjectType ot){
    if (ot == blueBot){
        for (int i = 0; i < blueBotCurves->size(); i++){
            if (blueBotCurves->data()[i]->getCurrentTime() != currTime){
                blueBotCurves->remove(i);
            }
        }
    }
    else if (ot == yellowBot){
        for (int i = 0; i < yellowBotCurves->size(); i++){
            if (yellowBotCurves->data()[i]->getCurrentTime() != currTime){
                yellowBotCurves->remove(i);
            }
        }
    }
    else if (ot == ball){
        for (int i = 0; i < ballCurves->size(); i++){
            if (ballCurves->data()[i]->getCurrentTime() != currTime){
                ballCurves->remove(i);
            }
        }
    }
}

int RobotPlot::getNumObjects(enum ObjectType ot){
    if (ot == blueBot){
        return blueBotCurves->size();
    }
    else if (ot == yellowBot){
        return yellowBotCurves->size();
    }
    else {
        return ballCurves->size();
    }
}

void RobotPlot::setTimePeriod(double timePeriod){
    this->timePeriod = timePeriod;
    for (int i = 0; i < yellowBotCurves->size(); i++){
        yellowBotCurves->data()[i]->setTimePeriod(timePeriod);
    }
    for (int i = 0; i < blueBotCurves->size(); i++){
        blueBotCurves->data()[i]->setTimePeriod(timePeriod);
    }
    for (int i = 0; i < ballCurves->size(); i++){
        ballCurves->data()[i]->setTimePeriod(timePeriod);
    }
    this->setAxisScale(QwtPlot::xBottom, 0.0, timePeriod);
}

void RobotPlot::changeDataType(enum RobotCurve::dataType d){
    currentDataType = d;

    switch(d){
        case RobotCurve::x: setAxisTitle(QwtPlot::yLeft, "x: cm"); break;
        case RobotCurve::y: setAxisTitle(QwtPlot::yLeft, "y: cm"); break;
        case RobotCurve::speed: setAxisTitle(QwtPlot::yLeft, "speed: cm/s"); break;
        case RobotCurve::acceleration: setAxisTitle(QwtPlot::yLeft, "accel: cm/s^2"); break;
        default: setAxisTitle(QwtPlot::yLeft, "???");
    }

    for (int i = 0; i < yellowBotCurves->size(); i++){
        yellowBotCurves->data()[i]->changeDataType(d);
    }
    for (int i = 0; i < blueBotCurves->size(); i++){
        blueBotCurves->data()[i]->changeDataType(d);
    }
    for (int i = 0; i < ballCurves->size(); i++){
        ballCurves->data()[i]->changeDataType(d);
    }
}

void RobotPlot::updateSize(){
    this->resize(this->parentWidget()->width(), this->parentWidget()->height());
}
