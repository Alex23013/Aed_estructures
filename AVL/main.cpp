#include <QCoreApplication>
#include "CTree.h"
#include<iostream>
using namespace std;

int main()
{
    cout<<"Binary tree\n";
    Tree<int> my_tree;
    int ar[]={30,12,15,5,3,50,60,100,45,200,300};

    for (int i = 1; i < 11  ; i++) {
        //my_tree.insertar(ar[i]);
        my_tree.insertar(i);
        }
    my_tree.printBonito();
}
