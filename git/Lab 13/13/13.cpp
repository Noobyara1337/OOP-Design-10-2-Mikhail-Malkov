// 13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Heap.h"
#include <iostream>
#include <iomanip>
void AAA::Print() { std::cout << x; }
int AAA::GetPriority() const { return x; }
namespace heap
{
	Heap Create(int maxsize, CMP(*f)(void*, void*))
	{
		return *(new Heap(maxsize, f));
	}
	int Heap::Left(int ix)
	{
		return (2 * ix + 1 >= Size) ? -1 : (2 * ix + 1);
	}
	int Heap::Right(int ix)
	{
		return (2 * ix + 2 >= Size) ? -1 : (2 * ix + 2);
	}
	int Heap::Parent(int ix) { return (ix + 1) / 2 - 1; }
	void Heap::Swap(int i, int j)
	{
		void* buf = Storage[i]; Storage[i] = Storage[j];
		Storage[j] = buf;
	}
	void Heap::Heapify(int ix)
	{
		int l = Left(ix), r = Right(ix), irl = ix;
		if (l>0)
		{
			if (isGreat(Storage[l], Storage[ix]))     irl = l;
			if (r>0 && isGreat(Storage[r], Storage[irl]))
				irl = r; if (irl != ix)
			{
				Swap(ix, irl);	Heapify(irl);
			}
		}
	}

	void Heap::Insert(void* x)
	{
		int i; if (!isFull())
		{
			Storage[i = ++Size - 1] = x;
			while (i>0 && isLess(Storage[Parent(i)], Storage[i]))
			{
				Swap(Parent(i), i);	i = Parent(i);
			}
		}
	}
	void* Heap::ExtractMax()
	{
		void* rc = NULL;   if (!isEmpty())
		{
			rc = Storage[0];	Storage[0] = Storage[Size - 1];
			Size--;	Heapify(0);
		}
		return rc;
	}

	void * Heap::Min()
	{
		void* min = NULL;
		int i = 1;
		if (!isEmpty())
		{
			min = Storage[0];
			Storage[i] = NULL;
			i--;
			/*while (Storage[i] != NULL)
			{
				if (min > Storage[i])
					min = Storage[i];
				i++;
			}*/
		}
		Storage[i] = Storage[Size - 1];
		Size--;
		Heapify(0);
		return min;

	}

	void * Heap::ExtractI(int i)
	{
		void* rc = NULL;   if (!isEmpty())
		{
			rc = Storage[i];
			Storage[i] = Storage[Size - 1];
			Size--;
			Heapify(0);
		}
		return rc;
	}



	//вывод значений элементов на экран 	
	void Heap::Scan(int i) const
	{
		int prodel = 20;	std::cout << '\n';
		if (Size == 0) std::cout << "Куча пуста";
		for (int u = 0, y = 0; u<Size; u++)
		{
			std::cout << std::setw(prodel + 10) << std::setfill(' ');
			((AAA*)Storage[u])->Print();
			if (u == y) {
				std::cout << '\n';
				if (y == 0)y = 2; else y += y * 2;
			} prodel /= 2;
		}
		std::cout << '\n';
	}
	void Heap::DeleteHeap()
	{
		if (!isEmpty())
		{
			Size = 0;	this->~Heap();
		}
	}
}
