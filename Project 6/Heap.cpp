#include "Heap.h"

void Heap::add(int elem, int& steps)
{
	if (trenutni_broj == kapacitet)
	{
		int* privremeni = new int[100 * trenutni_broj];
		for (int i = 0; i < trenutni_broj; i++)
		{
			privremeni[i] = heap[i];
		}
		kapacitet = kapacitet * 1000;
		delete[] heap;
		heap = privremeni;
	}
	if (heap == nullptr)
	{
		cout << "Heap mora prvo biti napravljen" << endl;
	}
	else
	{
		if (trenutni_broj == 0)
		{
			heap[0] = elem;
			trenutni_broj++;
		}
		else
		{
			heap[trenutni_broj] = elem;
			trenutni_broj++;

			int brojka = trenutni_broj - 1;
			int otac;
			while (true)
			{
				otac = (brojka - 1) / red;
				if (heap[otac] > heap[brojka])
				{
					steps++;
					int tmp = heap[brojka];
					heap[brojka] = heap[otac];
					heap[otac] = tmp;
					brojka = otac;
					steps++;
				}
				else
				{
					steps++;
					break;
				}
				if (brojka == 0)break;
			}
		}

	}
}

int Heap::get() const
{
	if (heap == nullptr)
	{
		cout << "Trebate prvo napraviti heap!" << endl;
		return -1;
	}
	else if (trenutni_broj == 0)
	{
		cout << "Heap je prazan!" << endl;
		return -1;
	}
	else
	{
		return heap[0];
	}
}

int Heap::obrisi(int& steps)
{

	if (trenutni_broj > 0 && heap != nullptr)
	{
		int broj = heap[0];
		heap[0] = heap[trenutni_broj - 1];
		trenutni_broj--;
		int brojka = 0;
		while (true)
		{
			int min = 1000000;
			int indeks = -1;
			bool kraj = false;
			for (int i = 0; i < red; i++)
			{
				int sin = brojka * red + i + 1;
				if (sin > trenutni_broj - 1) { break; kraj = true; }
				if (heap[sin] < heap[brojka] && heap[sin] < min) { min = heap[sin]; indeks = sin; steps++; }
			}
			if (indeks == -1)
			{
				steps++;
				break;
			}
			else
			{
				steps++;
				steps++;
				heap[indeks] = heap[brojka];
				heap[brojka] = min;
				brojka = indeks;
				if (kraj)break;
			}
		}
		return broj;
	}
}

void Heap::destroy()
{
	trenutni_broj = 0;
	red = 0;
	delete[] heap;
	heap = nullptr;
}

void Heap::convertTo(int newM)
{
	red = newM;
	int q = -1;
	for (int i = trenutni_broj - 1; i >= 0; i--)
	{
		setanje_do_oca(i, q);
	}
}

void Heap::unija(Heap& h, int& steps)
{

	for (int i = trenutni_broj; i < trenutni_broj + h.trenutni_broj; i++)
	{
		heap[i] = h.heap[i - trenutni_broj];
	}
	int pocetak = trenutni_broj;
	trenutni_broj = trenutni_broj + h.trenutni_broj;
	for (int i = trenutni_broj/red; i >=0 ; i--)
	{
		setanje_po_sinovima(steps,i);
	}
}

void Heap::setanje_po_sinovima(int& steps, int index)
{
	int brojka = index;
	while (true)
	{
		int min = 1000000;
		int indeks = -1;
		bool kraj = false;
		for (int i = 0; i < red; i++)
		{
			int sin = brojka * red + i + 1;
			if (sin > trenutni_broj - 1) { break; kraj = true; }
			if (heap[sin] < heap[brojka] && heap[sin] < min) { min = heap[sin]; indeks = sin; steps++; }
		}
		if (indeks == -1)
		{
			steps++;
			break;
		}
		else
		{
			steps++;
			steps++;
			heap[indeks] = heap[brojka];
			heap[brojka] = min;
			brojka = indeks;
			if (kraj)break;
		}
	}

};

