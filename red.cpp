#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ================= Enrutadores =================

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || existeEnrutador(nombre)) {
        return false;
    }
    enrutadores[nombre] = Enrutador(nombre);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    if (!existeEnrutador(nombre)) {
        return false;
    }
    for (auto& par : enrutadores) {
        par.second.eliminarVecino(nombre);
    }
    enrutadores.erase(nombre);
    actualizarTablas();
    return true;
}

bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

// ---------------------------------------------------------

bool Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (!existeEnrutador(a) || !existeEnrutador(b)) {
        return false;
    }
    if (!enrutadores[a].agregarVecino(b, costo)) {
        return false;
    }
    enrutadores[b].agregarVecino(a, costo);
    actualizarTablas();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    if (!existeEnrutador(a) || !existeEnrutador(b)) {
        return false;
    }
    if (!enrutadores[a].eliminarVecino(b)) {
        return false;
    }
    enrutadores[b].eliminarVecino(a);
    actualizarTablas();
    return true;
}

//----------------------------------------------------
// Formato: cada linea es un enlace "A B 4".
// Una linea con un solo nombre "E" agrega un enrutador sin enlaces.
bool Red::cargarArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }
    enrutadores.clear();

    string linea, a, b;
    int costo;
    while (getline(archivo, linea)) {
        istringstream datos(linea);
        if (!(datos >> a)) {
            continue;                       // linea vacia
        }
        agregarEnrutador(a);
        if (datos >> b >> costo) {
            agregarEnrutador(b);
            agregarEnlace(a, b, costo);
        }
    }
    return true;
}

// --------------------------------------------------------------------

map<string, int> Red::dijkstra(const string& origen, map<string, string>& previo) const {
    const int INF = 1000000000;
    map<string, int> dist;
    map<string, bool> visitado;

    for (const auto& par : enrutadores) {
        dist[par.first] = INF;
        visitado[par.first] = false;
    }
    dist[origen] = 0;

    for (size_t i = 0; i < enrutadores.size(); i++) {
        // 1. Escoger el no visitado con menor distancia
        string actual = "";
        for (const auto& d : dist) {
            if (!visitado[d.first] && (actual == "" || d.second < dist[actual])) {
                actual = d.first;
            }
        }
        if (dist[actual] == INF) {
            break;                          // los que faltan son inalcanzables
        }
        visitado[actual] = true;

        // 2. Ver si pasando por 'actual' se llega mas barato a sus vecinos
        for (const auto& v : enrutadores.at(actual).getVecinos()) {
            int nuevo = dist[actual] + v.second;
            if (nuevo < dist[v.first]) {
                dist[v.first] = nuevo;
                previo[v.first] = actual;
            }
        }
    }

    // Los inalcanzables quedan en -1
    for (auto& d : dist) {
        if (d.second == INF) {
            d.second = -1;
        }
    }
    return dist;
}

Camino Red::calcularCamino(const string& origen, const string& destino) const {
    Camino camino;
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        return camino;
    }

    map<string, string> previo;
    map<string, int> dist = dijkstra(origen, previo);
    if (dist[destino] == -1) {
        return camino;                      // no hay camino
    }

    // Se reconstruye de atras hacia adelante: destino, previo, ..., origen
    string actual = destino;
    while (actual != origen) {
        camino.agregarAlInicio(actual);
        actual = previo[actual];
    }
    camino.agregarAlInicio(origen);
    camino.setCosto(dist[destino]);
    return camino;
}

void Red::actualizarTablas() {
    for (auto& par : enrutadores) {
        const string& origen = par.first;
        Enrutador& r = par.second;

        map<string, string> previo;
        map<string, int> dist = dijkstra(origen, previo);

        r.limpiarTabla();
        for (const auto& d : dist) {
            const string& destino = d.first;
            if (d.second == -1) {
                r.actualizarCosto(destino, -1, "-");
            } else if (destino == origen) {
                r.actualizarCosto(destino, 0, origen);
            } else {
                // Retroceder hasta el primer enrutador despues del origen
                string salto = destino;
                while (previo[salto] != origen) {
                    salto = previo[salto];
                }
                r.actualizarCosto(destino, d.second, salto);
            }
        }
    }
}

void Red::imprimir() const {
    cout << "\n ----- (0*0) ----- Red (" << enrutadores.size() << " enrutadores) ------- (W.W) -----\n";
    for (const auto& par : enrutadores) {
        par.second.imprimir();
    }
}