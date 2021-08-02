#include "mainwidget.h"

#include "PWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWidget::MainWidget(QWidget* parent) : QWidget(parent) {
    auto* pWidget = new PendulumWidget(this);

    l1Slider = new QSlider(Qt::Horizontal, this);
    auto* l1Label = new QLabel("Lenght 1", this);
    auto* l1Layout = new QVBoxLayout;
    l1Layout->addWidget(l1Label);
    l1Layout->addWidget(l1Slider);
    l1Slider->setValue(7);
    l1Slider->setMinimum(1);
    l1Slider->setMaximum(10);


    auto* mainLayout = new QHBoxLayout(this);
    auto* sliderLayout = new QVBoxLayout;

    sliderLayout->addLayout(l1Layout);

    mainLayout->addLayout(sliderLayout);
    mainLayout->addWidget(pWidget);
}