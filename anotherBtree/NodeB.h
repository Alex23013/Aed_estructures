#ifndef NODEB_H
#define NODEB_H
#include <iostream>
using namespace std;
template<class E>class NodeB{
private:
	E *keys;
	NodeB<E>** childs;
	int count;
public:
	NodeB(int);
	int getCount();
	void setCount(int);
	E& operator[](int);
	bool nodeFull(int);
	bool nodeEmpty(int);
	E* getKeys();
	NodeB<E>** getChilds();
	friend ostream& operator<<(ostream& os, NodeB<E> &x){
		for (int i = 0; i < x.getCount(); i++)
			os << x[i] << " ";
		return os;
	}
};
template<class E>NodeB<E>::NodeB(int orden){
	keys = new E[orden];
	childs = new NodeB<E>*[orden];
	count = 0;
	for (int i = 0; i < orden; i++)
		childs[i] = 0;
}
template<class E>bool NodeB<E>::nodeFull(int orden){
	return(count == orden);
}
template<class E>bool NodeB<E>::nodeEmpty(int orden){
	return(count < orden/2);
}
template<class E>E& NodeB<E>::operator[](int i){
	return this->keys[i];
}
template<class E>int NodeB<E>::getCount(){
	return count;
}
template<class E>void NodeB<E>::setCount(int x){
	this->count = x;
}
template<class E>E* NodeB<E>::getKeys(){
	return keys;
}
template<class E>NodeB<E>** NodeB<E>::getChilds(){
	return childs;
}
#endif