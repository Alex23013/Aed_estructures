#ifndef CHASHTABLE_H
#define CHASHTABLE_H
#include<iostream>
#include "lista.h"
#include "tree.h"
using namespace std;

template< class T,class Fx,class Ds, int Sz >
class ChashTable{
public:
    Ds* m_table[Sz];
    Fx m_f;

    ChashTable(){
        for(int i=0;i<Sz;i++){
            m_table[i]=NULL;
        }
    }

    void print_table(){
        for(int i=0;i<Sz;i++){
            cout<<endl<<i<<":";
            if(m_table [i]== NULL){
                cout<<"--";
            }else{
                m_table[i]->imprimir();
            }
        }
        cout<<"\n";
    }

    bool insert(T info){
         int pos = m_f(info,Sz);
         if(m_table[pos] == nullptr){
              m_table[pos]=new Ds;}
        return m_table[pos]->insertar(info);
        }

    bool remove(T info){
        int pos = m_f(info,Sz);
        if(m_table[pos] == nullptr){
             return 0;}
        return m_table[pos]->eliminar(info);
    }

    bool find(T info){
        int pos = m_f(info,Sz);
        if(m_table[pos] == nullptr){
             return 0;}
        return m_table[pos]->buscar(info);
    }
};
#endif // CHASHTABLE_H
