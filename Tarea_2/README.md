# Tarea 2 y 3 de Algoritmo y Complejidad

Este repositorio contiene los códigos correspondientes a las tareas 2 y 3 de la materia **Algoritmo y Complejidad**. Los archivos implementan dos enfoques diferentes para resolver el problema de transformar una cadena en otra utilizando las operaciones de sustitución, inserción, eliminación y transposición, minimizando el costo total.

---

## Archivos

### 1. `BruteForce.cpp`
Este archivo corresponde a la **Tarea 2** y utiliza un enfoque de fuerza bruta con recursión para resolver el problema.  
#### **Características principales**:
- Implementación recursiva pura.
- Evalúa todas las posibles transformaciones para determinar el costo mínimo.
- Admite las siguientes operaciones con sus respectivos costos:
  - **Sustitución**: costo = 2 (si los caracteres son diferentes).
  - **Inserción**: costo = 1.
  - **Eliminación**: costo = 1.
  - **Transposición**: costo = 1 (si los caracteres intercambiados coinciden).
- **Complejidad**:
  - **Tiempo**: \[O(4^{\min(m, n)})\]
  - **Espacio**: O(n+m)

---

### 2. `Dinamic.cpp`
Este archivo corresponde a la **Tarea 3** y utiliza un enfoque de programación dinámica para optimizar la solución del problema.  
#### **Características principales**:
- Implementación iterativa basada en una tabla bidimensional (`dp`) para evitar cálculos repetidos.
- Admite las mismas operaciones y costos que el enfoque de fuerza bruta.
- **Complejidad**:
  - **Tiempo**: \(O(m \times n)\), donde \(m\) y \(n\) son las longitudes de las cadenas de entrada.
  - **Espacio**: \(O(m \times n)\), debido a la tabla `dp`.

---

## Ejecución de los programas

### **Compilación**
Ambos códigos están escritos en C++ y se pueden compilar usando cualquier compilador compatible, como `g++`.  
Ejemplo de compilación:
```bash
g++ BruteForce.cpp -o main
g++ Dinamic.cpp -o main
