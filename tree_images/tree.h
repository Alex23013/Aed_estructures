#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <queue>
#include<QDebug>
#include<QFileInfo>
#include<QFileInfoList>
using namespace std;

template<typename T,typename XX>
class nodo{
public:
T info;
XX nombre;
bool color;//0: rojo 1: negro
nodo<T,XX>* hijos[2];

nodo(T info){
    this->nombre=info.baseName();
    this->info=info;
    this ->color=0;//todo nodo que se ingresa es rojo
    hijos[0] =NULL;
    hijos[1] =NULL;
    }

};

template<typename T, typename XX>
class Arbol_R_B{
public:
  nodo<T,XX> *root;

    Arbol_R_B(){root=NULL;}

      bool find(XX x,nodo<T,XX>**&p,stack<pair <nodo<T,XX>**,bool> >& camino){
              p=&root;
              camino.push(make_pair(&root,0));//q dir al root?--doesn't matter
              //cout<<"x";
              //cout<<(*p)->info;
              while(*p && (*p)->nombre != x){
                 // cout<<"p";
                  bool dir=(*p)->nombre < x;
                  p=&((*p)->hijos[dir]);
                  camino.push(make_pair(p,dir));
                  }
              return *p;
              }

      bool dos_rojos (stack<pair <nodo<T,XX>**,bool> >& camino){
              while(!camino.empty() && camino.size()>=2 ){
               //   cout<<"\nsize del camino: "<<camino.size()<<endl;
              nodo<T,XX>** hijo=(camino.top()).first;
              //cout<<"hijo: "<<(*hijo)->info;
              bool dir_hijo =(camino.top()).second;
              camino.pop();
              nodo<T,XX>** padre=(camino.top()).first;
              //cout<<"padre "<<(*padre)->info;
              bool dir_padre =(camino.top()).second;
              //cout<<"\ndir_padre"<<dir_padre<<endl;
              nodo <T,XX>** abuelo;
              if((*padre)->color == 0 && (*hijo)->color == 0){
                  //cout<<"dos rojos detected \t";
                  camino.pop();
                  abuelo =(camino.top()).first;
              //    cout<<"abu: "<<(*abuelo)->info<<"c: "<<(*abuelo)->color;
                  if((*abuelo)->hijos[!dir_padre] == 0 || ((*abuelo)->hijos[!dir_padre])->color == 1){
                      //cout<<"\nrotacion ";//antes aqi el cambio de color
                      if(dir_padre != dir_hijo){//RL v LR
                          //cout<<"\nRL v LR\n";
                          nodo<T, XX>* w=(*padre);
                          (*padre)=(*padre)->hijos[dir_hijo];
                          w->hijos[dir_hijo]=(*padre)->hijos[!dir_hijo];
                          (*padre)->hijos[!dir_hijo]=w;
                          }
                      //RR v LL
                    //  cout<<"\nRR v LL\n";
                      nodo<T,XX>* w=(*abuelo);
                      (*abuelo)=(*padre);
                      w->hijos[dir_hijo]=(*padre)->hijos[!dir_hijo];
                      (*abuelo)->hijos[!dir_hijo]=w;

                      //cout<<"c-padre"<<(*abuelo)->color<<" c-abuelo"<<w->color;
                        w->color=1-(w->color);//abuelo
                        (*abuelo)->color=1-((*abuelo)->color);//padre
                      //  cout<<"\nAfter change\nc-padre"<<(*abuelo)->color<<" c-abuelo"<<w->color;
                  }else{
                     // cout<<"\ncambio de color ";
                        (*abuelo)->color=1-((*abuelo)->color);
                        ((*abuelo)->hijos[1])->color=1-((*abuelo)->hijos[1])->color;
                        ((*abuelo)->hijos[0])->color=1-((*abuelo)->hijos[0])->color;
                  }

                  }

              // cout<<"\nal final size del camino: "<<camino.size()<<endl;
              }
              return 0;
              }

      bool insertar(T x){
        //cout<<"\nnodo_in:"<<x<<endl;
          nodo<T,XX>** p;
        stack<pair <nodo<T,XX>**,bool> > camino;


        if(find(x.baseName() ,p,camino)){
            return 0;}

        *p=new nodo<T,XX>(x);
        //cout<<"\npp: "<<(*p)->info<<"root"<<root->info;
        //cout<<"camino guardado:";
        if(dos_rojos(camino)){
            //cout<<"balanceo\n";
        }else{
               // cout<<"insercion completed\n";
        }

        /*while(!camino.empty()){
        cout<<(*(camino.top().first))->info<<" ->(c "<<(*camino.top().first)->color<<",dir "<<(camino.top()).second<<") ";
        camino.pop();
        }*/
        root->color=1;

        return 1;
        }



    nodo<T,XX>** Intercambio(nodo<T,XX>** q ){
        q = &(*q)->hijos[0];
        while ((*q)->hijos[1])
        {
            q = &((*q)->hijos[1]);
        }
        return q;
    }

     bool Remover(T x){
        nodo<T,XX>**p, **q;
        if (!find(x.nombre, p))
        {
            return 0;
        }
        if ((*p)->hijos[0] && (*p)->hijos[1])
        {
            q = Intercambio(p);
            (*p)->info = (*q)->info;
            p = q;
        }
        nodo<T,XX>* t = *p;
        *p = (*p)->hijos[(*p)->hijos[1]!=0];
        delete t;
        return 1;
    }

    void amplitud()
    {
    //cout<<"\nRecorrdio en amplitud\n";
    queue <nodo<T,XX>*> cola;
    cola.push(root);
    while(!cola.empty()){
        if(cola.front()){
            cout<<cola.front()->info<<"("<<cola.front()->color<<") - ";
            cola.push(cola.front()->hijos[1]);
            cola.push(cola.front()->hijos[0]);
            }
            cola.pop();
        }
    }

    void print_arbol(QFileInfoList & lista){
        if(root == NULL)
            {cout<<"\nEl arbol esta vacio"<<endl;}
        else{
            cout<<"\nEl arbol impreso  inorden es: "<<endl;
            //cout<<"\nroot"<<root->info<<endl;
            print_inorden(root,lista);
        }
    }


    void print_inorden(nodo<T,XX>* yop, QFileInfoList & lista){
        //cout<<"q: "<<yop->info;
        if(!yop){return;}
            print_inorden(yop->hijos[0],lista);
            //cout<<yop->info<<"("<<yop->color<<")- ";
           // qDebug()<<yop->info<<"("<<yop->color<<")- ";
            lista.append(yop->info);
            print_inorden(yop->hijos[1],lista);
     }

};
#endif // TREE_H
