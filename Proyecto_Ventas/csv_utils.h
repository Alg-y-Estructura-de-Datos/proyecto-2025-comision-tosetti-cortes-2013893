#pragma once
#include <fstream>  // Para manejar archivos (ifstream)
#include <sstream>  // Para usar stringstream y dividir líneas en campos
#include <iostream> // Para mostrar mensajes por pantalla
#include <list>     // LISTAS: usamos list<Venta> para almacenar todas las ventas
#include "venta.h"  // Importamos la definición del struct Venta

using namespace std;

// Función que carga un archivo CSV con datos de ventas y llena una lista de objetos Venta
void cargarCSV(const string &nombreArchivo, list<Venta> &ventas)
{
    ifstream archivo(nombreArchivo); // Abre el archivo en modo lectura
    if (!archivo.is_open())
    {
        cerr << " Error al abrir el archivo: " << nombreArchivo << "\n";
        return;
    }

    string linea;
    getline(archivo, linea); // Ignora la primera línea (encabezado del CSV)

    // Lee línea por línea hasta el final del archivo
    while (getline(archivo, linea))
    {
        stringstream ss(linea); // Usa stringstream para dividir los campos por coma
        string campo;
        Venta venta; // Creamos una nueva estructura Venta

        // Asignamos cada campo leído al atributo correspondiente de la venta
        getline(ss, venta.idVenta, ',');
        getline(ss, venta.fecha, ',');
        getline(ss, venta.pais, ',');
        getline(ss, venta.ciudad, ',');
        getline(ss, venta.cliente, ',');
        getline(ss, venta.producto, ',');
        getline(ss, venta.categoria, ',');

        // Conversiones numéricas
        getline(ss, campo, ',');
        venta.cantidad = stoi(campo); // Convertimos a int
        getline(ss, campo, ',');
        venta.precioUnitario = stod(campo); // Convertimos a double
        getline(ss, campo, ',');
        venta.montoTotal = stod(campo);

        // Medio de envío y estado
        getline(ss, venta.medioEnvio, ',');
        getline(ss, venta.estadoEnvio, ',');

        // Agregamos la venta cargada a la lista
        ventas.push_back(venta);
    }

    archivo.close(); // Cerramos el archivo una vez que terminamos
    cout << "\n Datos cargados correctamente. Total de ventas: " << ventas.size() << "\n\n";
}
