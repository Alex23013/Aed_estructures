#include <QCoreApplication>
#include "chashtable.h"
#include "functors.h"
#include"adaptor.h"
#include<iostream>
using namespace std;


int main()
{
    cout<<" --- TABLAS HASH ---\n";

    //ChashTable<int,cFxB<int>,lista<int>,11> my_hash;
    ChashTable<int,cFxA<int>,Cadaptor<lista<int>>,7> my_hash;

    //my_hash.print_table();//cuando la tabla esta vacia
    int ejm =14;
    my_hash.insert(ejm);
    srand((unsigned)time(NULL));
    int insertado;
    for(int i=0;i<10;i++){
        insertado =rand() % 100;
        //cout<<insertado<<"-";
        my_hash.insert(insertado);
    }
    //my_hash.print_table();
    //cout<<"se encuentra el "<<ejm <<": "<<my_hash.find(ejm);

    //my_hash.remove(ejm);
    //my_hash.print_table();
    //cout<<"se encuentra el "<<ejm <<": "<<my_hash.find(ejm);

    ChashTable<int,cFxA<int>,Cadaptor<Arbol<int>>,100> my_hashB;

    //srand((unsigned)time(NULL));
    int inserto;
    for(int i=0;i<10;i++){
        //inserto =rand() % 100;
        //cout<<insertado<<"-";
        my_hashB.insert(i);
    }
    cout<<"\n\nde arboles con print inorden";
    my_hashB.print_table();
    my_hashB.remove(1);
    my_hashB.print_table();
}
