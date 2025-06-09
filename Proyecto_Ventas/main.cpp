#include <iostream>      // Para entrada y salida estándar (cin, cout)
#include <list>          // LISTAS: usamos list<Venta> para guardar todas las ventas
#include <string>        // Para usar strings
#include "venta.h"       // Estructura de datos Venta
#include "csv_utils.h"   // Función para cargar ventas desde archivo CSV
#include "menu.h"        // Muestra el menú principal
#include "procesador.h"  // Análisis de ventas (Top 5, promedios, etc.)
#include "modificador.h" // Funciones para agregar, eliminar, modificar ventas (usa pilas)
#include "consultas.h"   // Consultas dinámicas por ciudad, país, productos, etc.

using namespace std;

int main()
{
    list<Venta> ventas;         // Lista dinámica que almacena todas las ventas cargadas
    bool datosCargados = false; // Marca si se cargó el archivo CSV
    int opcion;                 // Almacena la opción elegida por el usuario

    do
    {
        // Muestra el menú de opciones al usuario
        mostrarMenuPrincipal();
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cin.ignore(); // Ignora el salto de línea después del número

        // Estructura de control del menú principal
        switch (opcion)
        {
        case 1:
            // Opción 1: Cargar datos desde archivo CSV
            cargarCSV("ventas_sudamerica.csv", ventas); // Lee y carga los datos
            procesarDatos(ventas);                      // Analiza ventas (Top 5, promedios, árbol)
            datosCargados = true;                       // Marca que los datos están listos
            break;

        case 2:
            // Opción 2: Agregar nueva venta
            if (!datosCargados)
            {
                cout << "\n Primero debe cargar los datos.\n\n";
                break;
            }
            agregarVenta(ventas);  // Agrega una nueva venta
            procesarDatos(ventas); // Actualiza estadísticas
            break;

        case 3:
            // Opción 3: Eliminar ventas (por ciudad o país)
            if (!datosCargados)
            {
                cout << "\n Primero debe cargar los datos.\n\n";
                break;
            }
            eliminarVenta(ventas); // Elimina ventas por filtro
            procesarDatos(ventas); // Vuelve a procesar
            break;

        case 4:
            // Opción 4: Modificar venta por ID
            if (!datosCargados)
            {
                cout << "\n Primero debe cargar los datos.\n\n";
                break;
            }
            modificarVenta(ventas); // Permite cambiar valores de una venta
            procesarDatos(ventas);  // Vuelve a analizar después de modificar
            break;

        case 5:
            // Opción 5: Consultas dinámicas
            if (!datosCargados)
            {
                cout << "\n Primero debe cargar los datos.\n\n";
                break;
            }
            realizarConsultas(ventas); // Muestra menú de consultas por ciudad, país, producto, etc.
            break;

        case 6:
            // Opción 6: Deshacer último cambio
            deshacerUltimoCambio(ventas); // PILA: Restaura la lista de ventas anterior
            procesarDatos(ventas);        // Recalcula los análisis
            break;

        case 7:
            // Opción 7: Salir del sistema
            cout << "\n Saliendo del sistema. ¡Gracias!\n";
            break;

        default:
            // Cualquier número que no sea 1-7
            cout << "\n Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 7); // El menú se repite mientras no se elija salir (opción 7)
}
