#include "Hospital.h"
#include <iostream>

using namespace std;

int main() {
    Hospital hospital;
    int opcion = 0;

    // Carga inicial automática de un archivo de prueba si existe
    hospital.cargarPacientesDesdeArchivo("pacientes.txt");

    do {
        cout << "\n=== HOSPITAL MARMAJA ===\n";
        cout << "1. Atender pacientes (Cola -> Decision -> AVL)\n";
        cout << "2. Ver departamentos y estados AVL\n";
        cout << "3. Buscar paciente (ID o Nombre)\n";
        cout << "4. Cargar archivo de pacientes\n";
        cout << "5. Salir\n";
        cout << "Seleccionar opcion: ";
        
        if (!(cin >> opcion)) {
            cout << "Entrada inválida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                hospital.atenderSiguientePaciente();
                break;
            case 2:
                hospital.verDepartamentos();
                break;
            case 3:
                hospital.buscarPaciente();
                break;
            case 4: {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo de texto (ej: pacientes.txt): ";
                cin >> nombreArchivo;
                hospital.cargarPacientesDesdeArchivo(nombreArchivo);
                break;
            }
            case 5:
                cout << "Saliendo del sistema del hospital. Liberando memoria...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 5);

    return 0;
}