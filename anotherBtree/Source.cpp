#include "NodeB.h"
#include "Btree.h"

template<class E>void insertar(NodeB<E>& nd, E ele, int max){
	E aux;
	int j;
	if (!nd.nodeFull(max-1)){

		for (j = nd.getCount() - 1; j >= 0 && ele<nd.getKeys()[j]; j--)
			nd.getKeys()[j + 1] = nd.getKeys()[j];
		nd.getKeys()[j+1] = ele;
		nd.setCount(nd.getCount() + 1);
	}	
	else
		cout << "Lleno"<< endl;
}

int  main(){
	BTree<int> a(5);
	a.insert(10);
	a.insert(4);
	a.insert(23);
	a.insert(17);
	a.insert(2);
	a.insert(35);
	a.insert(24);
	a.insert(18);
	a.insert(29);
	a.insert(31);
	a.insert(6);
	a.insert(15);
	a.insert(22);
	a.insert(48);
	a.insert(1);
	a.insert(11);
	a.insert(21);
	a.insert(57);
	a.insert(36);
	a.insert(42);
	a.insert(45);
	cout << a;
	system("pause");
}
