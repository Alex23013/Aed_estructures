#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include<QGraphicsScene>
#include<QGraphicsView>
#include<QInputDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include<QDir>
#include "myview.h"


class MyMainWindow: public QWidget
{
  Q_OBJECT

  public:

    MyMainWindow(){
    }
    ~ MyMainWindow(){}

    int nodos_;
    GraphView *graphView;

    void decorate()
    {
       QPalette* blue_palette = new QPalette();
       blue_palette->setColor(QPalette::Button,Qt::blue);
       QPalette* green_palette = new QPalette();
       green_palette->setColor(QPalette::Button,Qt::green);

      QPushButton *Generate_graph_button = new QPushButton(tr("Generate graph"));
      QPushButton *button2 = new QPushButton(tr("View graph"));
      QPushButton *num_nodos_Button = new QPushButton(tr("set num_nodos"));


      Generate_graph_button->setPalette(*blue_palette);
      num_nodos_Button->setPalette(*green_palette);
      button2->setPalette(*green_palette);

    //  Generate_graph_button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //  button2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //  num_nodos_Button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

      QObject::connect(Generate_graph_button, SIGNAL(clicked()),this, SLOT(make_graph()));
      QObject::connect(button2, SIGNAL(clicked()),this, SLOT(view_graph()));
      QObject::connect(num_nodos_Button,SIGNAL(clicked()),this,SLOT(setInteger()));

      QWidget* centralWidget = new QWidget(this);
      QGridLayout *layout = new QGridLayout;
      layout->setColumnStretch(1,1);
      layout->addWidget(Generate_graph_button,0,0);
      layout->addWidget(button2,0,1);
      layout->addWidget(num_nodos_Button,1,0);
      //layout->addWidget(erase_region_Button,1,1);
      centralWidget->setLayout(layout);
      //setCentralWidget(centralWidget);
      setWindowTitle("CityGraph ... ");
      show();
    }


   public slots:

    void setInteger(){
    bool ok;
    int i= QInputDialog::getInt(this,tr("OLa::set_Nodos"),tr("Ingrese cantidad nodos deseados: "),5,1,10000,1,&ok);
    if(ok){
        this->nodos_=i;
        }

    }

    void make_graph(){
        graphView = new GraphView(this);
        graphView->generate_graph(nodos_);
    }
    void view_graph(){
            QWidget *widget = new QWidget;
            graphView->setBackgroundBrush(Qt::white);
            graphView->print_graph();
            QVBoxLayout* vlayout = new QVBoxLayout(widget);
            vlayout->addWidget(graphView);
            widget->show();
     }
};

#endif // MYMAINWINDOW_H
