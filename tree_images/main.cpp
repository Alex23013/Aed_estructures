#include <QApplication>
#include"tree.h"
#include"mylista_click.h"
#include <QDir>
#include <QDebug>
#include<QFile>
#include <QListWidget>
#include <QLabel>


#include<iostream>
using namespace std;

int main(int argc,char ** argv)
{
    cout<<"    ARBOLES RED_BLACK   "<<endl;
    QDir dir1("/home/dell/Imágenes/a");
    qDebug() << dir1.exists() << dir1.count();
    QStringList filters,images;
    QFileInfoList dir_images_ordered,images_ordered;
    filters << "*.jpeg";
    dir1.setNameFilters(filters);
    qDebug() << dir1.exists() << dir1.count();

    images<<dir1.entryList();
    dir_images_ordered<<dir1.entryInfoList();

    /*for(int i=0;i<images.size();i++){
            //qDebug()<<(dir_images_ordered[i]).absoluteFilePath();
            qDebug()<<(dir_images_ordered[i]).baseName();
    }*/

    Arbol_R_B<QFileInfo,QString> tree_images;
    for(int i=0;i<images.size();i++){
            tree_images.insertar(dir_images_ordered[i]);
    }

    tree_images.print_arbol(images_ordered);

    for(int i=0;i<images_ordered.size();i++){
                qDebug()<<(images_ordered[i]).baseName();
        }

    QApplication app(argc,argv);

     myLista_click * lista=new myLista_click;
     for(int i=0;i<images_ordered.size();i++){

                  lista->addItem( new QListWidgetItem((images_ordered[i]).absoluteFilePath()));
                  lista->item(i)->setForeground(*(new QBrush(Qt::blue)));
         }

     lista->setWindowTitle("Mis Imagenes xD");
     lista->show();


     return app.exec();

}
