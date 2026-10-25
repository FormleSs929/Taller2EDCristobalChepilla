#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Paciente.h"
#include <string>

using namespace std;

struct NodoAVL {
    Paciente paciente;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(Paciente p) : paciente(p), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

class AVLTree {
private:
    NodoAVL* raiz;

    int obtenerAltura(NodoAVL* n) const;
    int obtenerBalance(NodoAVL* n) const;
    int max(int a, int b) const;

    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);

    NodoAVL* insertar(NodoAVL* nodo, Paciente p, bool& insertado);
    NodoAVL* eliminar(NodoAVL* nodo, string id, bool& encontrado);
    NodoAVL* minValueNode(NodoAVL* nodo);

    void destruir(NodoAVL* nodo);
    void inorden(NodoAVL* nodo) const;
    void preorden(NodoAVL* nodo) const;
    void postorden(NodoAVL* nodo) const;

    NodoAVL* buscarPorId(NodoAVL* nodo, string id) const;
    void buscarPorNombre(NodoAVL* nodo, string nombre, bool& encontrado) const;

public:
    AVLTree();
    ~AVLTree();

    bool insertar(Paciente p);
    bool eliminar(string id);
    Paciente* buscarPorId(string id) const;
    void buscarPorNombre(string nombre) const;
    
    void mostrarInorden() const;
    void mostrarPreorden() const;
    void mostrarPostorden() const;
    bool estaVacio() const;
    int getAltura() const;
    void mostrarEstadoBalance(NodoAVL* nodo) const;
    NodoAVL* getRaiz() const;
};

#endif