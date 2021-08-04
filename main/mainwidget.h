#pragma once

#include "pendulum.h"
#include "PWidget.h"
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>


#include <memory>


using std::unique_ptr;



class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);

private:
    void l1SliderInit();
    void l2SliderInit();
    void m1SliderInit();
    void m2SliderInit();
    void checkBoxesInit();

private slots:
    void setL1();
    void setL2();
    void setM1();
    void setM2();
    void rod1Draw(int state);
    void rod2Draw(int state);
    void bob1Draw(int state);
    void bob2Draw(int state);
    void bob1Trace(int state);
    void bob2Trace(int state);

private:
    unique_ptr<DoublePendulum> pendulum;
    PendulumWidget* pWidget;
    
    QSlider* l1Slider;
    QLabel* l1Label;
    QLabel* l1Value;
    QVBoxLayout* l1Layout;

    QSlider* l2Slider;
    QLabel* l2Label;
    QLabel* l2Value;
    QVBoxLayout* l2Layout;

    QSlider* m1Slider;
    QLabel* m1Label;
    QLabel* m1Value;
    QVBoxLayout* m1Layout;

    QSlider* m2Slider;
    QLabel* m2Label;
    QLabel* m2Value;
    QVBoxLayout* m2Layout;
    
    QCheckBox*  rod1DrawCheck;
    QCheckBox*  rod2DrawCheck;
    QCheckBox*  bob1DrawCheck;
    QCheckBox*  bob2DrawCheck;
    QCheckBox*  bob1TraceCheck;
    QCheckBox*  bob2TraceCheck;
    QVBoxLayout* checkBoxLayout;
};