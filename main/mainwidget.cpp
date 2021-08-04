#include "mainwidget.h"

#include "PWidget.h"
#include <QHBoxLayout>
#include <QLabel>


MainWidget::MainWidget(QWidget* parent) : QWidget(parent), pendulum(new DoublePendulum) {
    pWidget = new PendulumWidget(pendulum.get(), this);

    l1SliderInit();
    l2SliderInit();
    m1SliderInit();
    m2SliderInit();
    checkBoxesInit();

    connect(l1Slider, &QSlider::valueChanged, this, &setL1);
    connect(l2Slider, &QSlider::valueChanged, this, &setL2);
    connect(m1Slider, &QSlider::valueChanged, this, &setM1);
    connect(m2Slider, &QSlider::valueChanged, this, &setM2);

    connect(rod1DrawCheck, &QCheckBox::stateChanged, this, &rod1Draw);
    connect(rod2DrawCheck, &QCheckBox::stateChanged, this, &rod2Draw);
    connect(bob1DrawCheck, &QCheckBox::stateChanged, this, &bob1Draw);
    connect(bob2DrawCheck, &QCheckBox::stateChanged, this, &bob2Draw);
    connect(bob1TraceCheck, &QCheckBox::stateChanged, this, &bob1Trace);
    connect(bob2TraceCheck, &QCheckBox::stateChanged, this, &bob2Trace);
    
    auto* mainLayout = new QHBoxLayout(this);
    auto* sliderLayout = new QVBoxLayout;

    sliderLayout->addLayout(l1Layout);
    sliderLayout->addLayout(l2Layout);
    sliderLayout->addLayout(m1Layout);
    sliderLayout->addLayout(m2Layout);
    sliderLayout->addLayout(checkBoxLayout);
    sliderLayout->setContentsMargins(11,11,25,11);

    mainLayout->addLayout(sliderLayout, 2);
    mainLayout->addWidget(pWidget, 3);
}

void MainWidget::setL1() {
    double curL1 = pendulum->getL1();
    double curOmega1 = pendulum->getOmega1();
    double sliderVal = (double)l1Slider->value() / 10;
    pendulum->setL1(sliderVal);
    l1Value->setNum(sliderVal);

    double divisor = 1;
    if (curL1 > sliderVal) divisor = (double)sliderVal / curL1;
    if (curL1 < sliderVal) divisor = curL1 / sliderVal;

    pendulum->setOmega1(curOmega1*divisor);
}

void MainWidget::setL2() {
    double curL2 = pendulum->getL2();
    double curOmega1 = pendulum->getOmega1();
    double sliderVal = (double)l2Slider->value() / 10;
    pendulum->setL2(sliderVal);
    l2Value->setNum(sliderVal);

    double divisor = 1;
    if (curL2 > sliderVal) divisor = (double)sliderVal / curL2;
    if (curL2 < sliderVal) divisor = curL2 / sliderVal;

    pendulum->setOmega1(curOmega1*divisor);
}

void MainWidget::setM1() {
    double curM1 = pendulum->getM1();
    double sliderVal = (double)m1Slider->value() / 10;
    pendulum->setM1(sliderVal);
    m1Value->setNum(sliderVal);
}

void MainWidget::setM2() {
    double curM2 = pendulum->getM2();
    double sliderVal = (double)m2Slider->value() / 10;
    pendulum->setM2(sliderVal);
    m2Value->setNum(sliderVal);
}

void MainWidget::rod1Draw(int state) {
    if (state == Qt::Checked) pWidget->rod1Draw = true;
    else pWidget->rod1Draw = false;
}

void MainWidget::rod2Draw(int state) {
    if (state == Qt::Checked) pWidget->rod2Draw = true;
    else pWidget->rod2Draw = false;
}

void MainWidget::bob1Draw(int state) {
    if (state == Qt::Checked) pWidget->bob1Draw = true;
    else pWidget->bob1Draw = false;
}

void MainWidget::bob2Draw(int state) {
    if (state == Qt::Checked) pWidget->bob2Draw = true;
    else pWidget->bob2Draw = false;
}

void MainWidget::bob2Trace(int state) {
    if (state == Qt::Checked) pWidget->bob2Trace = true;
    else pWidget->bob2Trace = false;
}

void MainWidget::bob1Trace(int state) {
    if (state == Qt::Checked) pWidget->bob1Trace = true;
    else pWidget->bob1Trace = false;
}

