#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#define L_KOSTEK 6000
#define L_UDERZEN 100
#define L_OCZEK 6
#define OPOZNIENIE 1000
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
	cout << "\nLiczba kostek: \t" << L_KOSTEK;
	cout << "\nLiczba oczek(max): \t" << L_OCZEK;
	cout << "\nLiczba uderzen: \t" << L_UDERZEN;
	int kostki[L_KOSTEK];
	int oczka[L_OCZEK];

	//ustawianie max wartosci oczek na akzdej kostce
	for (int i = 0; i < L_KOSTEK; i++)
	{
		kostki[i] = L_OCZEK;
	}
	for (int i = 0; i < L_OCZEK; i++) {
		oczka[i] = 0;
	}
	oczka[L_OCZEK-1] = L_KOSTEK;
	wyswietlWyniki(0, oczka);

	for (int nrUderzenia = 0; nrUderzenia < L_UDERZEN; nrUderzenia++)
	{
		for (int i = 0; i < L_OCZEK; i++) {
			oczka[i] = 0;
		}
		for (int nrKostki = 0; nrKostki < L_KOSTEK; nrKostki++)
		{
			if (!(rand() % 20))
			{
				kostki[nrKostki] = rand() % L_OCZEK + 1;
			}
		}
		for (int i = 0; i < L_KOSTEK; i++) {
			oczka[kostki[i] - 1]++;
		}
		
		wyswietlWyniki(nrUderzenia, oczka);
		sleepcp(OPOZNIENIE);
	}
	cout << "\n";
#ifdef WIN32
	getchar();
#endif // WIN32

	return 0;
}

void sleepcp(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif // win32
}

double calculate(int ilosc) {
	if (ilosc) {
		//return ilosc * (log(ilosc) - 1.0) + 0, 5 * log(2.0* M_PI* ilosc);
		return log(ilosc) * (ilosc + 1.0 / 2.0) + ((log(2) + log(M_PI)) / 2) - ilosc;
	}
	else {
		return 0;
	}
}

double entropia(int oczka[]) {
	//double result = calculate(L_KOSTEK);
	double result = log(L_KOSTEK) * (L_KOSTEK + 1.0 / 2.0) - L_KOSTEK + ((log(2) + log(M_PI)) / 2);

	for (int i = 0; i < L_OCZEK; i++) {
		result -= calculate(oczka[i]);
	}
	return result;
}

void wyswietlWyniki(int nrUderzenia, int oczka[]) {
	int temp = 0;
	cout << "\n=====Wyniki=====";
	cout << "\nIteracja: " << nrUderzenia + 1;
	for (int i = 0; i < L_OCZEK; i++) {
		cout << "\t\t" << i + 1 << ": " << oczka[i];
		temp += oczka[i];
	}
	cout << "\t\tEntropia: " << entropia(oczka) << "\n";
}


