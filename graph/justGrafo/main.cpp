#include <QCoreApplication>
#include "graph.h"
int main()
{
    c_graph<char,int> Centaury;

        Centaury.insert_node('a');
        Centaury.insert_node('b');
        Centaury.insert_node('c');
        Centaury.insert_node('d');
        Centaury.insert_node('e');
        Centaury.insert_node('f');
    Centaury.recorrer_grafo();
        Centaury.insert_edge(7,'a','b',0);
        Centaury.insert_edge(6,'a','c',0);
        Centaury.insert_edge(5,'a','d',0);
        Centaury.insert_edge(2,'b','c',0);
        Centaury.insert_edge(5,'d','c',0);
        Centaury.insert_edge(3,'b','e',0);
        Centaury.insert_edge(4,'c','e',0);
        Centaury.insert_edge(2,'d','f',0);
        Centaury.insert_edge(10,'e','f',0);
    Centaury.recorrer_grafo();
    /*vector<char> a=Centaury.m_nodes[0]->mis_vecinos();
    for(int i =0;i<a.size();i++){
        cout<<a[i]<<" - ";
    }*/

//cout<<Centaury.distancia_a_b(Centaury.m_nodes[0],Centaury.m_nodes[1]);
    cout<<"\nDIJKSTRA\n";
    Centaury.dijkstra(0);
    cout<<"\nfinite\n";
        return 0;
}

//   Centaury.remove_edge('a',1,2);
//   Centaury.recorrer_grafo();
//   Centaury.remove_node(1);
//   Centaury.recorrer_grafo();
