#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Queue.h"
#include "DecisionTree.h"
#include "AVLTree.h"
#include <string>

using namespace std;

class Hospital {
private:
    Queue colaPacientes;
    DecisionTree arbolDecision;
    
    AVLTree avlUrgencias;
    AVLTree avlMedicinaGeneral;
    AVLTree avlCardiologia;
    AVLTree avlNeurologia;
    AVLTree avlTraumatologia;
    AVLTree avlCirugia;
    AVLTree avlPediatria;
    AVLTree avlHospitalizacion;

public:
    Hospital();
    void cargarPacientesDesdeArchivo(const string& nombreArchivo);
    void atenderSiguientePaciente();
    void verDepartamentos() const;
    void buscarPaciente() const;
};

#endif