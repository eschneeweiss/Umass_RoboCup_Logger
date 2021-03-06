#ifndef GRAPH_VIEWER_H
#define GRAPH_VIEWER_H

#include <QWidget>
#include "proto/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "qwt.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_text.h"
#include <vector>
#include <math.h>
#include <QVector>
#include "robotplot.h"
#include "trashcan.h"
//temp
#include <iostream>

using namespace std;

class MainWindow;

class graph_viewer : public QWidget
{
    Q_OBJECT
public:
    explicit graph_viewer(QWidget *parent);
    ~graph_viewer();

private:
    MainWindow *mw;
    RobotPlot *plot;

signals:

public slots:
    void updateDisplay(SSL_WrapperPacket *packet);
    void resizeEvent(QResizeEvent* resize);

};

#endif // GRAPH_VIEWER_H
