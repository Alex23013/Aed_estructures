#include<iostream>
#include<string>
using namespace std;
template<typename Y>
class nodo{
public:
Y dato;
nodo* sig;

nodo(Y dato){
	this->dato=dato;
	sig =NULL;
	}

};
template<typename Y>
class lista{

public:
 nodo<Y>* head;

};

int main(){
nodo<int> A(2);
cout<<A.dato<<endl;

nodo<float> b(2.3);
cout<<b.dato<<endl;

nodo<char> c('s');
cout<<c.dato<<endl;

}
