#ifndef MWINDOW_H
#define MWINDOW_H

#include <QWidget>
#include "qt/graphview.h"

class MWindow : public QWidget {
    Q_OBJECT
public:
    GraphView *graphView;

    explicit MWindow(QWidget *parent = 0);

signals:

public slots:
};

#endif // MWINDOW_H