Heap::~Heap()
{
	clear();
}

void Heap::brisanje_zadatog_kljuca(int kljuc, int& steps)
{
	if (heap == nullptr) { cout << "Heap nije prvo napravljen!" << endl; }
	else if (trenutni_broj <= 0) { cout << "Heap je prazan!" << endl; }
	else if (trenutni_broj > 0 && heap != nullptr)
	{
		int index = -1;
		for (int i = 0; i < trenutni_broj; i++)
		{
			if (heap[i] == kljuc) { index = i; break; }
		}
		if (index == -1)
		{
			cout << "Kljuc " << kljuc << " ne postoji u heapu!" << endl;
		}
		else
		{
			heap[index] = heap[trenutni_broj - 1];
			trenutni_broj--;
			int brojka = index;
			while (true)
			{
				int min = 1000000;
				int indeks = -1;
				bool kraj = false;
				for (int i = 0; i < red; i++)
				{
					int sin = brojka * red + i + 1;
					if (sin > trenutni_broj - 1) { break; kraj = true; }
					if (heap[sin] < heap[brojka] && heap[sin] < min) { min = heap[sin]; indeks = sin; }
				}
				if (indeks == -1)
				{
					steps++;
					break;
				}
				else
				{
					steps++;
					steps++;
					heap[indeks] = heap[brojka];
					heap[brojka] = min;
					brojka = indeks;
					if (kraj)break;
				}
			}
			int koraci = 0;
			setanje_do_oca(index, koraci);
		}
	}

}


void Heap::clear()
{
	delete[] heap;
	trenutni_broj = 0;
	heap = nullptr;
	red = 0;
}

void Heap::copy(const Heap& heap)
{


	this->red = heap.red;
	this->trenutni_broj = heap.trenutni_broj;
	for (int i = 0; i < trenutni_broj; i++)
	{
		this->heap[i] = heap.heap[i];
	}
}

void Heap::move(Heap& heap)
{
	delete[] this->heap;
	this->heap = heap.heap;
	this->red = heap.red;
	this->trenutni_broj = heap.trenutni_broj;
	heap.heap = nullptr;
	heap.trenutni_broj = 0;
	heap.red = 0;
}

void Heap::setanje_do_oca(int indeks, int& steps)
{
	int brojka = indeks;
	int otac;
	while (true)
	{
		otac = (brojka - 1) / red;
		if (heap[otac] > heap[brojka])
		{
			steps++;
			int tmp = heap[brojka];
			heap[brojka] = heap[otac];
			heap[otac] = tmp;
			brojka = otac;
			steps++;
		}
		else
		{
			steps++;
			break;
		}
		if (brojka == 0)break;
	}
}

Heap::Heap(const Heap& hip)
{
	copy(hip);
}

Heap& Heap::operator=(const Heap& hip)
{
	if (this != &hip)
	{
		clear();
		copy(hip);
	}
	return *this;
}

Heap::Heap(Heap&& hip)
{
	move(hip);
}

Heap& Heap::operator=(Heap&& hip)
{
	if (this != &hip)
	{
		clear();
		move(hip);
	}
	return *this;
}

