#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QtGui>

class myListWidget : public QListWidget{
Q_OBJECT
public:
    myListWidget():QListWidget()
    {

      connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
    };

    ~myListWidget ()
    {};
private slots:

    void itemClicked(QListWidgetItem* item)
    {
      QMessageBox::information(this,"Hello!","You clicked \""+item->text()+"\"");
    };
};
#endif // MYLISTWIDGET_H
