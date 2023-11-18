#pragma once
#include"Header.h"


template<class DataType>
class Node {
public:
    DataType data;
    Node* pNext;
    Node(DataType);
    void display();
};

template <class DataType>
Node<DataType>::Node(DataType _data)
{
	this->data = _data;
	this->pNext = NULL;
}

template <class DataType>
void Node<DataType>::display()
{
	cout << this->data << endl;
}



template <class DataType>
class LinkedList {
public:
	Node<DataType>* pHead;
	Node<DataType>* pTail;
	int iSize;
	LinkedList();
	~LinkedList();
	void addTail(DataType);
	void clear();
	void removeHead();
	Node<DataType>* searchPre(Node<DataType>*);
	void remove(DataType);
	void display();
	void selectionSort();
	int getSize();
};

template <class DataType>
LinkedList<DataType>::LinkedList()
{
	this->pHead = this->pTail = NULL;
	this->iSize = 0;
}
template <class DataType>
LinkedList<DataType>::~LinkedList() {}

template <class DataType>
void LinkedList<DataType>::addTail(DataType _data)
{
	Node<DataType>* pAdd = new Node<DataType>(_data);
	if (pHead == NULL)
		pHead = pTail = pAdd;
	else
	{
		pTail->pNext = pAdd;
		pTail = pAdd;
	}
	iSize++;
	//delete pAdd; // khong delete dc
}

template <class DataType>
void LinkedList<DataType>::removeHead()
{
	if (pHead != NULL)
	{
		Node<DataType>* pTemp = pHead;
		pHead = pHead->pNext;
		delete pTemp;
		if (pHead == NULL)
			pTail = NULL;
		iSize--;
	}
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node)
{
	Node<DataType>* p = pHead;
	if (p == node)
		return NULL;
	while ((p != NULL) && (p->pNext != node))
		p = p->pNext;
	return p;
}

template <class DataType>
void LinkedList<DataType>::remove(DataType _data)
{
	Node<DataType>* p = pHead, * pTemp = NULL;
	while ((p != NULL) && (p->data != _data))
	{
		pTemp = p;
		p = p->pNext;
	}

	if (p == NULL)
		return;
	if (pTemp != NULL)
	{
		if (p == pTail)
		{
			pTail = pTemp;
			pTail->pNext = NULL;
		}
		pTemp->pNext = p->pNext;
		delete p;
		iSize--;
	}
}

template <class DataType>
void LinkedList<DataType>::clear()
{
	while (pHead != NULL)
		removeHead();
}

template <class DataType>
void LinkedList<DataType>::selectionSort()
{
	Node<DataType>* pMax;
	Node<DataType>* p, * q;
	for (p = pHead; p->pNext != NULL; p = p->pNext)
	{
		pMax = p;
		for (q = p->pNext; q != NULL; q = q->pNext)
			if (q->data.getSoMu() > pMax->data.getSoMu())
				pMax = q;
		swap(pMax->data, p->data);
	}
}

template <class DataType>
void LinkedList<DataType>::display()
{
	Node<DataType>* p = pHead;
	while (p != NULL)
	{
		p->display();
		p = p->pNext;
	}
	delete p;
}
template <class DataType>
int LinkedList<DataType>::getSize(){
	return iSize;
}