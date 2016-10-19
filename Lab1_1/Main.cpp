#include <iostream> 
#include <cstdlib> 
#include <math.h> 
#include "Main.h"

using namespace std;

int calculateDelta(int a, int b, int c)
{
	int delta;
	delta = b*b - 4 * a*c;
	return delta;
}

int quadraticFunction(int a, int b, int c, double &x1, double &x2) {

	if (a == 0 && b == 0 && c == 0) {
		return -2; // liczby rzeczywiste
	}

	if (a == 0 && b == 0 && c != 0) {
		return -1; // brak rozwi¹zañ
	}

	if (a == 0) {
		x1 = -1 * c / b;
		return 1; //jedno
	}

	if (a != 0) {
		int delta = calculateDelta(a, b, c);
		if (delta > 0) {
			x1 = (-b - sqrt(delta)) / (2 * a);
			x2 = (-b + sqrt(delta)) / (2 * a);
			return 2; //dwa
		}
		if (delta == 0) {
			x1 = -b / (2 * a);
			return 1; //jedno
		}
		if (delta < 0) {
			return 0; //brak
		}
	}

	return -3;
}

int main()
{
	setlocale(LC_ALL, "");

	int a, b, c;
	cout << "podaj a:" << endl;
	cin >> a;
	cout << "podaj b:" << endl;
	cin >> b;
	cout << "podaj c:" << endl;
	cin >> c;

	double x1 = 0;
	double x2 = 0;

	int results = quadraticFunction(a, b, c, x1, x2);


	switch (results) {
		//liczby rzeczywiste
	case -2: {
		cout << "Rozwi¹zaniami s¹ wszystkie liczby rzeczywiste" << endl;
		break;
	}
			 //sprzeczne
	case -1: {
		cout << "Równanie sprzeczne" << endl;
		break;
	}
			 //brak rozwi¹zañ
	case 0: {
		cout << "Brak rozwi¹zañ rzeczywistych" << endl;
		break;
	}
			//jedno
	case 1: {
		cout << "Jedno rozwi¹zanie x1 = " << x1 << endl;
		break;
	}
			//dwa
	case 2: {
		cout << "Dwa rozwi¹zania x1 = " << x1 << ", x2 = " << x2 << endl;
		break;
	}
	default: {
		cout << "Wyst¹pi³ nieoczekiwany b³¹d" << endl;
	}

	}

	system("pause");
	return 0;
}
