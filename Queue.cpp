#include "Queue.H"

Queue::Queue() {
    frente = nullptr;
    fin = nullptr;
    tamano = 0;
}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(Paciente p) {
    NodoCola* nuevo = new NodoCola(p);
    if (isEmpty()) {
        frente = nuevo;
        fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }
    tamano++;
}

Paciente Queue::dequeue() {
    if (isEmpty()) {
        return Paciente(); // Retorna vacío si no hay elementos
    }
    NodoCola* temp = frente;
    Paciente p = temp->paciente;
    frente = frente->siguiente;
    if (frente == nullptr) {
        fin = nullptr;
    }
    delete temp;
    tamano--;
    return p;
}

bool Queue::isEmpty() const {
    return frente == nullptr;
}

int Queue::getTamano() const {
    return tamano;
}