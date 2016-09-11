#ifndef FSLIDER_H
#define FSLIDER_H

#include <QWidget>
#include <QSlider>

class fSlider : public QSlider
{
    Q_OBJECT
public:
    explicit fSlider(QWidget *parent = 0);

signals:
    void frameChanged(int frame);

public slots:
    void sliderPressedHandler();
    void sliderMovedHandler(int value);
};

#endif // FSLIDER_H
