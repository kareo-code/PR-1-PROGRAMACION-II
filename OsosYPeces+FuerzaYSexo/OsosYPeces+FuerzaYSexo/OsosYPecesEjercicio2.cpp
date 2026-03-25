#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 12; // al no indicarse en la practica se ha decidido que el array del rio sea un 12 x 12

// -------------------- CLASE BASE --------------------
class Animal {
public:
    bool sexo;
    int fuerza;

    Animal() {
        sexo = rand() % 2;          // 0 o 1 aleatorio
        fuerza = 1 + rand() % 100;  // fuerza entre 1 y 100
        }

    virtual char getSymbol() = 0; // símbolo del animal
    virtual ~Animal() {}
};

// -------------------- CLASE OSO --------------------
class Oso : public Animal {
public:
    char getSymbol() { return 'O'; } // se le establece al animal un símbolo
};

// -------------------- CLASE PEZ --------------------
class Pez : public Animal {
public:
    char getSymbol() { return 'P'; } // se le establece al animal un símbolo
};

// -------------------- CLASE RIO --------------------
class Rio {
private:
    Animal* grid[SIZE][SIZE];

public:
    Rio() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                grid[i][j] = NULL; //se llena el array entero de NULL
    }

    ~Rio() {
        // destructor
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                delete grid[i][j];
    }

    // colocar animal en celda vacía aleatoria
    void colocarAleatorio(Animal* a) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (grid[x][y] != NULL);
        grid[x][y] = a;
    }

    // inicializar río con osos y peces
    // al no especificar el número de osos y peces, se ha decidido, 10 osos y 20 peces
    void inicializar() {
        for (int i = 0; i < 10; i++)
            colocarAleatorio(new Oso());
        for (int i = 0; i < 20; i++)
            colocarAleatorio(new Pez());
    }

    // imprimir el río en formato tabla
    void imprimir() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                cout << "+-";
            cout << "+" << endl;

            for (int j = 0; j < SIZE; j++) {
                cout << "|";
                if (grid[i][j] == NULL)
                    cout << " ";
                else
                    cout << grid[i][j]->getSymbol();
            }
            cout << "|" << endl;
        }

        for (int j = 0; j < SIZE; j++)
            cout << "+-";
        cout << "+" << endl;
    }

    // mover animales
    void mover() {
        Animal* nuevo[SIZE][SIZE];

        // inicializar nuevo a NULL
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                nuevo[i][j] = NULL;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (grid[i][j] == NULL) continue;

                int dir = rand() % 5; // 0-arriba,1-abajo,2-izquierda,3-derecha,4-quedarse
                int ni = i, nj = j;

                // se comprueban los bordes antes de mover
                if (dir == 0 && i > 0) ni--;
                else if (dir == 1 && i < SIZE - 1) ni++;
                else if (dir == 2 && j > 0) nj--;
                else if (dir == 3 && j < SIZE - 1) nj++;

                if (nuevo[ni][nj] == NULL) {
                    nuevo[ni][nj] = grid[i][j];
                }
                else {
                    char simbActual = grid[i][j]->getSymbol();
                    char simbNuevo = nuevo[ni][nj]->getSymbol();

                    if (simbActual == simbNuevo) {
                        // misma especie
                        if (grid[i][j]->sexo != nuevo[ni][nj]->sexo) {
                            // distinto sexo -> reproducción
                            if (simbActual == 'O') colocarAleatorio(new Oso());
                            else colocarAleatorio(new Pez());

                            // el animal actual intenta quedarse en su sitio
                            if (nuevo[i][j] == NULL)
                                nuevo[i][j] = grid[i][j];
                        }
                        else {
                            // mismo sexo -> pelea por fuerza
                            if (grid[i][j]->fuerza > nuevo[ni][nj]->fuerza) {
                                delete nuevo[ni][nj];       // muere el que estaba
                                nuevo[ni][nj] = grid[i][j]; // gana el actual
                            }
                            else {
                                delete grid[i][j];          // muere el actual
                            }
                        }
                    }
                    else {
                        // oso vs pez
                        if (simbActual == 'O') {
                            delete nuevo[ni][nj]; // muere pez
                            nuevo[ni][nj] = grid[i][j];
                        }
                        else {
                            delete grid[i][j]; // muere pez
                        }
                    }
                }
            }
        }

        // copiar nuevo a grid
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                grid[i][j] = nuevo[i][j];
    }
};

// -------------------- MAIN --------------------
int main() {
    srand(time(NULL));

    Rio rio;
    rio.inicializar();

    for (int i = 0; i < 15; i++) { // al no especificar se ha decidido hacer 15 pasos de tiempo
        cout << "Paso " << i + 1 << endl;
        rio.imprimir();
        rio.mover();
    }

    return 0;
}