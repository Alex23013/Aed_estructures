#ifndef NODOS_H
#define NODOS_H
//#include "csparsa.h"

template<typename T>
class nodo_smx{
public:
T m_data;
int x_data,y_data;
nodo_smx<T>* next;
nodo_smx<T>* down;

nodo_smx(T info, int x ,int y){
    this->m_data=info;
    this->x_data=x;
    this->y_data=y;
    next=down=NULL;
    }
};

template<typename M>
class nodo_temp{
public:
    typedef typename M:: Tt T;
    T info;
    int x_,y_;
    M* matrix;

nodo_temp(T info, int x ,int y, M* ma ){
    this->info=info;
    this->x_=x;
    this->y_=y;
    matrix =ma;
    }
 operator T();
 nodo_temp<M>& operator =(T dato){
        cout<<"dato:"<<dato;
        cout<<"\t"<<info<<" ("<<x_<<" , "<<y_<<")"<<endl;
        if(dato == matrix->var_nul){
            matrix->eliminar(x_,y_);
        }else{
            matrix->insertar(x_,y_,dato);
        }
        return *this;
    }

 nodo_temp<M>& operator =(nodo_temp<M> dato){
        cout<<"dato:"<<dato;
        cout<<"\t"<<info<<" ("<<x_<<" , "<<y_<<")"<<endl;
        if(dato == matrix->var_nul){
            matrix->eliminar(x_,y_);
        }else{
            matrix->insertar(x_,y_,dato);
        }
        return *this;
    }
};

template<typename M>
nodo_temp<M>::operator T(){
    return info;
}



#endif // NODOS_H
