#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include "Paciente.h"
#include <string>

using namespace std;

struct NodoDecision {
    string preguntaAtributo; // Condición lógica evaluada
    string servicio;        // Si es hoja, contiene el servicio asignado
    NodoDecision* izquierdo; // Ruta Sí / Verdadero
    NodoDecision* derecho;   // Ruta No / Falso

    NodoDecision(string serv = "") : servicio(serv), izquierdo(nullptr), derecho(nullptr) {}
};

class DecisionTree {
private:
    NodoDecision* raiz;
    void destruirArbol(NodoDecision* nodo);

public:
    DecisionTree();
    ~DecisionTree();
    void construirArbol();
    string evaluarPaciente(const Paciente& p, string& rutaLog) const;
};

#endif