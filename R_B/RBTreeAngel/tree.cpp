#include <iostream>
#include <cstdlib>
#include <ctime>
#include"tre.h"
using namespace std;




int main(){

	cout<<"Probando si probando \n";
	cout<<"    ARBOLES BINARIOS   "<<endl;
  	Arbol <int>tree;
	tree.insertar(5);
	tree.insertar(2);	
	tree.insertar(18);
	
	tree.insertar(35);
	tree.insertar(17);
tree.insertar(22);	
	tree.insertar(181);
	tree.print_arbol();
	tree.a_lista();
	tree.print_lista();
	/*srand((unsigned)time(NULL));
	int ar[]={2,15,20,25,56,12};
 	for (int i = 0; i < 5; i++) {
		tree.insertar(ar[i]);
        	//tree.insertar( rand() % 100);
		//tree.insertar(i);
    	}
	//tree.print_arbol();
	//tree.Remover(10);
	//tree.print_arbol();

	
	cout<<"\n -- IMPRESIONES --\n";
	cout<<"\nEl arbol impreso  inorden es: "<<endl;
	tree.print_inorden(tree.root);
	cout<<"\nEl arbol impreso  preorden es: "<<endl;
	tree.print_preorden(tree.root);
	cout<<"\nEl arbol impreso  postorden es: "<<endl;
	tree.print_postorden(tree.root);
	tree.amplitud();
	tree.profundidad();
	*/
	
}
