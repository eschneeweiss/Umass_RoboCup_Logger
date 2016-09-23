#ifndef FSPINBOX_H
#define FSPINBOX_H

#include <QWidget>
#include <QSpinBox>

using namespace std;

class fSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit fSpinBox(QWidget *parent = 0);
    virtual void stepBy(int step);

signals:
    void frameChanged(int frame);

private slots:
    void stepDown();
    void stepUp();
    void editingFinishedHandler();
};

#endif // FSPINBOX_H
