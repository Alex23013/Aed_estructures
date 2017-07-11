#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "tre.h"
#include "lista.h"
using namespace std;
using namespace std::chrono;



int main(){

	srand(time(NULL));
	cout<<"Starting ...\n";
    int opt;
    cout<<"Que estructura desea probar?\n1: list   \t2: arbol binario\n\n3: tomar tiempos\n4:exit\n";
    cin>>opt;
    if (opt == 1){
    	lista <int> listaTest;
        listaTest.contenido();
        int n;
        int x,xNuevo;

        cout<<"Cuantos elementos desea insertar? \n";
        cin>>n;

        int insertado;
        for(int i=0;i<n;i++){
            insertado =rand() % 100;
            listaTest.insertarDato(insertado);
        }
        listaTest.contenido();
        cout<<"Que dato desea buscar?\n";
        cin>>x;
        cout<<"El valor ";
        nodoList<int>**p;
        if(listaTest.find(x, p)){cout<< "si ";}else{cout<<"no ";}
        cout<<"esta en la estructura.\n ";
        listaTest.contenido();

        cout<<"Que dato desea reemplazar?\n";
        cin>>x;
        if(listaTest.find(x, p) == false){
                cout<<"no se puede reemplazar porque no se encuentra\n";
        }else{
            cout<<"cual es el reemplazo?\n";
            cin>>xNuevo;
            listaTest.reemplazarUnDato(x,xNuevo,p);
            listaTest.contenido();
        }
        cout<<"Que dato desea borrar?\n";
        cin>>x;
        if(listaTest.find(x, p) == false){
                cout<<"no se puede borrar porque no se encuentra\n";
        }else{
        	listaTest.borrarUnDato(x);
        	listaTest.contenido();}
	}
    if (opt == 2){
        Arbol<int> treeTest;
        treeTest.contenido();
        int n;
        int x,xNuevo;

        cout<<"Cuantos elementos desea insertar? \n";
        cin>>n;

        int insertado;
        for(int i=0;i<n;i++){
            insertado =rand() % 100;
            treeTest.insertarDato(insertado);
        }
        treeTest.contenido();
        cout<<"Que dato desea buscar?\n";
        cin>>x;
        cout<<"El valor ";
        nodo<int>**p;
        if(treeTest.find(x, p)){cout<< "si ";}else{cout<<"no ";}
        cout<<"esta en la estructura.\n ";
        treeTest.contenido();

        cout<<"Que dato desea reemplazar?\n";
        cin>>x;
        if(treeTest.find(x, p) == false){
                cout<<"no se puede reemplazar porque no se encuentra\n";
        }else{
            cout<<"cual es el reemplazo?\n";
            cin>>xNuevo;
            treeTest.reemplazarUnDato(x,xNuevo);
            treeTest.contenido();
        }
        cout<<"Que dato desea borrar?\n";
        cin>>x;
        if(treeTest.find(x, p) == false){
                cout<<"no se puede borrar porque no se encuentra\n";
        }else{
        	treeTest.borrarUnDato(x);
        	treeTest.contenido();}
    	}
    	
    if (opt == 3){
        int n = 10000;
        cout<<"Promedio de los tiempos con "<<n<<" elementos\n";

        //////////////////////

        cout<<"En un arbol\n";
        Arbol<int> treeTest;
       
       	int elementos[4] = {100,3000,5000,7000};
		int tests = 100;
		int insertado;
		for(int i = 0; i < 4; i++){

			n = elementos[i];

			double timeTree = 0;

			for (int i = 0; i < tests ; i++) {

				///////
				high_resolution_clock::time_point arbolt1 = high_resolution_clock::now();
				
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    treeTest.insertarDato(insertado);
				}
				high_resolution_clock::time_point arbolt2 = high_resolution_clock::now();
				auto resarbolInsertion = duration_cast<microseconds>( arbolt2 - arbolt1 ).count();
				
				///////
				timeTree += resarbolInsertion;
			}
			long long ttimeTree = timeTree/tests;
			cout<<"tiempo arbol insercion:"<< ttimeTree/1000.0<< " milliseconds con " <<elementos[i]<< endl ;          
		
       
       		timeTree = 0;
			nodo<int>**p;
			
			for (int i = 0; i < tests ; i++) {
				///////
				high_resolution_clock::time_point arbolst1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
					insertado =rand() % 100;
					treeTest.find(insertado,p);
				}
				high_resolution_clock::time_point arbolst2 = high_resolution_clock::now();
				auto resarbolSearch = duration_cast<microseconds>( arbolst2 - arbolst1 ).count();
				///////
				timeTree += resarbolSearch;
			}

			ttimeTree= timeTree/tests;
			cout << "tiempo arbol busqueda:"<< ttimeTree/1000.0<< " milliseconds con " <<elementos[i]<< endl ;          
			
			timeTree = 0;
			for (int i = 0; i < tests ; i++) {
				///////
				high_resolution_clock::time_point arbolret1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    treeTest.reemplazarUnDato(insertado,insertado+1);
				}
				high_resolution_clock::time_point arbolret2 = high_resolution_clock::now();
				auto resarbolReemplace = duration_cast<microseconds>( arbolret2 - arbolret1 ).count();
				///////
				timeTree += resarbolReemplace;
			}

			ttimeTree = timeTree/tests;
			cout << "tiempo arbol Reemplace:" << ttimeTree/1000.0<< " milliseconds con " <<elementos[i]<< endl ; 
		
			timeTree = 0;
			for (int i = 0; i < tests ; i++) {
				///////
				high_resolution_clock::time_point arbolbt1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    treeTest.borrarUnDato(insertado);
				}
				high_resolution_clock::time_point arbolbt2 = high_resolution_clock::now();
				auto resarbolRemove = duration_cast<microseconds>( arbolbt2 - arbolbt1 ).count();
				///////
				timeTree += resarbolRemove;
			}
			ttimeTree = timeTree/tests;
			cout << "tiempo arbol borrado:" << ttimeTree/1000.0<< " milliseconds con " <<elementos[i]<< endl ; 
			cout<<"\n";
		}
	//////////////////////

        cout<<"En un lista\n";
        lista<int> listaTest;
        
        
		for(int i = 0; i < 4; i++){

			n = elementos[i];
			double time = 0;
			for (int i = 0; i < tests ; i++) {
				///////
				high_resolution_clock::time_point listat1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    listaTest.insertarDato(insertado);
				}
				high_resolution_clock::time_point listat2 = high_resolution_clock::now();
				auto reslistaInsertion = duration_cast<microseconds>( listat2 - listat1 ).count();
				
				///////
				time += reslistaInsertion;
			}

			long long  ttime = time/tests;
			cout << "tiempo lista insercion:" << ttime/1000.0<< " milliseconds con " <<elementos[i]<< endl ;          
			
			nodoList<int>**q;
			time = 0;
			for (int i = 0; i < tests ; i++) {
				///////
				high_resolution_clock::time_point listast1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    listaTest.find(insertado,q);
				}
				high_resolution_clock::time_point listast2 = high_resolution_clock::now();
				auto reslistaSearch = duration_cast<microseconds>( listast2 - listast1 ).count();
				
				///////
				time += reslistaSearch;
			}

			ttime = time/tests;
			cout << "tiempo lista busqueda: " << ttime/1000.0<< " milliseconds con " <<elementos[i]<< endl ; 
		
			nodoList<int>**w;
			time = 0;
			for (int i = 0; i < tests ; i++) {
				///////		
				high_resolution_clock::time_point listaret1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    listaTest.reemplazarUnDato(insertado,insertado+1,w);
				}
				high_resolution_clock::time_point listaret2 = high_resolution_clock::now();
				auto reslistaReemplace = duration_cast<microseconds>( listaret2 - listaret1 ).count();
				///////
				time += reslistaReemplace;
			}

			ttime = time/tests;
			cout << "tiempo lista Reemplace:" << ttime/1000.0<< " milliseconds con " <<elementos[i]<< endl ; 
		
			time = 0;
			for (int i = 0; i < tests ; i++) {
				///////
				high_resolution_clock::time_point listabt1 = high_resolution_clock::now();
				for(int i=0;i<n;i++){
				    insertado =rand() % 100;
				    listaTest.borrarUnDato(insertado);
				}
				high_resolution_clock::time_point listabt2 = high_resolution_clock::now();
				auto reslistaRemove = duration_cast<microseconds>( listabt2 - listabt1 ).count();		
				///////
				time += reslistaRemove;
			}

			ttime = time/tests;
			cout << "tiempo lista borrado:" << ttime/1000.0<< " milliseconds con " <<elementos[i]<< endl ;
			cout<<endl;			
		
		}
	}
}
