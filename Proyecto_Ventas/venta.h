#pragma once
#include <string> // Para usar strings
using namespace std;

// ESTRUCTURA PRINCIPAL: Representa una venta individual
struct Venta
{
    string idVenta;   // ID único de la venta
    string fecha;     // Fecha de la venta (formato: YYYY-MM-DD)
    string pais;      // País donde ocurrió la venta
    string ciudad;    // Ciudad donde ocurrió la venta
    string cliente;   // Nombre del cliente
    string producto;  // Nombre del producto vendido
    string categoria; // Categoría del producto

    int cantidad;          // Cantidad de unidades vendidas
    double precioUnitario; // Precio por unidad
    double montoTotal;     // Monto total de la venta (cantidad * precio)

    string medioEnvio;  // Medio de envío utilizado (aéreo, terrestre, etc.)
    string estadoEnvio; // Estado del envío (entregado, en tránsito, etc.)
};
