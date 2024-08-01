#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime> // Para time()
#include <algorithm>
using namespace std;


template <typename T>
class Nodo {
private:
    T elem;  // Elemento almacenado en el nodo
    Nodo<T>* derecho;
    Nodo<T>* izquierdo;
    int Contador; 
    int factorBalance;

public:
    // Inicializar el color en los constructores
    Nodo()
    {
        derecho = nullptr;
        izquierdo = nullptr;
        Contador = 0;
        factorBalance = 0;
    }
    
    Nodo(T elem)
    {
        this->elem = elem;
        derecho = nullptr;
        izquierdo = nullptr;
        Contador = 1;
        factorBalance = 0;
    }

    void setElem(T valor) {
        elem = valor;
    }

    T getElem()  {
        return elem;
    }

    Nodo<T>*& getDerecho() {
        return derecho;
    }

    Nodo<T>*& getIzquierdo() {
        return izquierdo;
    }

    void setDerecho(Nodo<T>* nodo) {
        derecho = nodo;
    }

    void setIzquierdo(Nodo<T>* nodo) {
        izquierdo = nodo;
    }

    int getContador(){
        return Contador;
    }

    void aumentarRepetido() {
        Contador++;
    }

    int getFactor(){
        return factorBalance; 
    }
    void setFactor(int factorBalance) {
        this->factorBalance = factorBalance; 
    }
};