ostream& operator<<(ostream& os, const Heap& hip)
{
	if (hip.heap == nullptr) { os << "Prvo mora da se napravi heap!" << endl; return os; }
	else if (hip.trenutni_broj == 0) { os << "Heap je prazan!" << endl; return os; }

	else
	{
		if (hip.red == 2)
		{
			int brojac = 0;

			while (true)
			{
				if (brojac >= hip.trenutni_broj) { cout << endl; cout << endl; break; }

				int broj = hip.heap[brojac];
				if (brojac == 0)
				{
					for (int i = 0; i < 45; i++)
					{
						cout << " ";
					}
					cout << setw(2) << setfill(' ') << broj << endl;
				}
				else if (brojac == 1)
				{
					for (int i = 0; i < 21; i++)
					{
						cout << " ";
					}
					cout << setw(2) << setfill(' ') << broj;
					for (int i = 0; i < 46; i++)
					{
						cout << " ";
					}
				}
				else if (brojac == 2)
				{
					cout << setw(2) << setfill(' ') << broj << endl;
				}
				else if (brojac == 3)
				{
					for (int i = 0; i < 9; i++)
					{
						cout << " ";
					}
					cout << setw(2) << setfill(' ') << broj;
					for (int i = 0; i < 22; i++)
					{
						cout << " ";
					}
				}
				else if (brojac >= 4 && brojac <= 6)
				{
					cout << setw(2) << setfill(' ') << broj;
					for (int i = 0; i < 22; i++)
					{
						cout << " ";
					}
					if (brojac == 6)cout << endl;
				}
				else if (brojac >= 7 && brojac <= 14)
				{
					if (brojac == 7)
					{
						for (int i = 0; i < 3; i++)
						{
							cout << " ";
						}
						cout << setw(2) << setfill(' ') << broj;

					}
					else
					{
						for (int i = 0; i < 10; i++)
						{
							cout << " ";
						}
						cout << setw(2) << setfill(' ') << broj;
					}
					if (brojac == 14)cout << endl;
				}
				else
				{
					cout << setw(2) << setfill(' ') << broj;
					for (int i = 0; i < 4; i++)
					{
						cout << " ";
					}
				}
				brojac++;
			}

		}
		else if (hip.red == 3)
		{
			int brojac = 0;

			while (true)
			{
				if (brojac >= hip.trenutni_broj) { cout << endl; cout << endl; break; }

				int broj = hip.heap[brojac];
				if (brojac == 0)
				{
					for (int i = 0; i < 94; i++)
					{
						cout << " ";
					}
					cout << setw(2) << setfill(' ') << broj << endl;

				}
				else if (brojac >= 1 && brojac <= 3)
				{
					if (brojac == 1)
					{
						for (int i = 0; i < 28; i++)
						{
							cout << " ";
						}
					}
					else
					{
						for (int i = 0; i < 64; i++)
						{
							cout << " ";
						}

					}
					cout << setw(2) << setfill(' ') << broj;
					if (brojac == 3)cout << endl;
				}
				else if (brojac >= 4 && brojac <= 12)
				{
					if (brojac == 4)
					{
						for (int i = 0; i < 6; i++)
						{
							cout << " ";
						}
					}
					else
					{
						for (int i = 0; i < 20; i++)
						{
							cout << " ";
						}
					}
					cout << setw(2) << setfill(' ') << broj;
					if (brojac == 12)cout << endl;
				}
				else if (brojac > 12)
				{
					cout << setw(2) << setfill(' ') << broj;
					if (brojac % 3 > 0)
					{
						for (int i = 0; i < 4; i++)
						{
							cout << " ";
						}
					}
					else
					{
						for (int i = 0; i < 8; i++)
						{
							cout << " ";
						}
					}
				}
				brojac++;
			}
		}
		else if (hip.red == 4)
		{
			int brojac = 0;

			while (true)
			{
				if (brojac >= hip.trenutni_broj) { cout << endl; cout << endl; break; }

				int broj = hip.heap[brojac];
				if (brojac == 0)
				{
					for (int i = 0; i < 52; i++)
					{
						cout << " ";
					}
					cout << setw(2) << setfill(' ') << broj;
					cout << endl;
				}
				else if (brojac > 0 && brojac <= 4)
				{
					if (brojac == 1)
					{
						for (int i = 0; i < 10; i++)
						{
							cout << " ";
						}

					}
					else
					{
						for (int i = 0; i < 26; i++)
						{
							cout << " ";
						}
					}
					cout << setw(2) << setfill(' ') << broj;
					if (brojac == 4)cout << endl;
				}
				else
				{
					cout << setw(2) << setfill(' ') << broj;
					if (brojac % 2 == 1)
					{
						for (int i = 0; i < 4; i++)
						{
							cout << " ";
						}
					}
					else
					{
						for (int i = 0; i < 6; i++)
						{
							cout << " ";
						}

					}
				}
				brojac++;
			}




		}
	}
}



