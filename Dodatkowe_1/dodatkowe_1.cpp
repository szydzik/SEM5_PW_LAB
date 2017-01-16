//kompilacja
//g++ dodatkowe_1.cpp -o dodatkowe_1 -fopenmp

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#include <omp.h>

#define MAX_NT 4

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>

time_t calculateTime(time_t czas);
void sleepcp(int milliseconds);
using namespace std;


int main()
{
	cout << "\n=====Inicjalizacja=====";
	time_t czas = clock();
	int id;
	cout << "\n";


#pragma omp parallel num_threads(MAX_NT) private(id)
	{
		id = omp_get_thread_num();
		printf("TIME: %lld \tWatek %d zaczyna prace...\n", (long long) calculateTime(czas), id);

		sleepcp((id+1)*2000);

		printf("TIME: %lld \tWatek %d zakonczyl prace i czeka przy barierze, az pozostale watki dotra do bariery...\n", (long long) calculateTime(czas), id);
#pragma omp barrier

		printf("TIME: %lld \tWatek %d juz jest poza bariera.\n", (long long) calculateTime(czas), id);
	}

	cout << "Czas dzialania programu: " << calculateTime(czas) << "\n";

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

time_t calculateTime(time_t czas) {
#ifdef WIN32
	return clock() - czas;
#else
	return (clock() - czas) / 1000;
#endif // WIN32
}