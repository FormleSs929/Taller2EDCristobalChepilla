# Taller 2: Estructura de Datos - Hospital Marmaja

Sistema de gestión hospitalaria desarrollado en **C++** para clasificar automáticamente a los pacientes mediante un árbol de decisión manual y almacenarlos en árboles AVL independientes según el servicio asignado, utilizando una cola FIFO basada en nodos enlazados.

## Integrantes
* **Nombre:** Cristóbal Chepilla
* **RUT:** 21873055-8
* **Nombre en GitHub:** FormleSs929
* **Carrera:** ITI

---

## Estructura del Proyecto y Módulos
El código se encuentra modularizado en los siguientes archivos:
* **`Paciente.h` / `Paciente.cpp`**: Define la estructura de datos del paciente con sus respectivos atributos clínicos.
* **`Queue.h` / `Queue.cpp`**: Implementación manual de la Cola FIFO (orden de llegada), sin utilizar la STL.
* **`DecisionTree.h` / `DecisionTree.cpp`**: Árbol de decisión basado en punteros para evaluar múltiples atributos y determinar el servicio médico.
* **`AVLTree.h` / `AVLTree.cpp`**: Implementación manual del árbol AVL ordenado por ID, con rotaciones simples y dobles, cálculo de altura y factor de balance.
* **`Hospital.h` / `Hospital.cpp`**: Clase controladora encargada de gestionar la cola, el árbol de decisión y los 8 árboles AVL del hospital.
* **`main.cpp`**: Interfaz de consola interactiva con el menú principal del sistema.

---

## Criterio del Árbol de Decisión
El árbol evalúa los atributos del paciente siguiendo esta jerarquía para garantizar una ruta válida hacia los 8 servicios requeridos:
1. **Edad < 14** $\rightarrow$ **Pediatría**
2. **Trauma == 1**:
   * *Sí* $\rightarrow$ ¿Requiere Cirugía == 1? (Sí $\rightarrow$ **Cirugía**, No $\rightarrow$ **Traumatología**)
   * *No* $\rightarrow$ ¿Síntomas Neurológicos == 1? (Sí $\rightarrow$ **Neurología**, No $\rightarrow$ ...)
3. **Tipo de Dolor == "pecho"** $\rightarrow$ **Cardiología**
4. **Temperatura > 38.5 o Dolor >= 8** $\rightarrow$ **Urgencias**
5. **Días de Hospitalización >= 2** $\rightarrow$ **Hospitalización**
6. **Caso contrario** $\rightarrow$ **Medicina General**

---

## Instrucciones de Compilación y Ejecución (Codespace / Linux / Terminal)

### 1. Compilación:
Abre tu terminal en la carpeta del proyecto y ejecuta el siguiente comando con `g++`:
```bash
g++ -std=c++11 main.cpp Paciente.cpp Queue.cpp DecisionTree.cpp AVLTree.cpp Hospital.cpp -o hospital
```
### 2. Ejecución:
Para iniciar el programa, abre tu terminal en la carpeta del proyecto y ejecuta el siguiente comando:
```bash
./hospital
```
