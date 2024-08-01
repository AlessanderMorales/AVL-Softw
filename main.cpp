#include <iostream>
#include "ArbolBin.h"
#include <string>
#include <fstream>
#include <chrono>
#include <map>
template<typename T>

void leerArchivo(ArbolBin<T>* ArbolBin) {
    ifstream archivo;
    archivo.open("C:\\Users\\MSI\\OneDrive\\Desktop\\Estructura-Datos-2023\\ABB-Punteros\\libro.txt");
    if (!archivo.is_open()) {
       std:: cout << "Error al abrir el archivo." << std::endl;
        return;
    }
    else {
         T palabra;
        while (archivo >> palabra) {
            bool continuar;
            ArbolBin->Insertar(palabra,continuar);
        }
        archivo.close();
    }
}

template<typename T>
void leerArchivoMaps(map<string, T>& contadorPalabras) {
    ifstream archivo;
    archivo.open("C:\\Users\\MSI\\OneDrive\\Desktop\\Estructura-Datos-2023\\ABB-Punteros\\libro.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    } else {
        string palabra;
        while (archivo >> palabra) {
            contadorPalabras[palabra]++;
        }
        archivo.close();
    }
}

int main() {
    ArbolBin<string>* arbol = new ArbolBin<string>();
    auto star = chrono::high_resolution_clock::now();
    leerArchivo(arbol);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - star);
    cout << "Tiempo de AVL: " << duration.count() << " nanosegundos" << endl;
    cout << "Altura ALV :" << arbol->calcularAltura() << endl; 
    cout << "Cantidad Nodos AVL :" << arbol->contarNodos()<<endl;
    arbol->EliminarTodo();


    map<string, int> contadorPalabras;
    auto star2 = chrono::high_resolution_clock::now();
    leerArchivoMaps(contadorPalabras);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - star2);
    cout << "Tiempo de MAPS: " << duration2.count() << " nanosegundos" << endl;
    for (auto par : contadorPalabras) {
        cout << par.first << " contadas: " << par.second << " repetidas" << endl;
    }
    string valor;
    /*
    int opcion;

    while (true) {
        std::cout << "Menu de opciones:\n";
        std::cout << "1. Insertar elemento\n";
        std::cout << "2. Mostrar arbol InOrder\n";
        std::cout << "3. Mostrar arbol PreOrder\n";
        std::cout << "4. Mostrar arbol PostOrder\n";
        std::cout << "5. Contar nodos\n";
        std::cout << "6. Calcular altura\n";
        std::cout << "7. Mostrar menor elemento\n";
        std::cout << "8. Mostrar mayor elemento\n";
        std::cout << "9. Contar hojas\n";
        std::cout << "10. Eliminar Todo\n";
        std::cout << "11. Buscar un elemento\n";
        std::cout << "12. Eliminar un elemento\n";
        std::cout << "13. Mostrar por niveles\n";
        std::cout << "14. Salir\n";
        std::cout << "Selecciona una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:{
                bool continuar;
                std::cout << "Introduce el valor a insertar: ";
                std::cin >> valor;
                arbol->Insertar(valor,continuar); 
                break;
            }
            case 2:{
                arbol->recorrerInOrder();
                std::cout <<" \n";
                break;
            }
            case 3:{
                arbol->recorrerPreOrder();
                std::cout <<" \n";
                break;
            }    
            case 4:{
                arbol->recorrerPostOrder();
                std::cout <<" \n";
                break;
            }
            case 5:{
                std::cout << "Numero total de nodos: " << arbol->contarNodos() << "\n";
                break;
            }
            case 6:{
                std::cout << "Altura del arbol: " << arbol->calcularAltura() << "\n";
                break;
            }
            case 7:{
                if (arbol->Menor(valor)) {
                    std::cout << "El elemento menor es: " << valor << "\n";
                } else {
                    std::cout << "El arbol está vacio.\n";
                }
                break;
            }
            case 8:{
                if (arbol->Mayor(valor)) {
                    std::cout << "El elemento mayor es: " << valor << "\n";
                } else {
                    std::cout << "El arbol está vacío.\n";
                }
                break;
            }
            case 9:{
                std::cout << "Numero total de hojas: " << arbol->Hojas() << "\n";
                break;
            }
            case 10:{
                arbol->EliminarTodo();
                std::cout << "arbol eliminado.\n";
                break;
            }
            case 11:{
                std::cout << "Introduce el valor a buscar: ";
                std::cin >> valor;
                if (arbol->Buscar(valor)) { 
                    std::cout << "Elemento encontrado.\n";
                } else {
                    std::cout << "Elemento no encontrado.\n";
                }
                break;
            }
            case 12:{
                std::cout << "Introduce el valor a eliminar: ";
                std::cin >> valor;
                if (arbol->EliminarElemento(valor)) {
                    std::cout << "Elemento eliminado.\n";
                } else {
                    std::cout << "Elemento no encontrado o Arbol vacío.\n";
                }
                break;
            }
            case 13:{
                arbol->MostrarPorNiveles();
                cout<<endl;
                break;
            }
            case 15:{
                std::cout << "Saliendo...\n";
                delete arbol;
                return 0;
            }
            default:
                std::cout << "Opción no válida, intenta de nuevo.\n";
        }
    }
    */
    delete arbol;
    return 0;
}