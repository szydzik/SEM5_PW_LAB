//kompilacja
//g++ lab6_1.cpp -o lab6_1 -fopenmp

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32
#include <omp.h>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#define OPOZNIENIE 100
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

void sleepcp(int milliseconds);
using namespace std;


int main()
{

	cout << "\n=====Inicjalizacja=====";

	cout << "\n";

	time_t czas = clock();


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



