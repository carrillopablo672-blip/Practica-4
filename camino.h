#ifndef CAMINO_H
#define CAMINO_H

#include <string>
#include <list>
using namespace std;

// Clase auxiliar: guarda la secuencia de enrutadores de un camino y su costo
class Camino {
private:
    list<string> nodos;   // enrutadores en orden, de origen a destino
    int costo;                      // -1 si no hay camino

public:
    Camino();

    void agregarAlInicio(const string& nodo);
    void setCosto(int costo);
    int getCosto() const;
    bool existe() const;

    void imprimir() const;
};

#endif