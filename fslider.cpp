#include "fslider.h"

fSlider::fSlider(QWidget *parent) : QSlider(parent)
{
    this->setOrientation(Qt::Horizontal);
    connect(this, SIGNAL(sliderPressed()), this, SLOT(sliderPressedHandler()));
    connect(this, SIGNAL(sliderMoved(int)), this, SLOT(sliderMovedHandler(int)));
}

void fSlider::sliderPressedHandler(){
    emit frameChanged(value());
}

void fSlider::sliderMovedHandler(int value){
    emit frameChanged(value);
}
