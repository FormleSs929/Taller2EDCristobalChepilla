#include "DecisionTree.h"

DecisionTree::DecisionTree() {
    raiz = nullptr;
    construirArbol();
}

DecisionTree::~DecisionTree() {
    destruirArbol(raiz);
}

void DecisionTree::destruirArbol(NodoDecision* nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->derecho);
        delete nodo;
    }
}

void DecisionTree::construirArbol() {
    raiz = new NodoDecision();
    raiz->preguntaAtributo = "Edad < 14";
    
    // Izquierda (Sí -> Pediatría)[cite: 3]
    raiz->izquierdo = new NodoDecision("Pediatria");
    
    // Derecha (No -> Evaluar Trauma)[cite: 3]
    raiz->derecho = new NodoDecision();
    raiz->derecho->preguntaAtributo = "Trauma == 1";
    
    // Trauma == 1 (Sí -> Evaluar Cirugía)[cite: 3]
    raiz->derecho->izquierdo = new NodoDecision();
    raiz->derecho->izquierdo->preguntaAtributo = "RequiereCirugia == 1";
    raiz->derecho->izquierdo->izquierdo = new NodoDecision("Cirugia");       // Sí -> Cirugía[cite: 3]
    raiz->derecho->izquierdo->derecho = new NodoDecision("Traumatologia");   // No -> Traumatología[cite: 3]
    
    // Trauma != 1 (No -> Evaluar Síntomas Neurológicos)[cite: 3]
    raiz->derecho->derecho = new NodoDecision();
    raiz->derecho->derecho->preguntaAtributo = "SintomasNeurologicos == 1";
    raiz->derecho->derecho->izquierdo = new NodoDecision("Neurologia");      // Sí -> Neurología[cite: 3]
    
    // Sin síntomas neurológicos -> Evaluar TipoDolor == pecho[cite: 3]
    raiz->derecho->derecho->derecho = new NodoDecision();
    raiz->derecho->derecho->derecho->preguntaAtributo = "TipoDolor == pecho";
    raiz->derecho->derecho->derecho->izquierdo = new NodoDecision("Cardiologia"); // Sí -> Cardiología[cite: 3]
    
    // TipoDolor != pecho -> Evaluar Temperatura alta o Dolor intenso[cite: 3]
    raiz->derecho->derecho->derecho->derecho = new NodoDecision();
    raiz->derecho->derecho->derecho->derecho->preguntaAtributo = "Temperatura > 38.5 o Dolor >= 8";
    raiz->derecho->derecho->derecho->derecho->izquierdo = new NodoDecision("Urgencias"); // Sí -> Urgencias[cite: 3]
    
    // Temperatura normal y Dolor bajo -> Evaluar Días de Hospitalización >= 2[cite: 3]
    raiz->derecho->derecho->derecho->derecho->derecho = new NodoDecision();
    raiz->derecho->derecho->derecho->derecho->derecho->preguntaAtributo = "DiasHospitalizacion >= 2";
    raiz->derecho->derecho->derecho->derecho->derecho->izquierdo = new NodoDecision("Hospitalizacion"); // Sí -> Hospitalización[cite: 3]
    raiz->derecho->derecho->derecho->derecho->derecho->derecho = new NodoDecision("Medicina General");   // No -> Medicina General[cite: 3]
}

string DecisionTree::evaluarPaciente(const Paciente& p, string& rutaLog) const {
    NodoDecision* actual = raiz;
    rutaLog = "";

    while (actual != nullptr) {
        if (!actual->servicio.empty()) {
            return actual->servicio;
        }

        bool condicion = false;
        if (actual->preguntaAtributo == "Edad < 14") {
            condicion = (p.edad < 14);
            rutaLog += (condicion ? "Edad < 14 -> " : "Edad >= 14 -> ");
        } else if (actual->preguntaAtributo == "Trauma == 1") {
            condicion = (p.trauma == 1);
            rutaLog += (condicion ? "Trauma == 1 -> " : "Trauma != 1 -> ");
        } else if (actual->preguntaAtributo == "RequiereCirugia == 1") {
            condicion = (p.requiereCirugia == 1);
            rutaLog += (condicion ? "RequiereCirugia == 1 -> " : "RequiereCirugia != 1 -> ");
        } else if (actual->preguntaAtributo == "SintomasNeurologicos == 1") {
            condicion = (p.sintomasNeurologicos == 1);
            rutaLog += (condicion ? "SintomasNeurologicos == 1 -> " : "SintomasNeurologicos != 1 -> ");
        } else if (actual->preguntaAtributo == "TipoDolor == pecho") {
            condicion = (p.tipoDolor == "pecho");
            rutaLog += (condicion ? "TipoDolor == pecho -> " : "TipoDolor != pecho -> ");
        } else if (actual->preguntaAtributo == "Temperatura > 38.5 o Dolor >= 8") {
            condicion = (p.temperatura > 38.5 || p.dolor >= 8);
            rutaLog += (condicion ? "Temp > 38.5 o Dolor >= 8 -> " : "Temp <= 38.5 y Dolor < 8 -> ");
        } else if (actual->preguntaAtributo == "DiasHospitalizacion >= 2") {
            condicion = (p.diasHospitalizacion >= 2);
            rutaLog += (condicion ? "Dias >= 2 -> " : "Dias < 2 -> ");
        }

        if (condicion) {
            actual = actual->izquierdo;
        } else {
            actual = actual->derecho;
        }
    }
    return "Medicina General";
}