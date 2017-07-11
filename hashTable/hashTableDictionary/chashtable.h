#ifndef CHASHTABLE_H
#define CHASHTABLE_H
#include<iostream>
#include "lista.h"
#include "tree.h"
using namespace std;

template< class T,class Fx, int Sz >
class ChashTable{
public:
    lista<string>* m_table[Sz];
    Fx m_f;

    ChashTable(){
        for(int i=0;i<Sz;i++){
            m_table[i]=NULL;
        }
    }
    void clearTable(){
        for(int i=0;i<Sz;i++){
            m_table[i]=NULL;
        }
    }

    void print_table(){
        for(int i=0;i<Sz;i++){
            cout<<endl<<char(i+97)<<":";
            if(m_table [i]== NULL){
                cout<<"--";
            }else{
                m_table[i]->print_();
            }
        }
        cout<<"\n";
    }

    bool insert(T info, T traduccion){
         int pos = m_f(info,Sz);
         if(m_table[pos] == nullptr){
              m_table[pos]=new lista<T>;}
        return m_table[pos]->insertar(info, traduccion);
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

        nodo<string>** p;
        return m_table[pos]->find(info, p);
    }



    string traducir(T info){
        int pos = m_f(info,Sz);
        string no = "#";
        if(m_table[pos] == nullptr){
             return no;}
        nodo<string>** p;
        if(m_table[pos]->find(info,p)){
            //cout<<"(*p)->traduccion "<<(*p)->traduccion<<endl;
            return (*p)->traduccion;
        }
        return no;

    }
};
#endif // CHASHTABLE_H
