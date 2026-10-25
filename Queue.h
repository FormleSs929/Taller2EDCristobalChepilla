#ifndef QUEUE_H
#define QUEUE_H

#include "Paciente.h"

struct NodoCola {
    Paciente paciente;
    NodoCola* siguiente;
    NodoCola(Paciente p) : paciente(p), siguiente(nullptr) {}
};

class Queue {
private:
    NodoCola* frente;
    NodoCola* fin;
    int tamano;

public:
    Queue();
    ~Queue();
    void enqueue(Paciente p);
    Paciente dequeue();
    bool isEmpty() const;
    int getTamano() const;
};

#endif