#include "mwindow.h"

MWindow::MWindow(QWidget *parent) : QWidget(parent) {

    graphView = new GraphView(this);
    graphView->genGraph();
    graphView->printGraph();
}
