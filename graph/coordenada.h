#ifndef COORDENADA_H
#define COORDENADA_H
#include<iostream>
#include<utility>
#include<math.h>
using namespace std;
class coordenada{
    pair<double,double> my_par;

    coordenada(double a, double b){
        this->my_par.first=a;
        this->my_par.second=b;
    }

    double distancia(pair otro){
        return sqrt(pow(otro.first-my_par.first,2)+pow(otro.second-my_par.second,2));
    }
};
#endif // COORDENADA_H
