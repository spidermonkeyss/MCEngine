#pragma once

template <class T>
struct Node
{
	T thisNode;
	Node* Next;
};

template<class T>
class List
{
private:
	unsigned int size;

	template <class T>
	Node<T>* GetNode(int i)
	{
		Node<T>* currentNode = head;
		for (int k = 0; k < i; k++)
			currentNode = currentNode->Next;

		return currentNode;
	}
public:
	Node<T>* head;
	Node<T>* tail;

	List() 
		:size(0)
	{
		head = nullptr;
		tail = nullptr;
	}
	~List()
	{
		DeleteList();
	}
	
	//Will empty the list
	void SetSize(unsigned int _size)
	{
		DeleteList();
		size = _size;
		head = new Node<T>();
		Node<T>* currentNode = head;
		for (int i = 1; i < size; i++)
		{
			currentNode->Next = new Node<T>();
			currentNode = currentNode->Next;
		}
		tail = currentNode;
		tail->Next = nullptr;
	}

	void DeleteList()
	{
		Node<T>* currentNode = head;
		Node<T>* prevNode = head;
		for (int i = 0; i < size; i++)
		{
			prevNode = currentNode;
			currentNode = currentNode->Next;
			delete prevNode;
		}
	}

	unsigned int Size()
	{
		return size;
	}

	void MoveBack(unsigned int index)
	{
		if (index > size - 1)
		{
			std::cout << "index to big\n";
			return;
		}

		Node<T>* node = GetNode<T>(index);
		Node<T>* prevNode = GetNode<T>(index - 1);
		prevNode->Next = node->Next;
		tail->Next = node;
		tail = node;
		node->Next = nullptr;
	}

	void Swap(unsigned int fIndex, unsigned int sIndex)
	{
		if (fIndex >= sIndex)
		{
			if (fIndex == sIndex)
				std::cout << "fIndex = " << fIndex;
			std::cout << "fIndex must be smaller than sIndex\n";
			return;
		}
		if (fIndex > size - 1)
		{
			std::cout << "fIndex to big\n";
			return;
		}
		if (sIndex > size - 1)
		{
			std::cout << "sIndex to big\n";
			return;
		}

		Node<T>* firstNode = GetNode<T>(fIndex);
		Node<T>* secondNode = GetNode<T>(sIndex);
		Node<T>* tempNode = firstNode->Next;

		firstNode->Next = secondNode->Next;
		secondNode->Next = tempNode;

		if (fIndex == 0)
		{
			head = secondNode;
			GetNode<T>(sIndex - 1)->Next = firstNode;
		}
		else
		{
			GetNode<T>(fIndex - 1)->Next = secondNode;
			GetNode<T>(sIndex - 1)->Next = firstNode;
		}
	}

	T operator [](int i) const
	{ 
		Node<T>* currentNode = head;
		for (int k = 0; k < i; k++)
			currentNode = currentNode->Next;

		return currentNode->thisNode;
	}
	T& operator [](int i)
	{
		Node<T>* currentNode = head;
		for (int k = 0; k < i; k++)
			currentNode = currentNode->Next;

		return currentNode->thisNode;
	}
};

template <class T>
class Iterator
{
private:
	List<T>* list;
	int iteratorIndex;
	Node<T>* iteratorNodeIndex;
public:
	Iterator(List<T>* _list)
	{
		list = _list;
		iteratorIndex = 0;
		if (list != nullptr)
			iteratorNodeIndex = list->head;
		else
			iteratorNodeIndex = nullptr;
	}

	void Iterator_Next()
	{
		iteratorIndex++;
		iteratorNodeIndex = iteratorNodeIndex->Next;
	}

	int* Iterator_GetIndex() { return &iteratorIndex; }
	T& Value() { return iteratorNodeIndex->thisNode; }
};