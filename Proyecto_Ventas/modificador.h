#pragma once
#include <iostream>
#include <stack>   // PILAS: usamos stack<list<Venta>> para implementar "deshacer"
#include <list>    // LISTAS: list<Venta> permite recorrer y modificar fácilmente
#include "venta.h" // Estructura de venta

using namespace std;

// PILA GLOBAL: guarda copias completas de la lista de ventas antes de cada cambio
stack<list<Venta>> historialCambios;

// FUNCIÓN: Agrega una nueva venta a la lista
void agregarVenta(list<Venta> &ventas)
{
    Venta nueva;

    // Recolección de datos desde el usuario
    cout << "Ingrese ID de Venta: ";
    getline(cin, nueva.idVenta);
    cout << "Fecha (YYYY-MM-DD): ";
    getline(cin, nueva.fecha);
    cout << "Pais: ";
    getline(cin, nueva.pais);
    cout << "Ciudad: ";
    getline(cin, nueva.ciudad);
    cout << "Cliente: ";
    getline(cin, nueva.cliente);
    cout << "Producto: ";
    getline(cin, nueva.producto);
    cout << "Categoria: ";
    getline(cin, nueva.categoria);
    cout << "Cantidad: ";
    cin >> nueva.cantidad;
    cout << "Precio unitario: ";
    cin >> nueva.precioUnitario;
    cin.ignore(); // Importante: limpiar el buffer para getline siguiente

    // Calculamos el monto total
    nueva.montoTotal = nueva.cantidad * nueva.precioUnitario;

    cout << "Medio de Envio: ";
    getline(cin, nueva.medioEnvio);
    cout << "Estado de Envio: ";
    getline(cin, nueva.estadoEnvio);

    // Guardamos el estado anterior para permitir "deshacer"
    historialCambios.push(ventas);

    // Agregamos la nueva venta a la lista
    ventas.push_back(nueva);
    cout << " Venta agregada correctamente.\n";
}

// FUNCIÓN: Elimina ventas según país o ciudad (filtro dinámico)
void eliminarVenta(list<Venta> &ventas)
{
    string filtro;
    int tipo;

    cout << "Eliminar por: 1) Pais, 2) Ciudad ";
    cin >> tipo;
    cin.ignore(); // Limpiamos salto de línea
    cout << "Ingrese el valor: ";
    getline(cin, filtro);

    // Guardamos el estado anterior antes de eliminar
    historialCambios.push(ventas);

    int eliminadas = 0;

    // Eliminamos usando una función lambda y remove_if
    ventas.remove_if([&](const Venta &v)
                     {
        if ((tipo == 1 && v.pais == filtro) || (tipo == 2 && v.ciudad == filtro)) {
            ++eliminadas;
            return true;
        }
        return false; });

    cout << " Ventas eliminadas: " << eliminadas << "\n";
}

// FUNCIÓN: Modifica los datos de una venta específica (por ID)
void modificarVenta(list<Venta> &ventas)
{
    string id;
    cout << "Ingrese ID de la venta a modificar: ";
    getline(cin, id);

    // Buscamos la venta por ID en la lista
    for (auto &venta : ventas)
    {
        if (venta.idVenta == id)
        {
            // Guardamos el estado anterior antes de modificar
            historialCambios.push(ventas);

            // Reemplazamos los datos que el usuario desea actualizar
            cout << "Modificando venta con ID: " << id << "\n";
            cout << "Nuevo cliente (actual: " << venta.cliente << "): ";
            getline(cin, venta.cliente);
            cout << "Nuevo producto (actual: " << venta.producto << "): ";
            getline(cin, venta.producto);
            cout << "Nueva cantidad (actual: " << venta.cantidad << "): ";
            cin >> venta.cantidad;
            cout << "Nuevo precio unitario (actual: " << venta.precioUnitario << "): ";
            cin >> venta.precioUnitario;
            cin.ignore(); // Evita error con getline siguiente

            venta.montoTotal = venta.cantidad * venta.precioUnitario;

            cout << " Venta modificada.\n";
            return;
        }
    }

    cout << " Venta no encontrada.\n";
}

// FUNCIÓN: Deshace el último cambio realizado (agregado, eliminado o modificado)
void deshacerUltimoCambio(list<Venta> &ventas)
{
    if (historialCambios.empty())
    {
        cout << " No hay cambios para deshacer.\n";
        return;
    }

    // Restauramos la última versión guardada
    ventas = historialCambios.top();
    historialCambios.pop();

    cout << " Se deshizo el ultimo cambio.\n";
}
