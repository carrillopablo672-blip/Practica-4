#include <iostream>
#include <string>
#include "Red.h"

using namespace std;

int main() {
    Red red;
    int opcion;
    string a, b;
    int costo;

    do {
        cout << "\n1. Agregar enrutador\n"
                  << "2. Eliminar enrutador\n"
                  << "3. Agregar enlace\n"
                  << "4. Eliminar enlace\n"
                  << "5. Mostrar red y tablas\n"
                  << "6. Cargar red desde archivo\n"
                  << "7. Calcular camino\n"
                  << "0. Salir\n"
                  << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Nombre: ";
            cin >> a;
            cout << (red.agregarEnrutador(a) ? "Agregado\n" : "Ya existe\n");
        } else if (opcion == 2) {
            cout << "Nombre: ";
            cin >> a;
            cout << (red.eliminarEnrutador(a) ? "Eliminado\n" : "No existe\n");
        } else if (opcion == 3) {
            cout << "Enrutador 1, enrutador 2 y costo: ";
            cin >> a >> b >> costo;
            if (!red.existeEnrutador(a) || !red.existeEnrutador(b)) {
                cout << "Primero agregue los enrutadores con la opcion 1\n";
            } else if (red.agregarEnlace(a, b, costo)) {
                cout << "Enlace agregado\n";
            } else {
                cout << "El enlace ya existe o el costo no es mayor que 0\n";
            }
        } else if (opcion == 4) {
            cout << "Enrutador 1 y enrutador 2: ";
            cin >> a >> b;
            cout << (red.eliminarEnlace(a, b) ? "Enlace eliminado\n" : "No existe ese enlace\n");
        } else if (opcion == 5) {
            red.imprimir();
        } else if (opcion == 6) {
            cout << "Nombre del archivo: ";
            cin >> a;
            cout << (red.cargarArchivo(a) ? "Red cargada\n" : "No se pudo abrir el archivo\n");
        } else if (opcion == 7) {
            cout << "Origen y destino: ";
            cin >> a >> b;
            if (!red.existeEnrutador(a) || !red.existeEnrutador(b)) {
                cout << "Alguno de los enrutadores no existe\n";
            } else {
                red.calcularCamino(a, b).imprimir();
            }
        }
    } while (opcion != 0);

    return 0;
}