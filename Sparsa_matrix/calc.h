#ifndef CALC_H
#define CALC_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "csparsa.h"
using namespace std;


template <class T, int filas, int columnas ,T nulo_char>
void sumar(Csparsa<T,filas,columnas,nulo_char> A,Csparsa<T,filas,columnas,nulo_char> B){
    cout<<"\nLa suma es\n";
    for(int i =0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            cout<<A(i,j)+B(i,j)<<" ";
            //cout<<(*(*(A+i)+j))+(*(*(B+i)+j))<<" ";
        }
        cout<<endl;
    }
}

template <class T, int filas, int columnas ,T nulo_char>
void restar(Csparsa<T,filas,columnas,nulo_char> A,Csparsa<T,filas,columnas,nulo_char>  B){
    cout<<"\nLa resta es\n";
    for(int i =0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            cout<<A(i,j)-B(i,j)<<" ";
            //cout<<(*(*(A+i)+j))-(*(*(B+i)+j))<<" ";
        }
        cout<<endl;
    }
}

template <class T, int filas, int columnas ,T nulo_char>
void mult(Csparsa<T,filas,columnas,nulo_char> A,Csparsa<T,filas,columnas,nulo_char> B,Csparsa<T,filas,columnas,nulo_char> C,int filas_A, int columnas_B, int columnas_A){
    cout<<"\nLa multiplicacion es\n";
    for(int i=0; i<filas_A; i++){
        for(int j=0; j<columnas_B; j++){
            C(i,j)=0;
            // *(*(C+i)+j)=0;
            for(int z=0; z<columnas_A; z++){
                T mul =A(i,z)*B(z,j);
                C(i,j)= mul;
                //*(*(C+i)+j) += *(*(A+i)+z) * *(*(B+z)+j);
            }
        }
    }
}
template <class T, int filas, int columnas ,T nulo_char>
void print_matriz(Csparsa<T,filas,columnas,nulo_char> B, string nombre){
cout<<"Matriz: "<<nombre<<endl;
    for(int i =0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            //cout<<*(*(pm+i)+j)<<" ";
            cout<<B(i,j)<<" ";
        }
        cout<<endl;
    }

}

void preguntar(int*opcion,int*opcion2){
    cout<<"\ndesea poner un numero o un random? 0: numero repetido  1:random \n";
    cin>>*opcion;
    if(*opcion==0){
        cout<<"Que numero?\n";
        cin>>*opcion2;
    }else{
        cout<<"el random ira de 0 a ...?\n";
        cin>>*opcion2;
    }
}

#endif // CALC_H
