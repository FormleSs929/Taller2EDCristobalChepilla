#include "AVLTree.h"
#include <iostream>

AVLTree::AVLTree() : raiz(nullptr) {}

AVLTree::~AVLTree() {
    destruir(raiz);
}

void AVLTree::destruir(NodoAVL* nodo) {
    if (nodo != nullptr) {
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }
}

int AVLTree::obtenerAltura(NodoAVL* n) const {
    return (n == nullptr) ? 0 : n->altura;
}

int AVLTree::max(int a, int b) const {
    return (a > b) ? a : b;
}

int AVLTree::obtenerBalance(NodoAVL* n) const {
    if (n == nullptr) return 0;
    return obtenerAltura(n->izquierdo) - obtenerAltura(n->derecho);
}

NodoAVL* AVLTree::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

NodoAVL* AVLTree::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

bool AVLTree::insertar(Paciente p) {
    bool insertado = false;
    raiz = insertar(raiz, p, insertado);
    return insertado;
}

NodoAVL* AVLTree::insertar(NodoAVL* nodo, Paciente p, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(p);
    }

    if (p.id < nodo->paciente.id) {
        nodo->izquierdo = insertar(nodo->izquierdo, p, insertado);
    } else if (p.id > nodo->paciente.id) {
        nodo->derecho = insertar(nodo->derecho, p, insertado);
    } else {
        return nodo; // ID duplicado, no se inserta
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    int balance = obtenerBalance(nodo);

    // Rotación Simple Izquierda
    if (balance > 1 && p.id < nodo->izquierdo->paciente.id)
        return rotarDerecha(nodo);

    // Rotación Simple Derecha
    if (balance < -1 && p.id > nodo->derecho->paciente.id)
        return rotarIzquierda(nodo);

    // Rotación Doble Izquierda-Derecha
    if (balance > 1 && p.id > nodo->izquierdo->paciente.id) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

    // Rotación Doble Derecha-Izquierda
    if (balance < -1 && p.id < nodo->derecho->paciente.id) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

bool AVLTree::eliminar(string id) {
    bool encontrado = false;
    raiz = eliminar(raiz, id, encontrado);
    return encontrado;
}

NodoAVL* AVLTree::minValueNode(NodoAVL* nodo) {
    NodoAVL* actual = nodo;
    while (actual->izquierdo != nullptr)
        actual = actual->izquierdo;
    return actual;
}

NodoAVL* AVLTree::eliminar(NodoAVL* nodo, string id, bool& encontrado) {
    if (nodo == nullptr) return nullptr;

    if (id < nodo->paciente.id) {
        nodo->izquierdo = eliminar(nodo->izquierdo, id, encontrado);
    } else if (id > nodo->paciente.id) {
        nodo->derecho = eliminar(nodo->derecho, id, encontrado);
    } else {
        encontrado = true;
        if ((nodo->izquierdo == nullptr) || (nodo->derecho == nullptr)) {
            NodoAVL* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }
            delete temp;
        } else {
            NodoAVL* temp = minValueNode(nodo->derecho);
            nodo->paciente = temp->paciente;
            nodo->derecho = eliminar(nodo->derecho, temp->paciente.id, encontrado);
        }
    }

    if (nodo == nullptr) return nullptr;

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0)
        return rotarDerecha(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->derecho) <= 0)
        return rotarIzquierda(nodo);

    if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

Paciente* AVLTree::buscarPorId(string id) const {
    NodoAVL* res = buscarPorId(raiz, id);
    return (res != nullptr) ? &(res->paciente) : nullptr;
}

NodoAVL* AVLTree::buscarPorId(NodoAVL* nodo, string id) const {
    if (nodo == nullptr || nodo->paciente.id == id) return nodo;
    if (id < nodo->paciente.id) return buscarPorId(nodo->izquierdo, id);
    return buscarPorId(nodo->derecho, id);
}

void AVLTree::buscarPorNombre(string nombre) const {
    bool encontrado = false;
    buscarPorNombre(raiz, nombre, encontrado);
    if (!encontrado) {
        cout << "No se encontraron pacientes con el nombre: " << nombre << endl;
    }
}

void AVLTree::buscarPorNombre(NodoAVL* nodo, string nombre, bool& encontrado) const {
    if (nodo == nullptr) return;
    buscarPorNombre(nodo->izquierdo, nombre, encontrado);
    if (nodo->paciente.nombre == nombre) {
        cout << "ID: " << nodo->paciente.id << " | Nombre: " << nodo->paciente.nombre 
             << " | Servicio: " << nodo->paciente.servicioAsignado << endl;
        encontrado = true;
    }
    buscarPorNombre(nodo->derecho, nombre, encontrado);
}

void AVLTree::mostrarInorden() const { inorden(raiz); cout << endl; }
void AVLTree::inorden(NodoAVL* nodo) const {
    if (nodo == nullptr) return;
    inorden(nodo->izquierdo);
    cout << "[" << nodo->paciente.id << ": " << nodo->paciente.nombre << "] ";
    inorden(nodo->derecho);
}

void AVLTree::mostrarPreorden() const { preorden(raiz); cout << endl; }
void AVLTree::preorden(NodoAVL* nodo) const {
    if (nodo == nullptr) return;
    cout << "[" << nodo->paciente.id << ": " << nodo->paciente.nombre << "] ";
    preorden(nodo->izquierdo);
    preorden(nodo->derecho);
}

void AVLTree::mostrarPostorden() const { postorden(raiz); cout << endl; }
void AVLTree::postorden(NodoAVL* nodo) const {
    if (nodo == nullptr) return;
    postorden(nodo->izquierdo);
    postorden(nodo->derecho);
    cout << "[" << nodo->paciente.id << ": " << nodo->paciente.nombre << "] ";
}

bool AVLTree::estaVacio() const { return raiz == nullptr; }
int AVLTree::getAltura() const { return obtenerAltura(raiz); }
NodoAVL* AVLTree::getRaiz() const { return raiz; }