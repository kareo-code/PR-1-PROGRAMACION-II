// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

void duplicar(int* x) {
	*x = *x * 2;

}

void cambiar(int** x, int* y) {
	*x = y;

}

void referencias(int& a,int& b) {
	int itemp = b;
	b = a;
	a = itemp;

}

int main()
{
	//puntero
	int num = 10;
	int num2 = 40;

	int *punt = &num;

	cout << *punt << endl;

	duplicar(&num);

	cout << *punt << endl;

	//puntero de puntero
	cambiar(&punt, &num2);

	cout << *punt << endl;

	//referencias
	int x = 50;
    int y = 100;

	cout << x <<" "<< y << endl;

	referencias(x, y);

	cout << x << " " << y << endl;
}


