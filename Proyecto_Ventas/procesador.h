#pragma once
#include <map>       // MAP: Para agrupar ventas por país y ciudad/categoría
#include <vector>    // Para ordenar ciudades como vector
#include <string>    // Strings para nombres de ciudad, país, etc.
#include <algorithm> // ORDENAMIENTO: usamos sort() para Top 5
#include <iostream>  // Entrada/salida
#include <list>      // LISTA: estructura base con todas las ventas
#include "venta.h"   // Estructura Venta

using namespace std;

// FUNCIÓN 1: Muestra el Top 5 de ciudades con mayor monto vendido por país
void procesarTop5CiudadesPorPais(const list<Venta> &ventas)
{
    // Mapa anidado: país → ciudad → monto total
    map<string, map<string, double>> ventasPorPaisCiudad;

    // Recorremos todas las ventas
    for (const auto &venta : ventas)
        ventasPorPaisCiudad[venta.pais][venta.ciudad] += venta.montoTotal;

    cout << "\n Top 5 ciudades con mayor monto de ventas por pais:\n";

    // Recorremos por país
    for (const auto &[pais, ciudades] : ventasPorPaisCiudad)
    {
        cout << "\n Pais: " << pais << "\n";

        // Convertimos el map de ciudades a vector para ordenarlo
        vector<pair<string, double>> ciudadesOrdenadas(ciudades.begin(), ciudades.end());

        // Ordenamos de mayor a menor por monto
        sort(ciudadesOrdenadas.begin(), ciudadesOrdenadas.end(),
             [](const auto &a, const auto &b)
             {
                 return a.second > b.second;
             });

        // Mostramos hasta 5 ciudades
        int top = 0;
        for (const auto &[ciudad, monto] : ciudadesOrdenadas)
        {
            cout << " Ciudad " << ciudad << ": $" << monto << "\n";
            if (++top == 5)
                break;
        }
    }
}

// FUNCIÓN 2: Muestra el promedio por categoría en cada país
void promedioCategoriaPorPais(const list<Venta> &ventas)
{
    // Mapa anidado: país → categoría → (suma monto, cantidad)
    map<string, map<string, pair<double, int>>> datos;

    // Acumulamos por país y categoría
    for (const auto &venta : ventas)
    {
        datos[venta.pais][venta.categoria].first += venta.montoTotal;
        datos[venta.pais][venta.categoria].second += 1;
    }

    cout << "\n Promedio de ventas por categoria y pais:\n";

    // Recorremos por país y categoría
    for (const auto &[pais, categorias] : datos)
    {
        cout << "\n Pais: " << pais << "\n";

        for (const auto &[cat, val] : categorias)
        {
            double promedio = val.first / val.second;
            cout << " Categoria: " << cat << " → Promedio: $" << promedio << "\n";
        }
    }
}

// FUNCIÓN 3: Llama a los dos análisis anteriores (se invoca desde main)
void procesarDatos(const list<Venta> &ventas)
{
    procesarTop5CiudadesPorPais(ventas); // Top 5 ciudades
    promedioCategoriaPorPais(ventas);    // Promedios por categoría
}
