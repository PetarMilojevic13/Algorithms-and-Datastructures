#ifndef _heap_
#define _heap_

#include <iostream>
#include <iomanip>
using namespace std;
class Heap
{
	int* heap;
	int red;
	int trenutni_broj;
	int kapacitet;

	void clear();
	void copy(const Heap& heap);
	void move(Heap& heap);
	void setanje_do_oca(int indeks, int& steps);


public:
	Heap() :red(0), trenutni_broj(0) { heap = nullptr;};

	int* dohvati_heap()const { return heap;}
	Heap(const Heap&);
	Heap& operator= (const Heap&);
	Heap(Heap&&);
	void setanje_po_sinovima(int& steps, int index);
	Heap& operator= (Heap&&);

	void init(int m) { trenutni_broj = 0; red = m; heap = new int[1000]; kapacitet = 1000; }

	void add(int elem, int& steps);

	int get() const;
	int obrisi (int& steps);

	void destroy();

	void convertTo(int newM);

	void unija(Heap& h, int& steps);

	friend ostream& operator << (ostream& os, const Heap& hip);

	~Heap();

	void brisanje_zadatog_kljuca(int kljuc, int& steps);

	int father(int index)const { return (index - 1) / red;}
	int dohvati_trenutni()const { return trenutni_broj; }

};


#endif
