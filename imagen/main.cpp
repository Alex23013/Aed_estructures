#include <QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QWidget>
#include<QMouseEvent>
#include<iostream>
#include"mymainwindow.h"
#include<QMainWindow>
#include<QHBoxLayout>
using namespace std;


CCityGraph::Node* FINAL;
CCityGraph::Node* ACTUAL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow window;
    window.resize(250,200);
    window.decorate();

    return a.exec();

    /*cout<<"\nGrafos pioneros xD\n";
        c_graph<char,int> my_grafo;
        my_grafo.insert_node('h');
        my_grafo.insert_node('t');
        my_grafo.insert_node('a');
        my_grafo.recorrer_grafo();
        my_grafo.insert_edge(5,'h','a',0);
        my_grafo.insert_edge(3,'t','a',1);
        my_grafo.insert_edge(32,'h','t',0);
        my_grafo.recorrer_grafo();
        my_grafo.remove_node('a');
        my_grafo.recorrer_grafo();
*/
}
