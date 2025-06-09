#pragma once
#include <string>   // Para usar std::string
#include <memory>   // Para usar std::unique_ptr (punteros inteligentes)
#include <iostream> // Para imprimir el árbol
#include "venta.h"  // Incluye la estructura Venta

using namespace std;

// ESTRUCTURA DE ÁRBOL BINARIO DE PRODUCTOS
struct NodoProducto
{
    string producto;              // Nombre del producto
    int cantidadTotal = 0;        // Total acumulado de unidades vendidas
    unique_ptr<NodoProducto> izq; // Subárbol izquierdo (productos menores alfabéticamente)
    unique_ptr<NodoProducto> der; // Subárbol derecho (productos mayores)

    // Constructor
    NodoProducto(string p, int c) : producto(p), cantidadTotal(c) {}
};

// FUNCIÓN: Inserta un producto en el árbol o suma la cantidad si ya existe
// Usa RECURSIÓN para recorrer el árbol y ubicar correctamente el nodo
void insertarProducto(unique_ptr<NodoProducto> &nodo, const string &producto, int cantidad)
{
    if (!nodo)
    {
        // Si el nodo no existe, lo creamos
        nodo = make_unique<NodoProducto>(producto, cantidad);
    }
    else if (producto < nodo->producto)
    {
        // RECURSIÓN: vamos al subárbol izquierdo si el producto es menor
        insertarProducto(nodo->izq, producto, cantidad);
    }
    else if (producto > nodo->producto)
    {
        // RECURSIÓN: vamos al subárbol derecho si el producto es mayor
        insertarProducto(nodo->der, producto, cantidad);
    }
    else
    {
        // Ya existe: sumamos la cantidad vendida
        nodo->cantidadTotal += cantidad;
    }
}

// FUNCIÓN: Muestra el árbol en orden alfabético (inorden)
// También recursiva
void mostrarArbol(const unique_ptr<NodoProducto> &nodo)
{
    if (!nodo)
        return;

    // RECURSIÓN: recorremos el subárbol izquierdo
    mostrarArbol(nodo->izq);

    // Visitamos el nodo actual
    cout << nodo->producto << ": " << nodo->cantidadTotal << " unidades\n";

    // RECURSIÓN: recorremos el subárbol derecho
    mostrarArbol(nodo->der);
}
