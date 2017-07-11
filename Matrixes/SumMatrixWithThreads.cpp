#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <vector>
#include<chrono>
#include<mutex>

//g++ main.cpp -o as -std=c++11 -pthread //para compilar

//top -i para ver los procesos


using namespace std;
using namespace chrono;

mutex cc;
bool arbitroo;
void sumador(int** A,long long* sumador,int filas_ini,int filas_fin ,int columnas_ini,int columnas_fin){
cc.lock();	
//arbitroo=true;
	long tmp=0;	
	for(int i =filas_ini;i<filas_fin;i++){
		for(int j=columnas_ini;j<columnas_fin;j++){
			//cout<<*sumador<<" . ";
			tmp=tmp+*(*(A+i)+j);
           		}
	}

	*sumador=tmp;
cc.unlock();
//arbitroo=false;
}

void print_matriz(int** pm,int filas, int columnas){
	for(int i =0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cout<<*(*(pm+i)+j)<<" ";
		}
		cout<<endl;
	}

}


int main(){
	srand((unsigned)time(NULL));
	cout<<"\nMatriz A \n";
	int **pm;
	int tamano=22000;
	int filas=tamano;
	int columnas=tamano;
	pm = new int* [filas];
	for (int i = 0; i < filas; i++) {
		pm[i] = new int[columnas];
	}
	for(int i =0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			*(*(pm+i)+j)=rand()%10;
		}
	}
	//print_matriz( pm,filas, columnas);

    int cores=thread:: hardware_concurrency();
	cout <<"\n# de cores: "<<cores;
    long long suma[cores];
    long long suma_total=0;
    int division=columnas/cores;
    for(int i=0;i<cores;i++){
        suma[i]=0;
    }

    ///TIME///
    auto t1=high_resolution_clock::now();
    auto t2=high_resolution_clock::now();
    duration< double,std:: milli> out;
    t1=high_resolution_clock::now();
    ///TIME///

    vector <thread> ths(cores);
    for(int i=0;i<cores;i++){
        ths[i]=thread(sumador,pm,&suma_total,0,filas,i*division,(i+1)*division);
    }
    for(int i=0;i<cores;i++){
        ths[i].join();
    }
    for(int i=0;i<cores;i++){
        suma_total+=suma[i];
    }

    ///TIME///
    t2=high_resolution_clock::now();
    out=t2-t1;
    cout<<"\ncompleted in -> "<<out.count()<<" milliseconds";
    ///TIME///
    cout<<"\nsuma_ttal:\t"<<suma_total<<endl;

/*
///TIME///
    auto t1=high_resolution_clock::now();
    auto t2=high_resolution_clock::now();
    duration< double,std:: milli> out;
    t1=high_resolution_clock::now();
    ///TIME///

    long long suma_total=0;
    sumador(pm,&suma_total,0,filas,0,columnas);
    cout<<"\nsuma_ttal:\t"<<suma_total<<endl;

    ///TIME///
    t2=high_resolution_clock::now();
    out=t2-t1;
    cout<<"\ncompleted in -> "<<out.count()<<" milliseconds";
    ///TIME///
*/
}
