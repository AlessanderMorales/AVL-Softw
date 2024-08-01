#include <iostream>
#include "Nodo.h"
#include <string>

template <typename T>
class ArbolBin {
private:
    Nodo<T>* raiz;
public:

    ArbolBin() : raiz(nullptr) {}

    void RotarIzquierdaSimple(Nodo<T>*& raiz)
    {
        Nodo<T>* NuevaRaiz = raiz->getDerecho();
        Nodo<T>* temp;
        if (NuevaRaiz->getIzquierdo() != nullptr)
            temp = NuevaRaiz->getIzquierdo();
        else
            temp = nullptr;
        NuevaRaiz->getIzquierdo() = raiz;
        raiz->getDerecho() = temp; 
        raiz = NuevaRaiz;
        raiz->setFactor(0);
        raiz->getIzquierdo()->setFactor(0);
    }

    void RotarDerechaSimple(Nodo<T>*& raiz)
    {
        Nodo<T>* NuevaRaiz = raiz->getIzquierdo();
        Nodo<T>* temp;
        if (NuevaRaiz->getDerecho() != nullptr)
            temp = NuevaRaiz->getDerecho();
        else
            temp = nullptr;
        NuevaRaiz->getDerecho() = raiz;
        raiz->getIzquierdo() = temp;
        raiz = NuevaRaiz;
        raiz->setFactor(0);
        raiz->getDerecho()->setFactor(0);
    }



    void RotarDerechoCompuesto(Nodo<T>*& raiz)
    {
        Nodo<T>* nuevaRaiz = raiz->getIzquierdo()->getDerecho();
        Nodo<T>* tempIzq = nuevaRaiz->getIzquierdo();
        Nodo<T>* tempDer = nuevaRaiz->getDerecho();
        
        nuevaRaiz->setIzquierdo(raiz->getIzquierdo());
        nuevaRaiz->setDerecho(raiz);
        nuevaRaiz->getIzquierdo()->setDerecho(tempIzq);
        nuevaRaiz->getDerecho()->setIzquierdo(tempDer);
        raiz = nuevaRaiz;

        // Actualizar factores de equilibrio
        if (raiz->getFactor() == 0) {
            raiz->getIzquierdo()->setFactor(0);
            raiz->getDerecho()->setFactor(0);
        }
        else if (raiz->getFactor() == 1) {
            raiz->getIzquierdo()->setFactor(0);
            raiz->getDerecho()->setFactor(-1);
            raiz->setFactor(0);
        }
        else { // raiz->getFactor() == -1
            raiz->getIzquierdo()->setFactor(1);
            raiz->getDerecho()->setFactor(0);
            raiz->setFactor(0);
        }

    }


    void RotarIzquierdaCompuesto(Nodo<T>*& raiz) {
        Nodo<T>* nuevaRaiz = raiz->getDerecho()->getIzquierdo();
        Nodo<T>* tempIzq = nuevaRaiz->getDerecho(); 
        Nodo<T>* tempDer = nuevaRaiz->getIzquierdo();


        nuevaRaiz->setDerecho(raiz->getDerecho());
        nuevaRaiz->setIzquierdo(raiz);
        nuevaRaiz->getIzquierdo()->setDerecho(tempDer);
        nuevaRaiz->getDerecho()->setIzquierdo(tempIzq);
        raiz = nuevaRaiz;

        // Actualizar factores de equilibrio
        if (raiz->getFactor() == 0) {
            raiz->getIzquierdo()->setFactor(0);
            raiz->getDerecho()->setFactor(0);
        }
        else if (raiz->getFactor() == -1) {
            raiz->getIzquierdo()->setFactor(1);
            raiz->getDerecho()->setFactor(0);
            raiz->setFactor(0);
        }
        else { // factor = 0
            raiz->getIzquierdo()->setFactor(0);
            raiz->getDerecho()->setFactor(-1);
            raiz->setFactor(0);
        }
    }    

   
    bool InsertarRecursivo(T elem, Nodo<T>*& raiz,bool& continuar) {
        bool resp = false;
        if (raiz == nullptr) {
            Nodo<T>* nuevo = new Nodo<T>(elem);
            raiz = nuevo;
            continuar = true;
            resp = true;
        }
        else if (elem < raiz->getElem()) {
            resp = InsertarRecursivo(elem, raiz->getIzquierdo(),continuar);
            if (continuar) {
                raiz->setFactor(raiz->getFactor() + 1);
                if (raiz->getFactor() == 0)
                    continuar = false;
                else if (raiz->getFactor() == 2) {
                    continuar = false;
                    if (raiz->getIzquierdo()->getFactor() == 1)
                        RotarDerechaSimple(raiz);
                    else
                        RotarDerechoCompuesto(raiz);
                }
            }
        }
        else if (elem > raiz->getElem()) {
            resp = InsertarRecursivo(elem, raiz->getDerecho(),continuar);
            if (continuar) {
                raiz->setFactor(raiz->getFactor() - 1);
                if (raiz->getFactor() == 0)
                    continuar = false;
                else if (raiz->getFactor() == -2) {
                    continuar = false;
                    if (raiz->getDerecho()->getFactor() == -1)
                        RotarIzquierdaSimple(raiz);
                    else
                        RotarIzquierdaCompuesto(raiz);
                }
            }
        }
        return resp;
    }

