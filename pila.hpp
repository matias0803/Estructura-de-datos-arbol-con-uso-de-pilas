#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

struct nodo {
    char dato;
    nodo* siguiente;
};

class Pila {
private:
    nodo* top;

public:
    Pila() : top(nullptr) {}

    ~Pila() {
        while (!estaVacia()) {
            pop();
        }
    }

    void push(char valor) {
        nodo* nuevo_nodo = new nodo;
        nuevo_nodo->dato = valor;
        nuevo_nodo->siguiente = top;
        top = nuevo_nodo;
    }

    void pop() {
        if (!estaVacia()) {
            nodo* temp = top;
            top = top->siguiente;
            delete temp;
        } else {
            std::cout << "La pila está vacía, no se puede hacer pop.\n";
        }
    }

    int mostrar() const {
        if (!estaVacia()) {
            return top->dato;
        } else {
            std::cout << "La pila está vacía, no se puede hacer peek.\n";
            return -1; // Valor por defecto para indicar error
        }
    }

    bool estaVacia() const {
        return top == nullptr;
    }
};

#endif