void MainWidget::l1SliderInit() {
    l1Slider = new QSlider(Qt::Horizontal, this);
    l1Slider->setValue(pendulum->getL1() * 10);
    l1Slider->setMinimum(10);
    l1Slider->setMaximum(50);

    l1Label = new QLabel("Length of rod 1", this);
    QString l1LabelVal = QString::number((double)l1Slider->value()/10);
    l1Value = new QLabel(l1LabelVal, this);
    l1Layout = new QVBoxLayout;
    auto* l1sl = new QHBoxLayout;
    l1sl->addWidget(l1Slider);
    l1sl->addWidget(l1Value);
    l1Layout->addWidget(l1Label);
    l1Layout->addLayout(l1sl);
    l1Layout->addStretch();
}

void MainWidget::l2SliderInit() {
    l2Slider = new QSlider(Qt::Horizontal, this);
    l2Slider->setValue(pendulum->getL2() * 10);
    l2Slider->setMinimum(10);
    l2Slider->setMaximum(50);

    l2Label = new QLabel("Length of rod 2", this);
    QString l2LabelVal = QString::number((double)l2Slider->value()/10);
    l2Value = new QLabel(l2LabelVal, this);
    l2Layout = new QVBoxLayout;
    auto* l2sl = new QHBoxLayout;
    l2sl->addWidget(l2Slider);
    l2sl->addWidget(l2Value);
    l2Layout->addWidget(l2Label);
    l2Layout->addLayout(l2sl);
    l2Layout->addStretch();
}

void MainWidget::m1SliderInit() {
    m1Slider = new QSlider(Qt::Horizontal, this);
    m1Slider->setValue(pendulum->getM1() * 10);
    m1Slider->setMinimum(10);
    m1Slider->setMaximum(50);

    m1Label = new QLabel("Mass of bob 1", this);
    QString m1LabelVal = QString::number((double)m1Slider->value()/10);
    m1Value = new QLabel(m1LabelVal, this);
    m1Layout = new QVBoxLayout;
    auto* m1sl = new QHBoxLayout;
    m1sl->addWidget(m1Slider);
    m1sl->addWidget(m1Value);
    m1Layout->addWidget(m1Label);
    m1Layout->addLayout(m1sl);
    m1Layout->addStretch();
}

void MainWidget::m2SliderInit() {
    m2Slider = new QSlider(Qt::Horizontal, this);
    m2Slider->setValue(pendulum->getM2() * 10);
    m2Slider->setMinimum(10);
    m2Slider->setMaximum(50);

    m2Label = new QLabel("Mass of bob 2", this);
    QString m2LabelVal = QString::number((double)m2Slider->value()/10);
    m2Value = new QLabel(m2LabelVal, this);
    m2Layout = new QVBoxLayout;
    auto* m2sl = new QHBoxLayout;
    m2sl->addWidget(m2Slider);
    m2sl->addWidget(m2Value);
    m2Layout->addWidget(m2Label);
    m2Layout->addLayout(m2sl);
    m2Layout->addStretch();
}

void MainWidget::checkBoxesInit() {
    checkBoxLayout = new QVBoxLayout;
    rod1DrawCheck = new QCheckBox("Draw rod 1", this);
    rod1DrawCheck->setCheckState(Qt::Checked);
    rod2DrawCheck = new QCheckBox("Draw rod 2", this);
    rod2DrawCheck->setCheckState(Qt::Checked);
    bob1DrawCheck = new QCheckBox("Draw bob 1", this);
    bob1DrawCheck->setCheckState(Qt::Checked);
    bob2DrawCheck = new QCheckBox("Draw bob 2", this);
    bob2DrawCheck->setCheckState(Qt::Checked);
    bob1TraceCheck = new QCheckBox("Trace bob 1", this);
    // bob1TraceCheck->setCheckState(Qt::Checked);
    bob2TraceCheck = new QCheckBox("Trace bob 2", this);
    // bob2TraceCheck->setCheckState(Qt::Checked);

    checkBoxLayout->addWidget(rod1DrawCheck);
    checkBoxLayout->addWidget(rod2DrawCheck);
    checkBoxLayout->addWidget(bob1DrawCheck);
    checkBoxLayout->addWidget(bob2DrawCheck);
    checkBoxLayout->addWidget(bob1TraceCheck);
    checkBoxLayout->addWidget(bob2TraceCheck);
}
