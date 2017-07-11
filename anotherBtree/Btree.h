#ifndef BTREE_H
#define BTREE_H
#include "NodeB.h"

template<class E>class BTree{
private:
	NodeB<E>* root;
	int orden;
	void inOrden(NodeB<E>*);

public:
	BTree(int);
	void insert(E);
	void push(NodeB<E>*, E, bool*, E*, NodeB<E>**);
	bool findNode(NodeB<E>*, E, int*);
	void putNode(NodeB<E>*, E, NodeB<E>*, int);
	void inOrden();
	void dividedNode(NodeB<E>*, E, NodeB<E>*, int, E*, NodeB<E>**);
	NodeB<E>* succesorFind(NodeB<E>*);
	void RedistributionLeft(NodeB<E>*,NodeB<E>*,NodeB<E>*);
	void RedistributionRight(NodeB<E>*, NodeB<E>*, NodeB<E>*);
	ostream& operator<< <>(ostream& salida, BTree<E>& obj){
	obj.inOrden();
	return salida;
	}

};
template<class E>BTree<E>::BTree(int orden){
	this->orden = orden;
	root = 0;
}
template<class E>void BTree<E>::insert(E ele){
	bool up;
	E clMedian;
	NodeB<E>* pnew, *nd;
	push(root, ele, &up, &clMedian, &nd);
	if (up){
		pnew = new NodeB<E>(orden);
		pnew->getKeys()[0] = clMedian;
		pnew->getChilds()[0] = root;
		pnew->getChilds()[1] = nd;
		pnew->setCount(1);
		root = pnew;
	}
}
template<class E>void BTree<E>::push(NodeB<E>* act, E ele, bool* up, E* clMedian, NodeB<E>** newNode){
	int pos;
	if (!act){
		(*up) = true;
		(*clMedian) = ele;
		(*newNode) = 0;
	}
	else{
		bool f1 = findNode(act, ele, &pos);
		if (f1){
			cout << "El elemento esta duplicado"<<endl;
			(*up) = false;
			return;
		}
		push(act->getChilds()[pos], ele, up, clMedian, newNode);
		if ((*up)){
			if (act->nodeFull(orden - 1)){
				dividedNode(act, *clMedian, *newNode, pos, clMedian, newNode);
			}
			else{
				(*up) = false;
				putNode(act, *clMedian, *newNode, pos);
			}
		}

	}
}
template<class E> bool BTree<E>::findNode(NodeB<E>* act, E ele, int *pos){
	(*pos) = 0;
	while ((*pos)<act->getCount() && ele > act->getKeys()[(*pos)])
		(*pos)++;
	return (ele == act->getKeys()[(*pos)]);
}
template<class E>void BTree<E>::putNode(NodeB<E>*act, E clMedian, NodeB<E>*nd, int pos){
	int i;
	for (i = act->getCount() - 1; i >= pos; i--){
		act->getKeys()[i + 1] = act->getKeys()[i];
		act->getChilds()[i + 2] = act->getChilds()[i + 1];
	}
	act->getKeys()[pos] = clMedian;
	act->getChilds()[i + 2] = nd;
	act->setCount(act->getCount() + 1);

}
template<class E> void BTree<E>::inOrden(){
	inOrden(root);
	
}
template<class E> void BTree<E>::inOrden(NodeB<E>* act){
	if (act)
	{
		int i;
		for (i = 0; i < act->getCount(); i++)
			cout << act->getKeys()[i]<< " ";
		cout << endl;
		for (i = 0; i <= act->getCount(); i++)
			inOrden(act->getChilds()[i]);
		}
}


 template<class E>void BTree<E>::dividedNode(NodeB<E>* act, E cl, NodeB<E>* hd, int pos, E* clMediana, NodeB<E>** nd){
	 int i, posMdna;
	 posMdna = (pos <= orden / 2) ? orden / 2 : orden / 2 + 1;
	 (*nd) = new NodeB<E>(orden);
	 for (i = posMdna; i < orden - 1; i++){
		 (*nd)->getKeys()[i - posMdna] = act->getKeys()[i];
		 (*nd)->getChilds()[i - posMdna+1] = act->getChilds()[i+1];
	 }
	 (*nd)->setCount(orden - 1 - posMdna);
	 act->setCount(posMdna);
	 if (pos <= orden / 2)
		 putNode(act, cl, hd, pos);
	 else
		 putNode(*nd, cl, hd, pos - posMdna);
	 (*clMediana) = act->getKeys()[act->getCount() - 1];
	 (*nd)->getChilds()[0] = act->getChilds()[act->getCount()];
	 act->setCount(act->getCount() - 1);
 }
 template<class E>NodeB<E>* BTree<E>::succesorFind(NodeB<E>*act){
	 while (act)
		 act = act->getChilds()[act->getCount()-1]
	 return act->getKeys[0];
 }
 template<class E>void BTree<E>::RedistributionLeft(NodeB<E>*act, NodeB<E>*bro, NodeB<E>*father){
	 int i = 0;
	 while (i < father->getCount() && father->getKeys()[i] < bro->getKeys()[bro->getCount() - 1])
		 i++;
	 putNode(act, father->getKeys()[i], father->getChilds()[father->getCount()], 0);
	 father->getKeys()[i] = bro->getKeys()[bro->getCount() - 1];
	 bro->getKeys()[bro->getCount()-1] = NULL;
	 bro->getChilds()[bro->getCount()] = NULL;
 }
 template<class E>void BTree<E>::Redistribution(NodeB<E>*act, NodeB<E>*bro, NodeB<E>*father){
	 int i = 0;
	 while (i < father->getCount() && father->getKeys()[i] < bro->getKeys()[bro->getCount() - 1])
		 i++;
	 putNode(act, father->getKeys()[father->getCount() - 1], father->getChilds()[0], act->getCount());
	 father->getKeys()[i] = bro->getKeys()[bro->getCount() - 1];
	 bro->getKeys()[bro->getCount() - 1] = NULL;
	 bro->getChilds()[bro->getCount()] = NULL;
 }
#endif
