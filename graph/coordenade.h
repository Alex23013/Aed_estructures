#ifndef COORDENADE_H
#define COORDENADE_H
#include<iostream>
#include<utility>
#include<math.h>
using namespace std;
template <typename T>
class coordenada{
public:
    pair<T,T> my_par;

    coordenada(T a,T b){
        this->my_par.first=a;
        this->my_par.second=b;
    }

    double distancia(coordenada<T> otro){
        return sqrt(pow(otro.my_par.first-my_par.first,2)+pow(otro.my_par.second-my_par.second,2));
    }
};
#endif // COORDENADE_H
