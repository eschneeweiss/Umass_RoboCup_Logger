#include "graph_viewer.h"
#include "qwt_legend_data.h"

graph_viewer::graph_viewer(QWidget *parent, QSize initSize) : QWidget(parent)
{
    this->initSize = initSize;
    std::cout<<"graph_viewer initSize: w"<<this->initSize.width()<<", h"<<this->initSize.height()<<std::endl;

    plot = new RobotPlot(this);
    plot->setTimePeriod(2);
    plot->show();

    plot->changeDataType(RobotCurve::speed);
}

QSize graph_viewer::sizeHint(){
    std::cout<<"graph_viewer sizeHint called"<<std::endl;
    return initSize;
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

        }

        for (int i = 0; i < detection.robots_yellow_size(); i++){
            SSL_DetectionRobot robot = detection.robots_yellow(i);
            plot->addPointToObject(robot.x(), robot.y(), currentTime, robot.robot_id(), RobotPlot::yellowBot);
        }
        if (detection.robots_yellow_size() < plot->getNumObjects(RobotPlot::yellowBot)){

        }

        for (int i = 0; i < detection.balls_size(); i++){
            SSL_DetectionBall ball = detection.balls(i);
            plot->addPointToObject(ball.x(), ball.y(), currentTime, -1, RobotPlot::ball);
        }
        if (detection.balls_size() < plot->getNumObjects(RobotPlot::ball)){

        }
    }
}

void graph_viewer::resizeEvent(QResizeEvent* resize){
    plot->updateSize();
}

graph_viewer::~graph_viewer(){
    //clean up
}
