#include <QApplication>
#include <pWidget.h>


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    PendulumWidget w;
    w.show();

    return app.exec();

}