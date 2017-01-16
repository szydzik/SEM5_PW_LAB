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

void sleepcp(int milliseconds);
using namespace std;


int main()
{
	cout << "\n=====Inicjalizacja=====";
	time_t czas = clock();
	int id;
	cout << "\n";


#pragma omp parallel num_threads(MAX_NT) private(id) shared(printf)
	{
		id = omp_get_thread_num();
		printf("Watek %d zaczyna prace...\n", id);

		sleepcp((id+1)*2000);

		printf("Watek %d zakonczyl prace i czeka przy barierze, az pozostale watki dotra do bariery...\n", id);
#pragma omp barrier

		printf("Watek %d juz jest poza bariera.\n", id);
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