#include <iostream>
using namespace std;
#include "Heap.h"
#include <fstream>
#include <chrono>
#include <thread>
using namespace std::chrono;
#include <iomanip>

int main()
{
	srand(time(NULL));
	Heap heap;
	Heap dodatak;


	cout << "Moguce opcije su:" << endl
		<< "1.Stvaranje novog hipa reda m" << endl
		<< "2.Dodavanje elementa u hip" << endl
		<< "3.Dohvatanje minimalnog elementa hipa" << endl
		<< "4.Brisanje minimalnog elementa hipa" << endl
		<< "5.Pretvaranje hipa u hip zadatog novog reda" << endl
		<< "6.Dodavanje jednog hipa drugom" << endl
		<< "7.Ispis hipa u obliku m-arnog stabla" << endl
		<< "8.Brisanje hipa" << endl
		<< "9.Brisanje proizvoljnog kljuca" << endl
		<< "10.Prelazak na glavnu funkciju" << endl;

	while (true)
	{
		int opcija;

		cout << "Unesite zeljenu opciju:";
		cin >> opcija;
		if (opcija == 10)break;
		switch (opcija)
		{
		case 1:
		{
			if (heap.dohvati_heap() != nullptr) {
				cout << "Morate prvo obrisati heap!" << endl;
			}
			else
			{
				int m;
				cout << "Unesite red kog biste zeleli da heap bude:";
				cin >> m;
				heap.init(m);
			}
		}
		break;
		case 2:
		{
			int nacin;
			cout << "Unesite na koji biste nacin zeleli da "
				<< "unesete podatak(1 - Standardan unos, 2 - Datoteka, 3 - Slucajna vrednsot) :";
			cin >> nacin;
			switch (nacin)
			{
			case 1:
			{
				int broj;
				int koraci = 0;
				cout << "Unesite broj:";
				cin >> broj;
				heap.add(broj, koraci);
				cout << "Broj koraka : " << koraci << endl;
			}
			break;
			case 2:
			{
				string datoteka;
				int koraci = 0;
				cout << "Unesite ime datoteke:";
				ifstream dat;
				cin >> datoteka;
				dat.open(datoteka);
				int broj;
				dat >> broj;
				heap.add(broj, koraci);
				cout << "Broj koraka : " << koraci << endl;
			}
			break;
			case 3:
			{
				int broj = rand() % 100;
				int koraci = 0;
				heap.add(broj, koraci);
				cout << "Broj koraka : " << koraci << endl;
			}
			break;
			default:
				cout << "Pogresan nacin ste uneli!" << endl;
			}
		}
		break;
		case 3:
		{
			int broj = heap.get();
			if (broj != -1)
			{
				cout << "Broj je " << broj << endl;
			}
			
		}
		break;
		case 4:
		{
			int broj;
			int koraci = 0;
			if (heap.dohvati_heap() == nullptr)
			{
				cout << "Heap nije napravljen" << endl;

			}
			else if (heap.dohvati_trenutni() == 0)
			{
				cout << "Heap je prazan" << endl;
			}
			else
			{
				broj = heap.obrisi(koraci);
				cout << "Minimalan broj je " << broj << " ,a broj koraka je " << koraci << endl;
			}
			
		}
		break;
		case 5:
		{
			cout << "Unesite kog biste reda zeleli da heap bude: ";
			int red;
			cin >> red;
			heap.convertTo(red);
		}
		break;
		case 6:
		{	dodatak.init(2);
			cout << "Unesite broj clanova koliko biste zeleli da dodatni heap ima:";
			int broj_clanova;
			cin >> broj_clanova;
			cout << "Unesite na koji biste nacin zeleli da "
				<< "unesete podatak(1 - Standardan unos, 2 - Datoteka, 3 - Slucajna vrednsot) :";
			int nacin;
			cin >> nacin;
			switch (nacin)
			{
			case 1:
			{
				cout << "Unesite brojeve:";
				for (int i = 0; i < broj_clanova; i++)
				{
					int koraci = 0;
					int broj;
					cin >> broj;
					dodatak.add(broj, koraci);
				}
				int koraci = 0;
				heap.unija(dodatak, koraci);
				cout << "Broj koraka je jednak " << koraci << endl;
			}
			break;
			case 2:
			{
				cout << "Unesite ime datoteke";
				string datoteka;
				cin >> datoteka;
				ifstream dat;
				dat.open(datoteka);
				for (int i = 0; i < broj_clanova; i++)
				{
					int koraci;
					int broj;
					dat >> broj;
					dodatak.add(broj, koraci);
				}
				int koraci = 0;
				heap.unija(dodatak, koraci);
				cout << "Broj koraka je jednak " << koraci << endl;
			}
			break;
			case 3:
			{
				
				for (int i = 0; i < broj_clanova; i++)
				{
					int koraci = 0;
					int broj;
					broj = rand() % 100;
					dodatak.add(broj, koraci);
				}
				int koraci = 0;
				heap.unija(dodatak, koraci);
				cout << "Broj koraka je jednak " << koraci << endl;
			}
			break;
			default:
				cout << "Lose izabran nacin!" << endl;
			}
			dodatak.destroy();

		}
		break;
		case 7:
		{
			cout << heap;
		}
		break;
		case 8:
		{
			heap.destroy();
		}
		break;

		case 9:
		{
			{
				int nacin;
				cout << "Unesite na koji biste nacin zeleli da "
					<< "unesete podatak(1 - Standardan unos, 2 - Datoteka, 3 - Slucajna vrednsot) :";
				cin >> nacin;
				switch (nacin)
				{
				case 1:
				{
					int broj;
					int koraci = 0;
					cout << "Unesite broj:";
					cin >> broj;
					heap.brisanje_zadatog_kljuca(broj, koraci);
					cout << "Broj koraka : " << koraci << endl;
				}
				break;
				case 2:
				{
					string datoteka;
					int koraci = 0;
					cout << "Unesite ime datoteke:";
					ifstream dat;
					cin >> datoteka;
					dat.open(datoteka);
					int broj;
					dat >> broj;
					heap.brisanje_zadatog_kljuca(broj, koraci);
					cout << "Broj koraka : " << koraci << endl;
				}
				break;
				case 3:
				{
					int broj = rand();
					int koraci = 0;
					heap.brisanje_zadatog_kljuca(broj, koraci);
					cout << "Broj koraka : " << koraci << endl;
				}
				break;
				default:
					cout << "Pogresan nacin ste uneli!" << endl;
				}
				break;

			}
			break;


		default:
			cout << "Niste dobro uneli opciju!" << endl;
		}




		}
	}

	cout << endl;
	cout << "Glavna funkcija za testiranje!" << endl;
	cout << "Prioritetni red!" << endl;
	cout << "Moguce opcije:" << endl
		<< "1.Stvaranje reda" << endl
		<< "2.Ispitivanje da li je red prazan" << endl
		<< "3.Dohvatanje prvog elementa reda" << endl
		<< "4.Brisanje (sa dohvatanjem) prvog elementa reda" << endl
		<< "5.Umetanje elementa u red" << endl
		<< "6.Merenje performansi" << endl
		<< "7.Kraj programa" << endl;
	cout << endl;
	Heap prioritetni_red;
	while (true)
	{
		int opcija;
		cout << "Unesite zeljenu opciju:";
		cin >> opcija;
		if (opcija == 7) { break;}
		switch (opcija)
		{
		case 1:
		{
			cout << "Koji nacin unosa zelite (1.Standardni,2.Datoteka,3.Slucajne vrednosti):";
			int nacin;
			cin >> nacin;
			switch (nacin)
			{
			case 1:
			{
				if (prioritetni_red.dohvati_heap() != nullptr) { prioritetni_red.destroy(); }
				int m;
				cout << "Unesite red heapa:";
				cin >> m;
				prioritetni_red.init(m);


			}break;
			case 2:
			{
				if (prioritetni_red.dohvati_heap() != nullptr) {
					prioritetni_red.destroy();
				}
				int m;
				fstream dat;
				cout << "Uneste ime datoteke:";
				string datoteka;
				cin >> datoteka;
				dat.open(datoteka);
				dat >> m;

			}break;
			case 3:
			{
				if (prioritetni_red.dohvati_heap() != nullptr) {
					prioritetni_red.destroy();
				}

					int m = (rand() % 10) + 1;
					prioritetni_red.init(m);
				}break;
			default:
				cout << "Niste dobro uneli nacin!" << endl;
				break;
			}

			

		}break;

		case 2:
		{
			if (prioritetni_red.dohvati_heap() == nullptr)
			{
				cout << "Red nije stvoren" << endl;
			}
			else if (prioritetni_red.dohvati_trenutni() == 0)
			{
				cout << "Red je prazan" << endl;
			}
			else
			{
				cout << "Red nije prazan" << endl;
			}
		}
		break;

		case 3:
		{
			if (prioritetni_red.dohvati_heap() == nullptr)
			{
				cout << "Red nije stvoren" << endl;
			}
			else if (prioritetni_red.dohvati_trenutni() == 0)
			{
				cout << "Red je prazan" << endl;
			}
			else
			{
				cout << "Prvi element reda je " << prioritetni_red.get() << endl;
			}
		}
		break;

		case 4:
		{
			if (prioritetni_red.dohvati_heap() == nullptr)
			{
				cout << "Red nije stvoren" << endl;
			}
			else if (prioritetni_red.dohvati_trenutni() == 0)
			{
				cout << "Red je prazan" << endl;
			}
			else
			{
				int koraci=0;
				cout << "Prvi element reda je " << prioritetni_red.obrisi(koraci) << 
					" a broj koraka je jednak " << koraci<<endl;
			}


		}
		break;

		case 5:

		{
			cout << "Koji nacin unosa zelite (1.Standardni,2.Datoteka,3.Slucajne vrednosti):";
			int nacin;
			cin >> nacin;
			switch (nacin)
			{
			case 1:
			{
			
				int m;
				cout << "Unesite element";
				cin >> m;
				int koraci = 0;
				prioritetni_red.add(m,koraci);
				cout << "Broj koraka je jednak " << koraci << endl;


			}break;
			case 2:
			{
				
				int m;
				fstream dat;
				cout << "Uneste ime datoteke:";
				string datoteka;
				cin >> datoteka;
				dat.open(datoteka);
				dat >> m;
				int koraci = 0;
				prioritetni_red.add(m, koraci);
				cout << "Broj koraka je jednak " << koraci << endl;

			}break;
			case 3:
			{
				

					int m = (rand() % 100);
					int koraci = 0;
					prioritetni_red.add(m, koraci);
					cout << "Broj koraka je jednak " << koraci << endl;
			}break;
			default:
				cout << "Niste dobro uneli nacin!" << endl;
				break;
			}

			}
		
		
		break;
	
		case 6:
		{
			cout << "Performanse!" << endl;
			cout << endl;
			prioritetni_red.destroy();
			cout << "Velicina skupa i red\tVreme umetanja\tBroj koraka umetanje\tVreme izbacivanja\tBroj koraka izbacivanje" << endl;
			for (int i = 0; i < 12; i++)
			{
				int m;
				
				switch (i % 3)
				{
				case 0:
					m = 2;
					
					break;
				case 1:
					m = 4;
					
					break;
				case 2:
					m = 8;
					
					break;
				}
				prioritetni_red.init(m);
				switch (i/3)
				{
				case 0:
					
				{	
					cout << 100 << "," << m;
					for (int i = 0; i < 15; i++)
					{
						cout << " ";
					}
					
					cout <<"\t";
						fstream dat;
						dat.open("test_100.txt");
						int koraci = 0;
						auto start = high_resolution_clock::now();
						int& g = koraci;
						
						for (int i = 0; i < 100; i++)
						{
							int elem;
							dat >> elem;
							prioritetni_red.add(elem, g);
						}
						auto end = high_resolution_clock::now();
						duration<double, std::milli> time_ellapsed_ms = end - start;
						cout << setw(11) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
						cout << setw(20) << setfill(' ')<<koraci << "\t";
						koraci = 0;
						
						start = high_resolution_clock::now();
						
						for (int i = 0; i < 100; i++)
						{
							prioritetni_red.obrisi(g);
						}
						end = high_resolution_clock::now();
						time_ellapsed_ms = end - start;
						cout << setw(14) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
						cout << koraci;
						cout << endl;
					}
						break;
				case 1:
					{
					cout << 1000 << "," << m;
					for (int i = 0; i < 14; i++)
					{
						cout << " ";
					}
					cout << "\t";
					fstream dat;
					dat.open("test_1000.txt");
					int koraci = 0;
					auto start = high_resolution_clock::now();
					
					for (int i = 0; i < 1000; i++)
					{
						int elem;
						dat >> elem;
						prioritetni_red.add(elem, koraci);
					}
					auto end = high_resolution_clock::now();
					duration<double, std::milli> time_ellapsed_ms = end - start;
					cout << setw(11) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
					cout << setw(20) << setfill(' ') << koraci << "\t";
					koraci = 0;
					start = high_resolution_clock::now();
					
					for (int i = 0; i < 1000; i++)
					{
						prioritetni_red.obrisi(koraci);
					}
					end = high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					cout << setw(14) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
					cout << koraci;
					cout << endl;

					}
					break;
				case 2:
					{
					cout << 10000 << "," << m;
					for (int i = 0; i < 13; i++)
					{
						cout << " ";
					}
					cout << "\t";
					fstream dat;
					dat.open("test_10000.txt");
					int koraci = 0;
					auto start = high_resolution_clock::now();
					
					for (int i = 0; i < 10000; i++)
					{
						int elem;
						dat >> elem;
						prioritetni_red.add(elem, koraci);
					}
					auto end = high_resolution_clock::now();
					duration<double, std::milli> time_ellapsed_ms = end - start;
					cout << setw(11) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
					cout << setw(20) << setfill(' ') << koraci << "\t";
					koraci = 0;
					start = high_resolution_clock::now();
					
					for (int i = 0; i < 10000; i++)
					{
						prioritetni_red.obrisi(koraci);
					}
					end = high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					cout << setw(14) << setfill(' ')<< time_ellapsed_ms.count() << " ms \t";
					cout << koraci;
					cout << endl;

					}
					break;
				case 3:
					{
					cout << 100000 << "," << m;
					for (int i = 0; i < 12; i++)
					{
						cout << " ";
					}
					cout << "\t";
					fstream dat;
					dat.open("test_100000.txt");
					int koraci = 0;
					auto start = high_resolution_clock::now();
					
					for (int i = 0; i < 100000; i++)
					{
						int elem;
						dat >> elem;
						prioritetni_red.add(elem, koraci);
					}
					auto end = high_resolution_clock::now();
					duration<double, std::milli> time_ellapsed_ms = end - start;
					cout << setw(11) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
					cout << setw(20) << setfill(' ') << koraci << "\t";
					koraci = 0;
					start = high_resolution_clock::now();
					
					for (int i = 0; i < 100000; i++)
					{
						prioritetni_red.obrisi(koraci);
					}
					end = high_resolution_clock::now();
					time_ellapsed_ms = end - start;
					cout << setw(14) << setfill(' ') << time_ellapsed_ms.count() << " ms \t";
					cout << koraci;
					cout << endl;

					}
					break;

				}
			}




		}break;

		default:
			cout << "Lose uneta opcija!" << endl;
			

		}




	}
	cout << endl;
	cout << "KRAJ PROGRAMA" << endl;
	return 1;
}




