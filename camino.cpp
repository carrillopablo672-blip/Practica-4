#include "Camino.h"
#include <iostream>

using namespace std;



Camino::Camino() : costo(-1) {}

void Camino::agregarAlInicio(const std::string& nodo) {
    nodos.push_front(nodo);
}

void Camino::setCosto(int c) {
    costo = c;
}

int Camino::getCosto() const {
    return costo;
}

bool Camino::existe() const {
    return !nodos.empty();
}

void Camino::imprimir() const {
    if (!existe()) {
        std::cout << "No existe camino\n";
        return;
    }
    std::cout << "Camino: ";
    for (const std::string& n : nodos) {
        std::cout << n;
        if (n != nodos.back()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\nCosto: " << costo << "\n";
}