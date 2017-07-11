#ifndef MYLISTA_CLICK_H
#define MYLISTA_CLICK_H
#include <QListWidget>
#include<qmessagebox.h>
#include<QLabel>


class myLista_click : public QListWidget
{
    Q_OBJECT
    public:
    QImage myImage;
    QString av ;
    QLabel myLabel;

        myLista_click():QListWidget()
        {

          connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
        };


    private slots:

        void itemClicked(QListWidgetItem* item)
        {
          QMessageBox::information(this,"Q hiciste? ","Seleccionaste \""+item->text()+"\"");
          av=item->text();
          myImage.load(av);
          myLabel.setPixmap(QPixmap::fromImage(myImage));
          myLabel.show();

        };
};

#endif // MYLISTA_CLICK_H


/*QListWidget * list = new QListWidget();
for(int i=0;i<images_ordered.size();i++){

             list->addItem( new QListWidgetItem(images_ordered[i]));
    }

list->setWindowTitle("Mis Imagenes xD");

list->show();
*/
