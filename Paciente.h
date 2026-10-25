#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

using namespace std;

struct Paciente {
    string id;
    string nombre;
    int edad;
    double temperatura;
    double presionArterial;
    int dolor;
    string tipoDolor;
    int trauma;
    int sintomasNeurologicos;
    int requiereCirugia;
    int diasHospitalizacion;
    string servicioAsignado; // Se llenará con el árbol de decisión

    // Constructor por defecto
    Paciente();
};

#endif