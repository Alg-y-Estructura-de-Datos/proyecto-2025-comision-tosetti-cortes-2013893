#pragma once
#include <iostream>
#include <list>      // LISTA enlazada: se usa para almacenar las ventas
#include <map>       // HASH/ÁRBOL (std::map): se usa para agrupar y acumular datos
#include <algorithm> // ORDENAMIENTO: se usa para encontrar el mayor elemento
#include "venta.h"

using namespace std;

// CONSULTA 1: Mostrar ventas en una ciudad específica
void ventasPorCiudad(const list<Venta> &ventas)
{
    string ciudad;
    cout << "Ingrese la ciudad: ";
    getline(cin, ciudad);

    cout << "\n Lista de Ventas en " << ciudad << ":\n";
    // Recorre la lista de ventas (uso de list<>)
    for (const auto &v : ventas)
    {
        if (v.ciudad == ciudad)
        {
            cout << v.idVenta << " - " << v.producto << " - $" << v.montoTotal << "\n";
        }
    }
}

// CONSULTA 2: Mostrar ventas en un país dentro de un rango de fechas
void ventasPorRangoFecha(const list<Venta> &ventas)
{
    string pais, desde, hasta;
    cout << "Ingrese pais: ";
    getline(cin, pais);
    cout << "Desde (YYYY-MM-DD): ";
    getline(cin, desde);
    cout << "Hasta (YYYY-MM-DD): ";
    getline(cin, hasta);

    cout << "\n Fecha de Ventas en " << pais << " entre " << desde << " y " << hasta << ":\n";
    // Recorre todas las ventas y filtra por país + rango de fechas
    for (const auto &v : ventas)
    {
        if (v.pais == pais && v.fecha >= desde && v.fecha <= hasta)
        {
            cout << v.fecha << " - " << v.producto << " - $" << v.montoTotal << "\n";
        }
    }
}

// CONSULTA 3: Comparar 2 países por monto total, producto más vendido y medio de envío más usado
void compararPaises(const list<Venta> &ventas)
{
    string p1, p2;
    cout << "Ingrese primer pais: ";
    getline(cin, p1);
    cout << "Ingrese segundo pais: ";
    getline(cin, p2);

    double total1 = 0, total2 = 0;

    // MAPAS: agrupan productos y medios de envío con conteo acumulado
    map<string, int> productos1, productos2;
    map<string, int> envios1, envios2;

    for (const auto &v : ventas)
    {
        if (v.pais == p1)
        {
            total1 += v.montoTotal;
            productos1[v.producto] += v.cantidad;
            envios1[v.medioEnvio]++;
        }
        else if (v.pais == p2)
        {
            total2 += v.montoTotal;
            productos2[v.producto] += v.cantidad;
            envios2[v.medioEnvio]++;
        }
    }

    // ORDENAMIENTO (indirecto): busca el producto/envío con más cantidad
    auto maxProd = [](const auto &mapa)
    {
        return max_element(mapa.begin(), mapa.end(),
                           [](const auto &a, const auto &b)
                           { return a.second < b.second; })
            ->first;
    };

    cout << "\n Comparacion:\n";
    cout << p1 << ": $" << total1 << " | Producto: " << maxProd(productos1)
         << " | Envío: " << maxProd(envios1) << "\n";
    cout << p2 << ": $" << total2 << " | Producto: " << maxProd(productos2)
         << " | Envío: " << maxProd(envios2) << "\n";
}

// CONSULTA 4: Comparar cantidad y monto total entre 2 productos
void compararProductos(const list<Venta> &ventas)
{
    string prod1, prod2;
    cout << "Producto 1: ";
    getline(cin, prod1);
    cout << "Producto 2: ";
    getline(cin, prod2);

    // MAPA: acumula cantidad y monto total por producto
    map<string, pair<int, double>> datos;

    for (const auto &v : ventas)
    {
        if (v.producto == prod1 || v.producto == prod2)
        {
            auto &info = datos[v.producto];
            info.first += v.cantidad;
            info.second += v.montoTotal;
        }
    }

    for (const auto &[producto, info] : datos)
    {
        cout << producto << ": " << info.first << " unidades, $" << info.second << "\n";
    }
}

// CONSULTA 5 y 6: Mostrar productos cuyo monto promedio por unidad es mayor/menor a un umbral
void productosPorUmbral(const list<Venta> &ventas, bool mayor)
{
    string pais;
    double umbral;
    cout << "Ingrese pais: ";
    getline(cin, pais);
    cout << "Ingrese umbral ($): ";
    cin >> umbral;
    cin.ignore();

    // MAPA: producto → (suma monto total, suma cantidad)
    map<string, pair<double, int>> promedios;

    for (const auto &v : ventas)
    {
        if (v.pais == pais)
        {
            promedios[v.producto].first += v.montoTotal;
            promedios[v.producto].second += v.cantidad;
        }
    }

    bool encontrados = false;
    cout << "\n Productos " << (mayor ? "mayores" : "menores") << " a $" << umbral << " por unidad en " << pais << ":\n";

    for (const auto &[prod, val] : promedios)
    {
        if (val.second > 0)
        {
            double prom = val.first / val.second;
            if ((mayor && prom > umbral) || (!mayor && prom < umbral))
            {
                cout << prod << ": $" << prom << "\n";
                encontrados = true;
            }
        }
    }

    if (!encontrados)
    {
        cout << "No se encontraron productos que cumplan el criterio.\n";
    }
}

// FUNCIÓN FINAL: Menú interactivo de consultas dinámicas
void realizarConsultas(const list<Venta> &ventas)
{
    int opcion;
    do
    {
        cout << "\n===== CONSULTAS =====\n";
        cout << "1. Ventas por ciudad\n";
        cout << "2. Ventas por rango de fechas en un pais\n";
        cout << "3. Comparar dos paises\n";
        cout << "4. Comparar dos productos\n";
        cout << "5. Productos con monto promedio mayor a umbral\n";
        cout << "6. Productos con monto promedio menor a umbral\n";
        cout << "0. Volver\n";
        cout << "======================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            ventasPorCiudad(ventas);
            break;
        case 2:
            ventasPorRangoFecha(ventas);
            break;
        case 3:
            compararPaises(ventas);
            break;
        case 4:
            compararProductos(ventas);
            break;
        case 5:
            productosPorUmbral(ventas, true);
            break;
        case 6:
            productosPorUmbral(ventas, false);
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}
