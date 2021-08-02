#pragma once

#include <QWidget>
#include <QSlider>

class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);

private:
    QSlider* l1Slider;
    
    
};