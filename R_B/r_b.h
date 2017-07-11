#ifndef R_B_H
#define R_B_H

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename T>
class nodo{
public:
T info;
bool color;//0: rojo 1: negro
nodo<T>* hijos[2];

nodo(T info){
    this->info=info;
    this ->color=0;//todo nodo que se ingresa es rojo
    hijos[0] =NULL;
    hijos[1] =NULL;
    }

};

template<typename T>
class Arbol_R_B{
public:
  nodo<T> *root;

    Arbol_R_B(){root=NULL;}

      bool find(T x,nodo<T>**&p,stack<pair <nodo<T>**,bool> >& camino){
              p=&root;
              camino.push(make_pair(&root,0));//q dir al root?--doesn't matter
              //cout<<"x";
              //cout<<(*p)->info;
              while(*p && (*p)->info != x){
                //  cout<<"p";
                  bool dir=(*p)->info < x;
                  p=&((*p)->hijos[dir]);
                  camino.push(make_pair(p,dir));
                  }
              return *p;
              }

      bool dos_rojos (stack<pair <nodo<T>**,bool> >& camino){
              while(!camino.empty() && camino.size()>=2 ){
              cout<<"\nsize del camino: "<<camino.size()<<endl;
              nodo<T>** hijo=(camino.top()).first;
              cout<<"hijo: "<<(*hijo)->info;
              bool dir_hijo =(camino.top()).second;
              camino.pop();
              nodo<T>** padre=(camino.top()).first;
              cout<<"padre "<<(*padre)->info;
              bool dir_padre =(camino.top()).second;
              cout<<"\ndir_padre"<<dir_padre<<endl;
              nodo <T>** abuelo;
              if((*padre)->color == 0 && (*hijo)->color == 0){
                  cout<<"dos rojos detected \t";
                  camino.pop();
                  abuelo =(camino.top()).first;
                  cout<<"abu: "<<(*abuelo)->info<<"c: "<<(*abuelo)->color;
                  if((*abuelo)->hijos[!dir_padre] == 0 || ((*abuelo)->hijos[!dir_padre])->color == 1){
                      cout<<"\nrotacion ";
                      //cout<<"c-padre"<<(*padre)->color<<" c-abuelo"<<(*abuelo)->color;
                      //(*padre)->color=1-((*padre)->color);
                      //(*abuelo)->color=1-((*abuelo)->color);
                      //cout<<"\nAfter change\nc-padre"<<(*padre)->color<<" c-abuelo"<<(*abuelo)->color;
                      if(dir_padre != dir_hijo){//RL v LR
                          cout<<"\nRL v LR\n";
                          nodo<T>* w=(*padre);
                          (*padre)=(*padre)->hijos[dir_hijo];
                          w->hijos[dir_hijo]=(*padre)->hijos[!dir_hijo];
                          (*padre)->hijos[!dir_hijo]=w;
                          }
                      //RR v LL
                      cout<<"\nRR v LL\n";
                      nodo<T>* w=(*abuelo);
                      (*abuelo)=(*padre);
                      w->hijos[dir_hijo]=(*padre)->hijos[!dir_hijo];
                      (*abuelo)->hijos[!dir_hijo]=w;
                      cout<<"c-padre"<<(*abuelo)->color<<" c-abuelo"<<w->color;
                        w->color=1-(w->color);//abuelo
                        (*abuelo)->color=1-((*abuelo)->color);//padre
                        cout<<"\nAfter change\nc-padre"<<(*abuelo)->color<<" c-abuelo"<<w->color;
                  }else{
                      cout<<"\ncambio de color ";
                        (*abuelo)->color=1-((*abuelo)->color);
                        ((*abuelo)->hijos[1])->color=1-((*abuelo)->hijos[1])->color;
                        ((*abuelo)->hijos[0])->color=1-((*abuelo)->hijos[0])->color;
                  }

                  }
              //return 1;
               cout<<"\nal final size del camino: "<<camino.size()<<endl;
              }
              return 0;
              }

      bool insertar(T x){
        cout<<"\nnodo_in:"<<x<<endl;
        nodo<T>** p;
        stack<pair <nodo<T>**,bool> > camino;
        //nodo<T>* tmp;
        if(find(x,p,camino)){
            return 0;}

        *p=new nodo<T>(x);
        cout<<"\npp: "<<(*p)->info<<"root"<<root->info;
        cout<<"camino guardado:";
        if(dos_rojos(camino)){
            cout<<"balanceo\n";
        }else{
                cout<<"insercion completed\n";
        }

        /*while(!camino.empty()){
        cout<<(*(camino.top().first))->info<<" ->(c "<<(*camino.top().first)->color<<",dir "<<(camino.top()).second<<") ";
        camino.pop();
        }*/
        root->color=1;

        return 1;
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
        stack<pair <nodo<T>**,bool> > camino;
        //nodo<T>* tmp;
        if(!find(x,p,camino)){
            cout<<"no esta el nodo a borrar\n";
            return 0;
        }
        if ((*p)->hijos[0] && (*p)->hijos[1])
        {
            q = Intercambio(p);
            (*p)->info = (*q)->info;
            p = q;
        }
        nodo<T>* t = *p;
        if((*p)->hijos[0] || (*p)->hijos[1] ){
            (*p)->hijos[(*p)->hijos[1]!=0]->color = (*p)->color;
        }else{
            /*while(!camino.empty()){
                    cout<<(*(camino.top().first))->info<<" ->(c "<<(*camino.top().first)->color<<",dir "<<(camino.top()).second<<") ";
                    camino.pop();
                    }*/
            }

        *p = (*p)->hijos[(*p)->hijos[1]!=0];

        delete t;

        return 1;
    }

    void amplitud()
    {
    cout<<"\nRecorrdio en amplitud\n";
    queue <nodo<T>*> cola;
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

    void print_arbol(){
        if(root == NULL)
            {cout<<"\nEl arbol esta vacio"<<endl;}
        else{
            cout<<"\nEl arbol impreso  inorden es: "<<endl;
            cout<<"\nroot"<<root->info<<endl;
            print_inorden(root);
        }
    }


    void print_inorden(nodo<T>* yop){
        //cout<<"q: "<<yop->info;
        if(!yop){return;}
            print_inorden(yop->hijos[0]);
            cout<<yop->info<<"("<<yop->color<<")- ";
            print_inorden(yop->hijos[1]);
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

};

#endif // R_B_H
