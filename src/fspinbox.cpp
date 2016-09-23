#include "fspinbox.h"

fSpinBox::fSpinBox(QWidget *parent) : QSpinBox(parent)
{
    QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(editingFinishedHandler()));
}

void fSpinBox::stepDown(){
    setValue(value() - 1);
    emit frameChanged(value());
}

void fSpinBox::stepUp(){
    setValue(value() + 1);
    emit frameChanged(value());
}

void fSpinBox::editingFinishedHandler(){
    emit frameChanged(value());
}

void fSpinBox::stepBy(int steps){
    if (steps < 0)
        stepDown();
    else
        stepUp();
}
