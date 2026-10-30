#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "Enrutador.h"
#include "Camino.h"

using namespace std;

class Red {
private:
    map<string, Enrutador> enrutadores;   // nombre -> enrutador

    // Dijkstra: calcula el menor costo desde 'origen' a todos los demas
    // y guarda en 'previo' de que enrutador se llega a cada uno
    map<string, int> dijkstra(const string& origen, map<string, string>& previo) const;

public:
    // Enrutadores
    bool agregarEnrutador(const string& nombre);

    bool eliminarEnrutador(const string& nombre);

    bool existeEnrutador(const string& nombre) const;

    // Enlaces (bidireccionales)

    bool agregarEnlace(const string& a, const string& b, int costo);

    bool eliminarEnlace(const string& a, const string& b);

    // Archivo
    bool cargarArchivo(const string& ruta);

    // Costos y caminos
    Camino calcularCamino(const string& origen, const string& destino) const;

    void actualizarTablas();

    void imprimir() const;
};

#endif