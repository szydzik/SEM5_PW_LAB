#include <iostream> 
#include <cstdlib> 
#include <math.h> 
#include "Main.h"

using namespace std;

double calculateDelta(double a, double b, double c)
{
	double delta;
	delta = b*b - 4.0 * a*c;
	return delta;
}

int quadraticFunction(double a, double b, double c, double &x1, double &x2) {
	//{	0,	0,	0	}
	if (a == 0 && b == 0 && c == 0) {
		return 3; // liczby rzeczywiste
	}
	//{	0,	0,	+/-	}
	if (a == 0 && b == 0 && c != 0) {
		return -1; // brak rozwi¹zañ
	}
	//{	0,	+/-,	0	}
	//{	0,	+/-,	+/-	}
	if (a == 0) {
		x1 = -1 * c / b;
		return 1; //jedno
	}

	if (b == 0) {
		//{	+/-,	0,	0	}
		if (c == 0) {
			x1 = 0;
			return 1;
		}
		//{	+,	0,	+	}
		//{	-,	0,	-	}
		if ((a > 0 && c > 0) || (a < 0 && c < 0)) {
			return 3;
		}
		//{	+,	0,	-	}
		//{	-,	0,	+	}
		if ((a > 0 && c < 0) || (a < 0 && c > 0)) {
			x1 = sqrt(c / a);
			x2 = -sqrt(c / a);
			return 2;
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
		int delta = calculateDelta(a, b, c);
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
			return 0; //brak
		}
	}
	return -2;
}

int main()
{
	setlocale(LC_ALL, "");

	double a, b, c;
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
	case -1: {
		cout << "Równanie sprzeczne" << endl;
		break;
	}
	case 0: {
		cout << "Brak rozwi¹zañ rzeczywistych" << endl;
		break;
	}
	case 1: {
		cout << "Jedno rozwi¹zanie" << endl
			<< "x1 = " << x1 << endl;
		break;
	}
	case 2: {
		cout << "Dwa rozwi¹zania: " << endl
			<< "x1 = " << x1 << endl
			<< "x2 = " << x2 << endl;
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
	return 0;
}
