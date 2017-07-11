#include <QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include "Cgraph.h"
#include "coordenade.h"
#include"citygraph.h"
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

int main()
{
    /*cout<<"\nGrafos pioneros xD\n";
        cGraph<char,int> my_grafo;
        cNodo<cGraph<char,int> >* a=new cNodo<cGraph<char,int> >('s');// Esto es un puntero a Nodo
        cNodo<cGraph<char,int> > b('s'); //Esto es un nodo
        //my_grafo.insert_nodo(a); //Esto no funcionara :p
        my_grafo.insert_nodo('h'); //Esto si :D
        my_grafo.insert_nodo('t');
        my_grafo.insert_nodo('a');
        my_grafo.recorrer_grafo();
        cNodo<cGraph<char,int> > c('a');
        my_grafo.insert_edge(5,'h','a',0);
        my_grafo.insert_edge(3,'t','a',1);
        my_grafo.insert_edge(32,'h','t',0);
        my_grafo.recorrer_grafo();

        CCityGraph akkk;
        ////////// Tanto al nodo como a la arista debes pasarle todo el tipo de dato cGraph para poder crearlos desde aqui... pero no es necesario crear nodos aqui, porque si te das cuenta, la funcion insert no recibe un nodo sino un Nn que es el tipo de dato del nodo, no el nodo en si :)

    /*
    std::vector<int> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    // sort using the default operator<
    std::sort(s.begin(), s.end());
    for (auto a : s) {
        std::cout << a << " ";
    }*/

    QApplication a(argc, argv);


        CCityGraph Test;

        Test.GeneradorNodos(10000);

        QGraphicsView* view = new QGraphicsView();
        QGraphicsScene* scene = new QGraphicsScene();

        view->setScene(scene);

        for (int i = 0; i < 10000; ++i)
            scene->addEllipse(Test.m_nodes[i]->m_data.x(), Test.m_nodes[i]->m_data.y(), 1, 1);

        view->show();



        return a.exec();

}
