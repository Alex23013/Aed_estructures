#include "qt/mwindow.h"
#include <QApplication>

CityGraph::Node* FINAL;
CityGraph::Node* ACTUAL;

int main(int argc, char *argv[]) {

    /*QApplication a(argc, argv);
    MyMainWindow window;
    window.resize(400,350);
    window.decorate();

    return a.exec();*/

    QApplication app(argc, argv);
    MWindow *mWindow = new MWindow();
    mWindow->show();
    return app.exec();
}
