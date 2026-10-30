#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
using namespace std;

class Enrutador {
private:
    string nombre;                            // identificador
    map<string, int> vecinos;            // vecino -> costo del enlace
    map<string, int> tablaCostos;        // destino -> costo (-1 = sin ruta)
    map<string, string> siguiente;  // destino -> siguiente salto

public:
    Enrutador();
    explicit Enrutador(const string& nombre);

    string getNombre() const;

    // Vecinos directamente conectados
    bool agregarVecino(const string& vecino, int costo);
    bool eliminarVecino(const string& vecino);
    bool esVecino(const string& vecino) const;
    const map<string, int>& getVecinos() const;

    // Tabla de costos (la actualiza la Red)
    void limpiarTabla();
    void actualizarCosto(const string& destino, int costo, const string& salto);
    int getCosto(const string& destino) const;

    void imprimir() const;
};

#endif