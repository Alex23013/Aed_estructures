#pragma once

template <typename T>
class CNode
{
public:
	T mData;
	CNode<T>* mNode[2];

	CNode(T x);
	~CNode();
};

template<typename T>
inline CNode<T>::CNode(T x)
{
	mData = x;
	mNode[0] = mNode[1] = nullptr;
}

template<typename T>
inline CNode<T>::~CNode()
{
}
