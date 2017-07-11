#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void sumar(int** A,int** B,int filas, int columnas){
	cout<<"\nLa suma es\n";
	for(int i =0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cout<<(*(*(A+i)+j))+(*(*(B+i)+j))<<" ";
		}
		cout<<endl;
	}
}
void restar(int** A,int** B,int filas, int columnas){
	cout<<"\nLa resta es\n";
	for(int i =0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cout<<(*(*(A+i)+j))-(*(*(B+i)+j))<<" ";
		}
		cout<<endl;
	}
}

void mult(int** A,int** B,int**C,int filas_A, int columnas_B, int columnas_A){
	cout<<"\nLa multiplicacion es\n";
	for(int i=0; i<filas_A; i++){
		for(int j=0; j<columnas_B; j++){
		     *(*(C+i)+j)=0;
		    for(int z=0; z<columnas_A; z++){
		        *(*(C+i)+j) += *(*(A+i)+z) * *(*(B+z)+j);
		    }
		}
	}
}

void print_matriz(int** pm,int filas, int columnas){

	for(int i =0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cout<<*(*(pm+i)+j)<<" ";
		}
		cout<<endl;
	}

}

void print_matriz_1(int** pm,int filas, int columnas,int *i){
	
	for(*i=0;*i<filas;(*i)++){
		for(int j=0;j<columnas;j++){
			cout<<*(*(pm+(*i))+j)<<" ";
		}
		cout<<endl;
	}

}



void llenar_matriz(int** pm,int filas, int columnas,int random,int top_random){
	for(int i =0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(random ==1){
				*(*(pm+i)+j)=rand()%(top_random+1);
			}else{
				*(*(pm+i)+j)=top_random;
			}
		}
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



int main(){
	srand((unsigned)time(NULL));
	cout<<"\nCrear una matriz -.-\n";
	int **pm;
	int filas;	
	int columnas;	
	int opcion;
	int opcion2;
	int menu;
	int RoS;
	cout<<"de cuantas filas?: \n";
	cin>>filas;//4
	cout<<"de cuantas columnas?: \n";
	cin>>columnas;//5
	pm = new int* [filas];
	for (int i = 0; i < filas; i++) {
		pm[i] = new int[columnas];
	}
	preguntar(&opcion,&opcion2);
	llenar_matriz(pm,filas,columnas,opcion,opcion2);
	cout<<"\nMatriz A \n";
	int *p;
	int j=0;
	p=&j;
	print_matriz_1( pm,filas, columnas,p);
	cout<<"Que desea hacer ?\n\t0: sumar o restar\n\t1: multiplicar\n";
	cin>>menu;
	if(menu==0){
		///Matriz B
		int **pm2;
		pm2 = new int* [filas];
		for (int i = 0; i < filas; i++) {
			pm2[i] = new int[columnas];
		}
		cout<<"\nLa segunda matriz debe tener las mismas dimensiones para sumar o restar\n";
		cout<<"\tfilas: "<<filas<<"\n\tcolumnas: "<<columnas;
		preguntar(&opcion,&opcion2);
		llenar_matriz(pm2,filas,columnas,opcion,opcion2);
		cout<<"\nMatriz B \n";
		print_matriz( pm2,filas, columnas);
		cout<<"desea:\n\t0: sumar \n\t1:restar\n";
		cin>>RoS;
		if(RoS==0){
			sumar(pm,pm2,filas,columnas);
		}else{
			restar(pm,pm2,filas,columnas);
		}
		
	}else{
		cout<<"\nMatriz C \n";
		int **pm3;
		cout<<"\nLA matriz debe tener filas =columnasA";
	    	int filas_c=columnas;
		int columnas_c;	//6	
		cout<<"\nDe cuantas columnas? ";
		cin>>columnas_c;
		pm3 = new int* [filas_c];
		for (int i = 0; i < filas_c; i++) {
			pm3[i] = new int[columnas_c];
		}
		preguntar(&opcion,&opcion2);
		llenar_matriz(pm3,filas_c,columnas_c,opcion,opcion2);
		print_matriz( pm3,filas_c, columnas_c);

	 	cout<<"\nMatriz D: resultado Multiplicacion \n";
		int **pm4;
	    	int filas_d=columnas;
	    	int columnas_d=columnas_c;
		pm4 = new int* [filas_d];
		for (int i = 0; i < filas_d; i++) {
			pm4[i] = new int[columnas_d];
		}
		mult(pm,pm3,pm4,filas,columnas_c,columnas);
	    	print_matriz(pm4,filas,columnas_d);
	}

    	
}
