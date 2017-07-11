#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename T>
class nodo{
public:
T info;
int altura;
nodo<T>* hijos[2];

nodo(T info){
    this->info=info;
    altura=1;
    hijos[0] =NULL;
    hijos[1] =NULL;
    }

};

template<typename T>
class Arbol_AVL{
public:
  nodo<T> *root;

    Arbol_AVL(){root=NULL;}

      bool find(T x,nodo<T>**&p,stack<pair <nodo<T>**,bool> > & camino){
              p=&root;
              camino.push(make_pair(&root,0));//q dir al root?--doesn't matter
              //cout<<"x";
              while(*p && (*p)->info != x){
                  //cout<<"p";
                  bool dir=(*p)->info < x;
                  p=&((*p)->hijos[dir]);
                  camino.push(make_pair(p,dir));
                  }
              return *p;
              }

      int Alturas(nodo<T>* yop){
          if(yop->hijos[0] && yop->hijos[1])
            {return yop->hijos[0]->altura - yop->hijos[1]->altura;}
          return yop->hijos[yop->hijos[1] != nullptr]->altura;
      }


       void balanceo(stack<pair <nodo<T>**,bool> >& camino){
           pair <nodo<T>**,bool> hijo, padre;
               int diferencia;
               while(camino.size() > 1){
               padre = camino.top();
               camino.pop();

               diferencia = Alturas(*camino.top().first);
               if(diferencia == 0) return;

               if(diferencia == 1 or diferencia == -1){
                   if((*padre.first)->altura + 1 > (*camino.top().first)->altura)
                   (*camino.top().first)->altura++;
                   hijo = padre;
               }
               else if(diferencia == 2 or diferencia == -2){
                   if(hijo.second != padre.second){
                       cout<<"\nRL v LR\n";
                       bool dir_padre=padre.second;
                       nodo<T>* w=(*padre.first);
                       (*padre.first)=(*padre.first)->hijos[!dir_padre];
                       w->hijos[!dir_padre]=(*padre.first)->hijos[dir_padre];
                       (*padre.first)->hijos[dir_padre]=w;
                        swap(w->altura,(*padre.first)->altura);
                       //hijo = padre;
                   }
                       cout<<"\nRR v LL\n";
                       nodo<T>** abuelo=(camino.top()).first;
                       bool dir_padre=padre.second;
                       (*abuelo)->altura--;
                       nodo<T>* w=(*abuelo);
                       (*abuelo)=(*(padre.first));
                       w->hijos[dir_padre]=(*(padre.first))->hijos[!dir_padre];
                       (*abuelo)->hijos[!dir_padre]=w;

                }
               }
       }

      bool insertar(T x){
        cout<<"nodo_in:"<<x<<endl;
        nodo<T>** p;
        stack<pair <nodo<T>**,bool> > camino;
        if(find(x,p,camino)){
            return 0;}
        *p=new nodo<T>(x);
        //cout<<"camino guardado:\t";
        //cout<<" camino_size "<<camino.size()<<endl;
        
        if(camino.size() > 1){
            balanceo(camino);
        }
        
        return 1;
        }


      void printBonito(){
          vector <nodo<T>* > c;
          c.push_back(root);
          int len;
          while(c.size()!=0){
              len=c.size();
              for(int i=0;i<len;i++){
              if(c[i]){
              cout<<c[i]->info<<" ";
              c.push_back(c[i]->hijos[0]);
              c.push_back(c[i]->hijos[1]);
              }
              else
              cout << "- ";

              }
              cout<<endl;
              c.erase(c.begin(),c.begin()+len);
          }
      }

    nodo<T>** Intercambio(nodo<T>** q ){
        q = &(*q)->hijos[0];
        while ((*q)->hijos[1])
        {
            q = &((*q)->hijos[1]);
        }
        return q;
    }

     bool Remover(T x){
        nodo<T>**p, **q;
        if (!find(x, p))
        {
            return 0;
        }
        if ((*p)->hijos[0] && (*p)->hijos[1])
        {
            q = Intercambio(p);
            (*p)->info = (*q)->info;
            p = q;
        }
        nodo<T>* t = *p;
        *p = (*p)->hijos[(*p)->hijos[1]!=0];
        delete t;
        return 1;
    }

    void print_arbol(){
        if(root == NULL)
            {cout<<"\nEl arbol esta vacio"<<endl;}
        else{
            cout<<"El arbol impreso  inorden es:\t \n";
            cout<<"root: "<<root->info<<endl;
            print_inorden(root);
        }
    }


    void print_inorden(nodo<T>* yop){
        //cout<<"q: "<<yop->info;
        if(!yop){return;}
            print_inorden(yop->hijos[0]);
            cout<<yop->info<<"-h: "<<yop->altura<<"-> ";
            print_inorden(yop->hijos[1]);
     }

};


#endif // AVL_H
