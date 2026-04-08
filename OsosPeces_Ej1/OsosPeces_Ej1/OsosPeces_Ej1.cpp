
#include "Animales.h"

using namespace std;



// -------------------- MAIN --------------------
int main() {
    srand(time(NULL));

    Rio rio;
    rio.inicializar();

    for (int i = 0; i < 15; i++) { // al no especificar se ha decidido hacer 15 pasos de tiempo
        cout << "Paso " << i + 1 << endl;
        rio.imprimir();
        rio.imprimirDetalle(); // <-- detalle opcional
        rio.mover();
    }

    return 0;
}