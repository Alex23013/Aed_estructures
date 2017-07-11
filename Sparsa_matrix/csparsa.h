#ifndef CSPARSA_H
#define CSPARSA_H
#include "nodos.h"
template <class T,int filas, int columnas,T nulo_char >
class Csparsa{
public:

    typedef Csparsa<T,filas,columnas,nulo_char> self;
    typedef T  Tt;

    T var_nul =nulo_char;

    nodo_smx<T>* x_[filas];
    nodo_smx<T>* y_[columnas];

    Csparsa(){
        for(int i=0;i<filas;i++){
            x_[i]=0;
        }
        for(int i=0;i<columnas;i++){
            y_[i]=0;
        }
    }


    bool insertar( int i, int j,T dato);
    bool eliminar(int i, int j);
    void debug_fila(nodo_smx<T> * cent);
    bool find_x(int i,int j,nodo_smx<T> ** &p);
    bool find_y(int i,int j,nodo_smx<T> ** &p);
    void print_matrix_x();
    void print_matrix_y();
    //T operator()(int i, int j);
    nodo_temp<self> operator()(int i, int j);
    /*nodo_smx<T>& operator()(int i, int j){
       return insertar(i,j,0);
    }*/

};



template <class T, int filas, int columnas ,T nulo_char>
inline bool Csparsa<T,filas ,columnas,nulo_char > ::insertar(int i, int j,T dato) { // Probar enviar en ptr al pseudonodo
    nodo_smx<T> **ptr;
    //cout<<"dato in:"<<dato<<endl;
    if(i >= 0 && i< filas && j>=0 && j<columnas){
        if(find_x(i,j,ptr)) { //si lo encuentra, ya existe, entonces cambio su valor
            if(dato == nulo_char){
                eliminar(i,j);
            }else{
                (*ptr)->m_data = dato;
                return 1;
            }

            return 0;
        }
        else {
            nodo_smx<T> *tmp = new nodo_smx<T>(dato,i,j);
            tmp->down = *ptr;
            *ptr = tmp;

            find_y(i,j,ptr);
            tmp->next = *ptr;
            *ptr = tmp;

            return 1;
        }
    }else{
        cout<<"\nout of range\n";

       return 0;
    }

    }

template <class T, int filas, int columnas ,T nulo_char>
inline bool Csparsa<T,filas ,columnas,nulo_char > ::eliminar(int i, int j){
    nodo_smx<T> **ptrY;
    nodo_smx<T> **ptrX;
    if(!find_y(i,j,ptrY))
        {return 0;}

    find_x(i,j,ptrX);
    nodo_smx<T> *tmpY = (*ptrY)->down;
    nodo_smx<T> *tmpX = (*ptrX)->next;
    delete *ptrY;
    *ptrY = tmpY;
    *ptrX = tmpX;
    //cout<<"s";
    return true;
}

template <class T, int filas, int columnas ,T nulo_char>
inline void Csparsa<T,filas ,columnas,nulo_char > ::debug_fila(nodo_smx<T> * cent){
    while(cent){
        cout<<cent->m_data;
        cout<<"-> ";
            cent =cent->next;
            }
}

template <class T, int filas, int columnas,T nulo_char >
inline bool Csparsa<T, filas ,columnas , nulo_char> ::find_x(int i,int j,nodo_smx<T> ** &p){
        p=&(x_[i]);
        while(*p && (*p)->y_data<j ){
            p=&((*p)->next);
        }
        return *p && (*p)->y_data == j ;
}

template <class T, int filas, int columnas,T nulo_char >
inline bool Csparsa<T, filas ,columnas , nulo_char> ::find_y(int i,int j,nodo_smx<T> ** &p){
        p=&(y_[j]);
        while(*p && (*p)->x_data<i){
            p=&((*p)->down);
        }
        return *p && (*p)->x_data == i ;
}

template <class T, int filas, int columnas ,T nulo_char>
inline void Csparsa<T, filas ,columnas,nulo_char > :: print_matrix_x(){
    cout<<"\n";
    for(int i =0;i < filas;i++){
        cout<<"\t";
        //cout<<i;
        //debug_fila(x_[i]);
        int cont =0;
        nodo_smx<T>* q=x_[i];
        while(q){
            while(q->y_data>cont){
                cout<<nulo_char<<" ";
                cont++;
            }
            cout<<q->m_data<<" ";
            q=q->next;
            cont++;
        }
        while(columnas-cont>0){
            cout<<nulo_char<<" ";
            cont++;
        }
        cout<<"\n";
    }
    cout<<"\n";
}

template <class T, int filas, int columnas ,T nulo_char>
inline void Csparsa<T, filas ,columnas,nulo_char > :: print_matrix_y(){
    for(int i =0;i < columnas;i++){
        int cont =0;
        nodo_smx<T>* q=y_[i];
        while(q ){
            while(q->x_data>cont){
                cout<<nulo_char<<" ";
                cont++;
            }
            cout<<q->m_data<<" ";
            q=q->down;
            cont++;
        }
        while(filas-cont>0){
            cout<<nulo_char<<" ";
            cont++;
        }
        cout<<"\n";
    }
}


template <class T, int filas, int columnas ,T nulo_char>
nodo_temp<Csparsa<T, filas ,columnas,nulo_char >> Csparsa<T, filas ,columnas,nulo_char > :: operator()(int i, int j){
    nodo_smx<T>** p;
    T f;
    if(find_x(i,j,p)){
        f=(*p)->m_data;
    }else{
        f=nulo_char;
    }
    return nodo_temp<self> (f,i,j,this);
}



#endif // CSPARSA_H