    bool Insertar(T elem, bool& continuar)
    {
        return InsertarRecursivo( elem, raiz, continuar);
    }

    void recorrerInOrderRecursivo(Nodo<T>* nodo) {
        if (nodo !=  nullptr) {
            recorrerInOrderRecursivo(nodo->getIzquierdo());
            std::cout << nodo->getElem() << " ";
            recorrerInOrderRecursivo(nodo->getDerecho());
        }
    }

    void recorrerInOrder()
    {
        recorrerInOrderRecursivo(raiz);
    }

    void recorrerPreOrderRecursivo(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            std::cout << nodo->getElem() << " ";
            recorrerPreOrderRecursivo(nodo->getIzquierdo());
            recorrerPreOrderRecursivo(nodo->getDerecho());
        }
    }

    void recorrerPreOrder()
    {
        recorrerPreOrderRecursivo(raiz);
    }

    void recorrerPostOrderRecursivo(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            recorrerPostOrderRecursivo(nodo->getIzquierdo());
            recorrerPostOrderRecursivo(nodo->getDerecho());
            std::cout << nodo->getElem() << " ";
        }
    }

    void recorrerPostOrder()
    {
        recorrerPostOrderRecursivo(raiz);
    }


    int contarNodosRecursivo(Nodo<T>* nodo) {
        int res;
        if (nodo == nullptr)
        {
             res = 0;
        }
        else{
            res = 1 + contarNodosRecursivo(nodo->getIzquierdo()) + contarNodosRecursivo(nodo->getDerecho());
        }
        return res;
    }

    int contarNodos()
    {
        return contarNodosRecursivo(raiz);
    }

    int calcularAlturaRecursivo(Nodo<T>* nodo) {
        int res;
        if (nodo == nullptr)
        {
            res = 0;
        }
        else
        {
            int alturaIzquierda = calcularAlturaRecursivo(nodo->getIzquierdo());
            int alturaDerecha = calcularAlturaRecursivo(nodo->getDerecho());
            if(alturaIzquierda > alturaDerecha){
                res = 1 + alturaIzquierda;
            }
            else
            {
                res = 1 +  alturaDerecha;
            }
        }
       return res;
    }

        int calcularAlturaRecursivo2(Nodo<T>* nodo) {
        int res;
        if (nodo == nullptr)
        {
            res = 0;
        }
        else
        {
            int alturaIzquierda = calcularAlturaRecursivo(nodo->getIzquierdo());
            int alturaDerecha = calcularAlturaRecursivo(nodo->getDerecho());
            if(alturaIzquierda < alturaDerecha){
                res = 1 + alturaIzquierda;
            }
            else
            {
                res = 1 +  alturaDerecha;
            }
        }
       return res;
    }

    int calcularAltura()
    {
        return calcularAlturaRecursivo(raiz);
    }

    int calcular()
    {
        return calcularAlturaRecursivo2(raiz);
    }
    Nodo<T>* Buscar_ABB(Nodo<T>* nodo, T elem) {
        Nodo<T>* resultado;
        if(nodo==nullptr)
        {
            resultado = nullptr;
        }
        else{
            if(elem == nodo->getElem() ){
                resultado = nodo;
            }
            else if(elem < nodo->getElem() )
            {
                resultado = Buscar_ABB(nodo->getIzquierdo(),elem);
            }
            else{
                resultado = Buscar_ABB(nodo->getDerecho(),elem);
            }
        }
    return resultado;
}

    Nodo<T>* Buscar(T elem)
    {
        return Buscar_ABB(raiz,elem);
    }


    void EliminarTodoRecursivo(Nodo<T>*& nodo) {
        if (nodo != nullptr) {
            EliminarTodoRecursivo(nodo->getDerecho());
            EliminarTodoRecursivo(nodo->getIzquierdo());
            delete nodo;
        }
    }

    void EliminarTodo()
    {
        EliminarTodoRecursivo(raiz);
    }

    int ContarHojas(Nodo<T>* nodo) {
        int resp;
        if (nodo == nullptr) {
            resp = 0;
        }
        else
        {
            if (!nodo->getIzquierdo() && !nodo->getDerecho()) {
                resp = 1;
            } else {
                resp = ContarHojas(nodo->getIzquierdo()) + ContarHojas(nodo->getDerecho());
            }

        }
        return resp;
    }

    int Hojas()
    {
        return  ContarHojas(raiz);
    }

    bool MostrarMenor(Nodo<T>* raiz, T& menor) {
        bool res;
        if (raiz == nullptr) {  
            res = false;
        }
        else{
            Nodo<T>* actual = raiz;
            while (actual->getIzquierdo() != nullptr) {  
                actual = actual->getIzquierdo();
            }
            menor = actual->getElem(); 
            res = true;  // Se encontró el elemento menor
        }
        return res;
    }
    bool Menor(T& menor)
    {
        return MostrarMenor(raiz,menor);
    }

    bool MostrarMayor(Nodo<T>* raiz, T& mayor) {
        bool res;
        if (raiz == nullptr) {
            res = false;
        }
        else{
            Nodo<T>* actual = raiz;
            while (actual->getDerecho() != nullptr) {  
                actual = actual->getDerecho();
            }
            mayor = actual->getElem();
            res = true;
        }
        return res;
    }

    bool Mayor(T& mayor) {
        return MostrarMayor(raiz,mayor);
    }

