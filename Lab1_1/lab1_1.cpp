#include <iostream> 
#include <cstdlib> 
#include <math.h> 
#include <complex>
#include <utility>
#include "lab1_1.h"

using namespace std;

float calculateDelta(float a, float b, float c)
{
	float delta;
	delta = b*b - 4.0 * a*c;
	int temp = (int) delta * 1000;
	return (float) temp / 1000;
}

int quadraticFunction(float a, float b, float c, Complex &x1, Complex &x2) {
	//{	0,	0,	0	}
	if (a == 0 && b == 0 && c == 0) {
		return 3; // liczby rzeczywiste
	}
	//{	0,	0,	+/-	}
	if (a == 0 && b == 0 && c != 0) {
		return -1; // brak rozwi¹zañ
	}
	
	//{	0,	+/-,	+/-	}
	if (a == 0 && b != 0 && c != 0) {
		x1 = -1 * c / b;
		return 1; //jedno
	}

	//{	0,	+/-,	0	}
	if (a == 0 && b != 0 && c == 0) {
		x1 = 0;
		return 1; //jedno
	}

	if (b == 0) {
		//{	+/-,	0,	0	}
		if (c == 0) {
			x1 = 0;
			return 1;
		}

		//{	+/-,	0,	+/-	}
		if ((-1.0 * c / a) >= 0) {
			x1 = sqrt(-1.0 * c / a);
			x2 = -sqrt(-1.0 * c / a);
			return 2;
		}
		else {
			return -1;
		}
	}
	if (a != 0) {
		//{	+/-,	+/-,	0	}
		if (c == 0) {
			x1 = 0;
			x2 = -1.0 * b / a;
			return 2;
		}
		//{	+/-,	+/-,	+/-	}
		float delta = calculateDelta(a, b, c);
		if (delta > 0) {
			x1 = (-b - sqrt(delta)) / (2 * a);
			x2 = (-b + sqrt(delta)) / (2 * a);
			return 2; //dwa
		}
		if (delta == 0) {
			x1 = -b / (2.0 * a);
			return 1; //jedno
		}
		if (delta < 0) {
			Complex root = sqrt((Complex)delta);
			x1 = (-b - root) / (a*2);
			x2 = (-b + root) / (a*2);
			return 0; //brak rozwi¹zañ rzeczywistych - 2 urojone
		}
	}
	return -2;
}

int main()
{
	setlocale(LC_ALL, "");

	float a, b, c;
	for (;;) {
		system("cls");
		cout << "podaj a:" << endl;
		cin >> a;
		cout << "podaj b:" << endl;
		cin >> b;
		cout << "podaj c:" << endl;
		cin >> c;

		Complex x1 = 0, x2 = 0;

		int results = quadraticFunction(a, b, c, x1, x2);

		switch (results) {
		case -1: {
			cout << "Równanie sprzeczne" << endl;
			break;
		}
		case 0: {
			cout << "Brak rozwi¹zañ rzeczywistych" << endl
				<< "Dwa rozwi¹zania wykorzystuj¹ce jednostkê urojon¹:" << endl
				<< "x1 = " << x1.real() << x1.imag() << "i" << endl
				<< "x2 = " << x2.real() << "+" << x2.imag() << "i" << endl;
			break;
		}
		case 1: {
			cout << "Jedno rozwi¹zanie" << endl
				<< "x1 = " << x1.real() << endl;
			break;
		}
		case 2: {
			cout << "Dwa rozwi¹zania: " << endl
				<< "x1 = " << x1.real() << endl
				<< "x2 = " << x2.real() << endl;
			break;
		}
		case 3: {
			cout << "Rozwi¹zaniami s¹ wszystkie liczby rzeczywiste" << endl;
			break;
		}
		default: {
			cout << "Wyst¹pi³ nieoczekiwany b³¹d" << endl;
		}
		}

		system("pause");
	}
	return 0;
}


