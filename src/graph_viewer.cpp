#include "graph_viewer.h"
#include "mainwindow.h"
#include "qwt_legend_data.h"

graph_viewer::graph_viewer(QWidget *parent) : QWidget(parent)
{
    mw = (MainWindow*)parent;

    plot = new RobotPlot(this);
    plot->setTimePeriod(2);
    plot->show();

    plot->changeDataType(RobotCurve::speed);
}

void graph_viewer::updateDisplay(SSL_WrapperPacket *packet){
    if (packet->has_detection()){
        SSL_DetectionFrame detection = packet->detection();
        double currentTime = detection.t_capture();
        for (int i = 0; i < detection.robots_blue_size(); i++){
            SSL_DetectionRobot robot = detection.robots_blue(i);
            plot->addPointToObject(robot.x(), robot.y(), currentTime, robot.robot_id(), RobotPlot::blueBot);
        }
        if (detection.robots_blue_size() < plot->getNumObjects(RobotPlot::blueBot)){
            plot->removeUnupdatedObjects(currentTime, RobotPlot::blueBot);
        }

        for (int i = 0; i < detection.robots_yellow_size(); i++){
            SSL_DetectionRobot robot = detection.robots_yellow(i);
            plot->addPointToObject(robot.x(), robot.y(), currentTime, robot.robot_id(), RobotPlot::yellowBot);
        }
        if (detection.robots_yellow_size() < plot->getNumObjects(RobotPlot::yellowBot)){
            plot->removeUnupdatedObjects(currentTime, RobotPlot::yellowBot);
        }

        for (int i = 0; i < detection.balls_size(); i++){
            SSL_DetectionBall ball = detection.balls(i);
            plot->addPointToObject(ball.x(), ball.y(), currentTime, -1, RobotPlot::ball);
        }
        if (detection.balls_size() < plot->getNumObjects(RobotPlot::ball)){
            plot->removeUnupdatedObjects(currentTime, RobotPlot::ball);
        }
    }
    mw->trashCan->throwAway(packet);
}

void graph_viewer::resizeEvent(QResizeEvent* resize){
    plot->updateSize();
}

graph_viewer::~graph_viewer(){
    //clean up
}
