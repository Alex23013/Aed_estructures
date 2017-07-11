#include <QCoreApplication>
#include "r_b.h"
#include<iostream>
#include<qstring.h>
using namespace std;



int main(){
    cout<<"    ARBOLES RED_BLACK   "<<endl;
    Arbol_R_B <int>tree;
    tree.insertar(30);
    tree.print_arbol();

    int ar[]={12,8,5,13};//,1,0};//,45,50,11,15,35,17};
    for (int i = 0; i < 6  ; i++) {
        tree.insertar(ar[i]);
       // tree.print_arbol();
        }

   tree.print_arbol();
   tree.printBonito();
   tree.Remover(8);
   tree.print_arbol();
   tree.printBonito();


}
