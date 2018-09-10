#include "stdafx.h"
#include "Heap.h"
#include <iostream>
#include <fstream>

using namespace std;
int counter = 0;
heap::CMP cmpAAA(void * a1, void* a2) {
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
	heap::CMP rc = heap::EQUAL;
	if (A1->x > A2->x)
		rc = heap::GREAT;
	else
		if (A2->x > A1->x)
			rc = heap::LESS;
	return rc;
#undef A2
#undef A1
}

bool BulidHeap(char *FileName, heap::Heap& h)	//���������� ���� �� �����
{
	bool rc = true; int n;
	ifstream inFile;
	inFile.open(FileName, ios::out);
	if (!inFile) {
		cout << "���������� ������� ����" << endl;
		exit(1);
	}
	cout << "�������� ������\n" << endl;
	while (inFile >> n) {
		int *a = new int;
		*a = n;
		h.Insert((void*)a);
		cout << *a << endl;
	}
	inFile.close();
	return rc;
}

void SaveHeap(heap::Heap &h, char *FileName)
{
	ofstream outFile(FileName, ios_base::out | ios_base::trunc);
	if (!outFile) {
		cout << "������ ��������� ��������� �����" << endl;
		return;
	}
	int *a = new int;
	for (int u = 0, y = 0; u < h.Size; u++) {
		a = (int*)h.Storage[u];//storage-�������� ��������
		outFile << *a;
		outFile << std::endl;
	}
	outFile.close();
}

int main() {
	setlocale(LC_ALL, "rus");
	int k;
	heap::Heap h1 = heap::Create(30, cmpAAA);
	heap::Heap h2 = heap::Create(30, cmpAAA);

	int choise;
	for (;;) {
		cout << "1 - ����� ���� �� �����" << endl;
		cout << "2 - ���������� ��������" << endl;
		cout << "3 - �������� �������������" << endl;
		cout << "4 - �������� ����" << endl;
		
	
		cout << "7 - �������� �������� �� 2-�� ����" << endl;
		cout << "8 - ����� 2-�� ���� �� �����" << endl;
		cout << "9 - ����������� 2-�� ���" << endl;
		cout << "10 - �������� i-�� ��������" << endl;
		cout << "11 - �������� ������������ ��������" << endl;
		cout << "0 - �����" << endl;
		cout << "�������� �����" << endl;
		cin >> choise;
		switch (choise)
		{
		case 0: exit(0);
		case 1: h1.Scan(0); break;
		case 2: { AAA *a = new AAA;
			std::cout << "������� ����" << std::endl;
			std::cin >> k;
			a->x = k;
			h1.Insert(a); }
				break;
		case 3: h1.ExtractMax(); break;
		case 4: h1.DeleteHeap(); break;
	
		
		case 7: {
			AAA *a = new AAA;
			cout << "������� ����" << endl;
			cin >> k;
			a->x = k;
			h2.Insert(a);
			counter++; }
				break;
		case 8: h2.Scan(0); break;
		case 9: {
			int i = 0;
			for (i = 0; i < counter; i++)
				h1.Insert(h2.ExtractMax()); }
				break;
		case 10: {
			int i;
			cout << "������� i:" << endl;
			cin >> i;
			h1.ExtractI(i); }
				 break;
		case 11: h1.Min(); break;
			cout << endl << "������� �������� �������!" << endl;
		}
	}
	return 0;
}
	