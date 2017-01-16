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
double calculateIntegral(double zz, double bl, double bu);
double func(double xx, double yy, double zz);
using namespace std;


int main()
{

	cout << "\n=====Inicjalizacja=====\n";
	double zzi = 0.0;
	double zzk = 100;
	double dzz = zzk / 100.0;
	double results[100];
	double lowerLimit = 0.0, upperLimit = 20.0 * M_PI;
	time_t czas = clock();
	cout << "=====Inicjalizacja zakonczona=====\n";

	//#pragma omp parallel for 
	for (int ii = 0; ii < 100; ii++) {
		zzi = dzz*(ii + 1.0);
		results[ii] = calculateIntegral(zzi, lowerLimit, upperLimit);
		//#pragma omp critical
		cout << ii + 1 << "\t" << results[ii] << endl;
	}


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

double func(double xx, double yy, double zz) {
	double rob, result;
	rob = sin(xx)*sin(yy) / sqrt(zz*zz + xx*xx + yy*yy);
	rob = abs(rob);
	result = rob;
	return result;
}

double calculateIntegral(double zz, double lowerLimit, double upperLimit) {
	double result;
	double xi;
	double yj;
	double sum = 0;
	double dx, dy;

	dx = (upperLimit - lowerLimit) / 2000.0;
	dy = (upperLimit - lowerLimit) / 2000.0;
	xi = 0.0;

	for (int ii = 1; ii <= 2000; ii++) {
		xi = xi + dx;
		yj = 0.0;
		for (int jj = 1; jj <= 2000; jj++) {
			yj = yj + dy;
			sum = sum + func(xi, yj, zz);
		}
	}
	result = sum*dx*dy;
	return result;
}



