#pragma once
#include "CNode.h"
#include <iostream>
#include <list>

using std::cout;

int Mayor(int x, int y);
int Menor(int x, int y);

template <typename T>
class Tree
{
public:
	Tree();
	~Tree();
	CNode<T>* mRoot;
    bool Find(T x, CNode<T>** &p);


    bool insertar(T x);
    bool remover(T x);

	void InOrder(CNode<T>* p);

};

template <typename T>
Tree<T>::Tree()
{
	mRoot = nullptr;
}

template <typename T>
Tree<T>::~Tree()
{
}

template<typename T>
inline bool Tree<T>:: Find(T x,CNode<T>**&p){
    p=&mRoot;
    while( (*p )&& (*p)->info != x){
        p=&((*p)->hijos[(*p)->info < x]);
        }
    return *p;
}




template<typename T>
inline bool Tree<T>::insertar(T x)
{
	CNode<T>** p;
    if ( Find(x , p)
	{
		return 0;
	}
	*p = new CNode<T>(x);
	return 1;
}

template <typename T>
CNode<T>** Intercambio(CNode<T>** q )
{
	q = &(*q)->mNode[0];
	while ((*q)->mNode[1])
	{
		q = &((*q)->mNode[1]);
	}
	return q;
}

template<typename T>
inline bool Tree<T>::remover(T x)
{
	CNode<T> **p, **q;
    if (!Find(x, p))
	{
		return 0;
	}
	if ((*p)->mNode[0] && (*p)->mNode[1])
	{
		q = Intercambio(p);
		(*p)->mData = (*q)->mData;
		p = q;
	}
	CNode<T>* t = *p;
	*p = (*p)->mNode[(*p)->mNode[1]];
	delete t;
	return 1;
}

template <typename T>
void  Tree<T>::InOrder(CNode<T>* p)
{
	if (!p) return;
	InOrder(p->mNode[0]);
	cout << p->mData << " ";
	InOrder(p->mNode[1]);
}

template <typename T>
void  Tree<T>::PreOrder(CNode<T>* p)
{
	if (!p) return;
	cout << p->mData << " ";
	InOrder(p->mNode[0]);
	InOrder(p->mNode[1]);
}

template <typename T>
void  Tree<T>::PostOrder(CNode<T>* p)
{
	if (!p) return;
	InOrder(p->mNode[0]);
	InOrder(p->mNode[1]);
	cout << p->mData << " ";
}

template <typename T>
void Tree<T>:: printBonito(){
    vector <nodo<T>* > c;
    c.push_back(root);
    int len;
    while(c.size()!=0){
        len=c.size();
        for(int i=0;i<len;i++){
        if(c[i]){
        cout<<c[i]->info<<" ";
        c.push_back(c[i]->hijos[0]);
        c.push_back(c[i]->hijos[1]);
        }
        else
        cout << "- ";

        }
        cout<<endl;
        c.erase(c.begin(),c.begin()+len);
    }
}