bool EliminarElementoRecursivo(Nodo<T>*& nodo, T elemento) {
    if (nodo == nullptr) {
        return false; // Elemento no encontrado
    } else if (elemento < nodo->getElem()) {
        return EliminarElementoRecursivo(nodo->getIzquierdo(), elemento);
    } else if (elemento > nodo->getElem()) {
        return EliminarElementoRecursivo(nodo->getDerecho(), elemento);
    } else { // Elemento encontrado
        if (nodo->getIzquierdo() == nullptr || nodo->getDerecho() == nullptr) {
            Nodo<T>* temp = nodo->getIzquierdo() ? nodo->getIzquierdo() : nodo->getDerecho();
            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp; // Copiar el contenido del hijo
            }
            delete temp;
        } else {
            T Min;
            MostrarMenor(nodo->getDerecho(), Min);
            nodo->setElem(Min);
            return EliminarElementoRecursivo(nodo->getDerecho(), Min);
        }
        return true;
    }
}


    bool EliminarElemento(T elemento)
    {
        return EliminarElementoRecursivo(raiz,elemento);
    }


void MostrarNivel(Nodo<T>* nodo, int nivel) {
    if (nivel == 1) {
        if (nodo != nullptr) {
            std::cout << nodo->getElem();
        } else {
            std::cout << "- ";
        }
    } else if (nivel > 1 && nodo != nullptr) {
        MostrarNivel(nodo->getIzquierdo(), nivel - 1);
        MostrarNivel(nodo->getDerecho(), nivel - 1);
    }
}

void MostrarPorNiveles() {
    int altura = calcularAlturaRecursivo(raiz);
    for (int i = 1; i <= altura; i++) {
        MostrarNivel(raiz, i);
        std::cout << std::endl;
    }
}



};