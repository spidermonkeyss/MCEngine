#pragma once

template<class T>
class List
{
private:
	unsigned int capcity;
	unsigned int size;
	T* listArray;

	void IncreaseArrayCapcity()
	{
		T* tempArray = new T[capcity + 1];
		for (int i = 0; i < capcity - 1; i++)
		{
			tempArray[i] = listArray[i];
		}
		delete[] listArray;
		listArray = tempArray;
	}
public:
	List() :capcity(0), size(0), listArray(nullptr){ }
	List(unsigned int _capcity)
		:capcity(_capcity), size(0)
	{
		listArray = new T[_capcity];
	}
	~List()
	{
		if (listArray != nullptr)
			delete[] listArray;
	}
	
	void Add(T obj)
	{
		size++;
		if (size > capcity)
			IncreaseArrayCapcity();

		listArray[size - 1] = obj;
	}

	bool Remove(unsigned int index)
	{
		if (index > size - 1)
		{
			std::cout << "Index for list bigger than size!" << std::endl
			return false;
		}
		for (int i = index; i < size - 1; i++)
		{
			listArray[i] = listArray[i + 1];
		}
		size--;
	}

	T* At(unsigned int index)
	{
		return &listArray[index];
	}

	T* operator[](unsigned int index)
	{
		return &listArray[index];
	}

	inline unsigned int Capcity() { return capcity; }
	inline unsigned int Size() { return size; }
};