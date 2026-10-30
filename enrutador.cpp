#include "Enrutador.h"
#include <iostream>

using namespace std;

Enrutador::Enrutador() : nombre("") {}

Enrutador::Enrutador(const string& nombre) : nombre(nombre) {}

string Enrutador::getNombre() const {
    return nombre;
}

bool Enrutador::agregarVecino(const string& vecino, int costo) {
    if (vecino == nombre || costo <= 0 || esVecino(vecino)) {
        return false;
    }
    vecinos[vecino] = costo;
    return true;
}

bool Enrutador::eliminarVecino(const string& vecino) {
    return vecinos.erase(vecino) > 0;
}

bool Enrutador::esVecino(const string& vecino) const {
    return vecinos.find(vecino) != vecinos.end();
}

const std::map<string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

void Enrutador::limpiarTabla() {
    tablaCostos.clear();
    siguiente.clear();
}

void Enrutador::actualizarCosto(const string& destino, int costo, const string& salto) {
    tablaCostos[destino] = costo;
    siguiente[destino] = salto;
}

int Enrutador::getCosto(const string& destino) const {
    auto it = tablaCostos.find(destino);
    if (it == tablaCostos.end()) {
        return -1;
    }
    return it->second;
}

void Enrutador::imprimir() const {
    cout << "Enrutador " << nombre << "\n  Vecinos: ";
    if (vecinos.empty()) {
        cout << "ninguno";
    }
    for (const auto& v : vecinos) {
        cout << v.first << "(" << v.second << ") ";
    }
    cout << "\n  Destino  Costo  Siguiente salto\n";
    for (const auto& t : tablaCostos) {
        cout << "    " << t.first << "      ";
        if (t.second < 0) {
            cout << "-      sin ruta\n";
        } else {
            cout << t.second << "      " << siguiente.at(t.first) << "\n";
        }
    }
}