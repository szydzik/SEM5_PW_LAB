//kompilacja
//g++ srodowisko.cpp -o build -fopenmp

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32
#include <omp.h>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#define L_KOSTEK 6000
#define L_UDERZEN 100
#define L_OCZEK 6
#define OPOZNIENIE 100
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

void sleepcp(int milliseconds);
double entropia(int oczka[]);
double calculate(int ilosc);
void wyswietlWyniki(int nrUderzenia, int oczka[]);
using namespace std;


int main()
{

	cout << "\n=====Inicjalizacja=====";
	cout << "\nLiczba kostek: \t\t" << L_KOSTEK;
	cout << "\nLiczba oczek(max): \t" << L_OCZEK;
	cout << "\nLiczba uderzen: \t" << L_UDERZEN;
	cout << "\n";
	int kostki[L_KOSTEK];
	int oczka[L_OCZEK];
	time_t czas = clock();
	int nrUderzenia, i, nrKostki;

	//ustawianie max wartosci oczek na kazdej kostce
	int i1;

#pragma omp parallel for shared(kostki) private(i1) default(none)
	for (i1 = 0; i1 < L_KOSTEK; i1++)
	{
		kostki[i1] = L_OCZEK;
	}

#pragma omp parallel for shared(oczka) private(i1) default(none)
	for (i1 = 0; i1 < L_OCZEK; i1++) {
		oczka[i1] = 0;
	}

	oczka[L_OCZEK - 1] = L_KOSTEK;
	wyswietlWyniki(0, oczka);

	for (nrUderzenia = 0; nrUderzenia < L_UDERZEN; nrUderzenia++)
	{
#pragma omp parallel for shared(oczka) private(i) default(none)
		for (i = 0; i < L_OCZEK; i++) {
			oczka[i] = 0;
		}

#pragma omp parallel for shared(kostki) private(nrKostki) default(none)
		for (nrKostki = 0; nrKostki < L_KOSTEK; nrKostki++)
		{
			if (!(rand() % 20))
			{
				kostki[nrKostki] = rand() % L_OCZEK + 1;
			}
		}
//#pragma omp parallel for shared(kostki,oczka) private(i1) default(none)
		for (i1 = 0; i1 < L_KOSTEK; i1++) {
//#pragma omp critical
			oczka[kostki[i1] - 1]++;
		}

		wyswietlWyniki(nrUderzenia + 1, oczka);

		//sleepcp(OPOZNIENIE);
	}

	cout << "\n";
#ifdef WIN32
	czas = clock() - czas;
#else
	czas = (clock() - czas) / 1000;
#endif // WIN32
	cout << "Czas dzialania programu: " << czas << "\n";

#ifdef WIN32
	getchar();
#endif // WIN32

	return 0;
}

void sleepcp(int milliseconds)
{
#ifdef WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif // win32
}

double calculate(int ilosc) {
	if (ilosc) {
		return log(ilosc) * (ilosc + 1.0 / 2.0) + ((log(2) + log(M_PI)) / 2) - ilosc;
	}
	else {
		return 0;
	}
}

double entropia(int oczka[]) {
	double result = log(L_KOSTEK) * (L_KOSTEK + 1.0 / 2.0) - L_KOSTEK + ((log(2) + log(M_PI)) / 2);
	int i;
#pragma omp parallel for shared(oczka) private(i) reduction(- : result) default(none) 
	for (i = 0; i < L_OCZEK; i++) {
		result -= calculate(oczka[i]);
	}
	return result;
}

void wyswietlWyniki(int nrUderzenia, int oczka[]) {
	int temp = 0;
	cout << "\n=====Wyniki=====";
	cout << "\nIteracja: " << nrUderzenia;

	int i = 0;

#pragma omp parallel for shared(oczka,cout) private(i) default(none) reduction(+ : temp)
	for (i = 0; i < L_OCZEK; i++) {
#pragma omp critical
		{
			cout << "\t\t" << i + 1 << ": " << oczka[i];
		}
		temp += oczka[i];
	}
	cout << "\t\tEntropia dla " << temp << " kostek: " << entropia(oczka) << "\n";
}


