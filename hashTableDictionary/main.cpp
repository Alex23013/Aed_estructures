#include <QCoreApplication>
#include "chashtable.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "functors.h"

using namespace std;
using namespace std::chrono;

string english[25] = {"the","enought","night","yesterday","tomorrow",
                      "car","bicycle","notebook","ship","train",
                      "mum","dad","brother","sister","is",
                      "red","blue","yellow","grey","black",
                      "play","jump","read","eat","sleep"};
string spanish[25] = {"el","suficiente","noche","ayer","mañana",
                      "carro","bicicleta","cuaderno","barco","tren",
                      "mamá","papá","hermano","hermana","es",
                      "rojo","azul","amarillo","gris","negro",
                      "juega","salta","lee","come","duerme"};



int main()
{
    cout<<" --- TABLAS HASH aplicadas en un DICCIONARIO ---\n";

    ChashTable<string,cFxA<string>,26> my_hash;
    //ChashTable<string,cFxB<string>,500> my_hash;

    //my_hash.print_table();//cuando la tabla esta vacia
    int opt= 9;
    int tamVocabulario = 25;
    while(opt != 0 ){
        cout<<"Bienvenido ...\n Escoja una opcion: \n 1: Español -> Ingles \n 2: Ingles -> Español \n 3: tomar tiempos \n 0: Salir\n";
        cin>>opt;
        if (opt == 1){
            for(int i = 0 ;i < tamVocabulario ;i++){
                my_hash.insert(spanish[i], english[i]);
            }
        }
        else if(opt == 2){
            for(int i = 0 ;i < tamVocabulario ;i++){
                my_hash.insert(english[i], spanish[i]);
            }
        }

        if (opt == 1 || opt == 2){
            int optSubMain = 9;
            while(optSubMain != 7  && optSubMain != 0 && opt !=0){
                cout<<"\nDesea...\n 1: Traducir\n 2: agregar una nueva palabra\n 0: cambiar de diccionario\n";
                cin>>optSubMain;
                if (optSubMain == 1){
                    cout<<"Vocabulary\n";
                    my_hash.print_table();

                    int tamBuffer = 40;
                    string h;
                    cin.ignore();
                    cin.clear();
                    cout<<"tipee la frase a traducir:\n";
                    getline(cin,h);
                    //cout<<"+"<<h<<"+\n";
                    string palabras[15];
                    int i=0;
                    int pal =0;
                    while(i<tamBuffer  ){
                        string tmp="";

                        while (h[i] != ' ' && h[i] != '\0' ){
                           // cout<<"("<<h[i]<<")";
                            tmp+=h[i];
                            i++;
                        }

                        if(h[i]=='\0'){i = 1000;}
                        i++;
                        palabras[pal]=tmp;
                        pal++;
                    }
                    //for(int i = 0;i < pal;i++){cout<<"["<<palabras[i]<<"]";}
                    cout<<"TRADUCCION:";
                    for(int i = 0;i < pal;i++){
                      cout<<my_hash.traducir(palabras[i])<<" ";
                    }
                }
                else if (optSubMain == 2){
                    cout<<"Ingrese la tupla nueva \n";
                    cout<<"clave : ";
                    string key;
                    cin>>key;
                    cout<<"traduccion: ";
                    string translate;
                    cin>>translate;
                    my_hash.insert(key,translate);
                    my_hash.print_table();
                }
                else if(optSubMain == 0){
                    cout<<"fin de consulta\n";
                }
                else {
                    cout<<"{"<<optSubMain<<"}";
                    cout<<"opcion no valida";
                }
            }
             my_hash.clearTable();}
       if (opt == 3){
           cout<<"tiempos...\n";
           int elementos[4] = {100,3000,5000,7000};
           int tests = 100;
           int tamVocabulario = 25;
           int n;
           ChashTable<string,cFxA<string>,26> my_hash;
           //ChashTable<string,cFxB<string>,111> my_hash;
           for(int i = 0 ;i < tamVocabulario ;i++){
               my_hash.insert(english[i], spanish[i]);
           }
           srand(time(NULL));
           for(int i = 0; i < 4; i++){
               n = elementos[i];
               double time = 0;
               for (int i = 0; i < tests ; i++) {
                   high_resolution_clock::time_point t1 = high_resolution_clock::now();
                   for (int j = 0; j < n ; j++) {
                    int o = rand() % tamVocabulario;
                       my_hash.traducir(english[o]);
                   }
                   high_resolution_clock::time_point t2 = high_resolution_clock::now();
                   auto res = duration_cast<microseconds>( t2 - t1 ).count();
                   time += res;

               }

               long long  ttime = time/tests;
               cout << "tiempo busqueda promedio:" << ttime/1000.0<< " milliseconds con " <<elementos[i]<< endl ;
           }
       }
    }

}
