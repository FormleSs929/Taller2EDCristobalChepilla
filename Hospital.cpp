#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <sstream>

Hospital::Hospital() {}

void Hospital::cargarPacientesDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[Error] No se pudo abrir el archivo: " << nombreArchivo << ". Verifique que exista.\n";
        return;
    }

    string linea;
    int cargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#') continue; // Ignorar líneas vacías o comentarios

        stringstream ss(linea);
        string segmento;
        Paciente p;

        try {
            getline(ss, p.id, ';');
            getline(ss, p.nombre, ';');
            
            getline(ss, segmento, ';'); p.edad = stoi(segmento);
            getline(ss, segmento, ';'); p.temperatura = stod(segmento);
            getline(ss, segmento, ';'); p.presionArterial = stod(segmento);
            getline(ss, segmento, ';'); p.dolor = stoi(segmento);
            
            getline(ss, p.tipoDolor, ';');
            
            getline(ss, segmento, ';'); p.trauma = stoi(segmento);
            getline(ss, segmento, ';'); p.sintomasNeurologicos = stoi(segmento);
            getline(ss, segmento, ';'); p.requiereCirugia = stoi(segmento);
            getline(ss, segmento, ';'); p.diasHospitalizacion = stoi(segmento);

            // Validar duplicados en los AVL existentes antes de encolar
            bool duplicado = 
                (avlUrgencias.buscarPorId(p.id) != nullptr) ||
                (avlMedicinaGeneral.buscarPorId(p.id) != nullptr) ||
                (avlCardiologia.buscarPorId(p.id) != nullptr) ||
                (avlNeurologia.buscarPorId(p.id) != nullptr) ||
                (avlTraumatologia.buscarPorId(p.id) != nullptr) ||
                (avlCirugia.buscarPorId(p.id) != nullptr) ||
                (avlPediatria.buscarPorId(p.id) != nullptr) ||
                (avlHospitalizacion.buscarPorId(p.id) != nullptr);

            if (!duplicado) {
                colaPacientes.enqueue(p);
                cargados++;
            } else {
                cout << "[Aviso] Paciente con ID " << p.id << " ya existe en el sistema. Ignorado.\n";
            }
        } catch (...) {
            cout << "[Error] Formato de datos inválido en la línea: " << linea << "\n";
        }
    }
    archivo.close();
    cout << "Se cargaron exitosamente " << cargados << " pacientes a la cola de espera.\n";
}

void Hospital::atenderSiguientePaciente() {
    if (colaPacientes.isEmpty()) {
        cout << "No hay pacientes en la cola de espera.\n";
        return;
    }

    Paciente p = colaPacientes.dequeue();
    string rutaLog = "";
    p.servicioAsignado = arbolDecision.evaluarPaciente(p, rutaLog);

    bool insertado = false;
    if (p.servicioAsignado == "Urgencias") insertado = avlUrgencias.insertar(p);
    else if (p.servicioAsignado == "Medicina General") insertado = avlMedicinaGeneral.insertar(p);
    else if (p.servicioAsignado == "Cardiologia") insertado = avlCardiologia.insertar(p);
    else if (p.servicioAsignado == "Neurologia") insertado = avlNeurologia.insertar(p);
    else if (p.servicioAsignado == "Traumatologia") insertado = avlTraumatologia.insertar(p);
    else if (p.servicioAsignado == "Cirugia") insertado = avlCirugia.insertar(p);
    else if (p.servicioAsignado == "Pediatria") insertado = avlPediatria.insertar(p);
    else if (p.servicioAsignado == "Hospitalizacion") insertado = avlHospitalizacion.insertar(p);

    cout << "\n=== ATENDIENDO PACIENTE ===\n";
    cout << "ID: " << p.id << "\nNombre: " << p.nombre << "\nEdad: " << p.edad << "\n";
    cout << "Ruta: " << rutaLog << "\n";
    cout << "Servicio asignado: " << p.servicioAsignado << "\n";
    if (insertado) {
        cout << "Paciente insertado correctamente en el AVL de " << p.servicioAsignado << ".\n";
    } else {
        cout << "[Aviso] El paciente ya se encontraba registrado en el AVL del servicio.\n";
    }
}

void Hospital::verDepartamentos() const {
    cout << "\n=== ESTADO DE LOS DEPARTAMENTOS ===\n";
    
    auto mostrarAvlInfo = [](string nombreServicio, const AVLTree& avl) {
        cout << nombreServicio << "\n";
        if (avl.estaVacio()) {
            cout << "  Sin pacientes\n";
        } else {
            cout << "  Recorrido Inorden (IDs): ";
            avl.mostrarInorden();
            cout << "  Altura del AVL: " << avl.getAltura() << "\n";
        }
    };

    mostrarAvlInfo("Urgencias", avlUrgencias);
    mostrarAvlInfo("Medicina General", avlMedicinaGeneral);
    mostrarAvlInfo("Cardiologia", avlCardiologia);
    mostrarAvlInfo("Neurologia", avlNeurologia);
    mostrarAvlInfo("Traumatologia", avlTraumatologia);
    mostrarAvlInfo("Cirugia", avlCirugia);
    mostrarAvlInfo("Pediatria", avlPediatria);
    mostrarAvlInfo("Hospitalizacion", avlHospitalizacion);
    cout << "-------------------------------------\n";
}

void Hospital::buscarPaciente() const {
    string criterio;
    cout << "\nIndique el ID o Nombre del paciente a buscar: ";
    cin >> ws;
    getline(cin, criterio);

    cout << "Buscando en los AVL del hospital...\n";
    
    Paciente* encontrado = nullptr;
    auto buscarEnAvl = [&](const AVLTree& avl) {
        if (!encontrado) encontrado = avl.buscarPorId(criterio);
    };

    buscarEnAvl(avlUrgencias);
    buscarEnAvl(avlMedicinaGeneral);
    buscarEnAvl(avlCardiologia);
    buscarEnAvl(avlNeurologia);
    buscarEnAvl(avlTraumatologia);
    buscarEnAvl(avlCirugia);
    buscarEnAvl(avlPediatria);
    buscarEnAvl(avlHospitalizacion);

    if (encontrado != nullptr) {
        cout << "\nPaciente encontrado:\n";
        cout << "ID: " << encontrado->id << "\n";
        cout << "Nombre: " << encontrado->nombre << "\n";
        cout << "Departamento: " << encontrado->servicioAsignado << "\n";
        cout << "Temperatura: " << encontrado->temperatura << "° | Dolor: " << encontrado->dolor << " | TipoDolor: " << encontrado->tipoDolor << "\n";
    } else {
        cout << "Buscando por coincidencia de nombre exacto...\n";
        avlUrgencias.buscarPorNombre(criterio);
        avlMedicinaGeneral.buscarPorNombre(criterio);
        avlCardiologia.buscarPorNombre(criterio);
        avlNeurologia.buscarPorNombre(criterio);
        avlTraumatologia.buscarPorNombre(criterio);
        avlCirugia.buscarPorNombre(criterio);
        avlPediatria.buscarPorNombre(criterio);
        avlHospitalizacion.buscarPorNombre(criterio);
    }
}