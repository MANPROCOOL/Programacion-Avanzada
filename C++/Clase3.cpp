/**
 * =====================================================================================
 * Clase de Programación Orientada a Objetos (C++)
 * Conceptos abordados: Agregación, Modularidad, Cohesión, Acoplamiento y Amistad (friend).
 * Además de diferencias en gestión de memoria (C vs C++) y paso de parámetros por referencia.
 * =====================================================================================
 */

#include <iostream>
#include <cstdlib> // Para malloc y free

// --- NOTA TEÓRICA 1: GESTIÓN DE MEMORIA (Esquina superior izquierda de la pizarra) ---
/*
   En C tradicional, la memoria dinámica se reserva con malloc:
   int *v = (int *) malloc(cap * sizeof(int));
   
   En C++, se introducen los operadores nativos 'new' y 'delete', los cuales no solo asignan 
   memoria, sino que también invocan a los constructores/destructores de los objetos:
   int *v = new int[cap];
   delete[] v; // Nota: Para arreglos se usa delete[], para punteros simples 'delete v;'
*/

// =====================================================================================
// DEFINICIÓN DE LA CLASE: Punto3D
// =====================================================================================
class Linea; // Declaración adelantada (Forward Declaration) necesaria para la relación de amistad

class Punto3D {
private:
    // Atributos privados para mantener una alta COHESIÓN (ocultamiento de la estructura interna)
    double x, y, z;
    char color[3];

public:
    // Constructor por defecto (Inicializa en el origen)
    Punto3D() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    // Constructor por copia (Paso de parámetros por referencia constante para evitar duplicar memoria)
    Punto3D(const Punto3D &p) {
        x = p.x;
        y = p.y;
        z = p.z;
        color[0] = p.color[0];
        color[1] = p.color[1];
        color[2] = p.color[2];
    }

    // Métodos Getters (Selectores)
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Métodos Setters (Modificadores)
    void setX(double val) { x = val; }
    void setY(double val) { y = val; }
    void setZ(double val) { z = val; }

    // --- CONCEPTO CLAVE: AMISTAD (friend class) ---
    // Al declarar a 'Linea' como friend, le permitimos acceder directamente a nuestros miembros
    // privados (x, y, z) sin necesidad de usar getters/setters. 
    // Ojo: Esto rompe el encapsulamiento clásico, aumentando el ACOPLAMIENTO, pero optimiza el rendimiento.
    friend class Linea;
};

// =====================================================================================
// DEFINICIÓN DE LA CLASE: Linea (Demuestra AGREGACIÓN y MODULARIDAD)
// =====================================================================================
/*
   CONCEPTOS EN LA CLASE LINEA:
   - AGREGACIÓN: Una 'Linea' está compuesta por objetos de tipo 'Punto3D' (p1 y p2). La línea "tiene" puntos.
   - MODULARIDAD: Separar la lógica del punto de la lógica de la línea.
*/
class Linea {
private:
    Punto3D p1, p2;     // Relación de agregación por valor (Composición)
    int grosor;
    char color[3];

public:
    // Constructor por defecto
    Linea() {
        grosor = 1;
        // Los objetos p1 y p2 llaman automáticamente a sus constructores por defecto (0,0,0)
    }

    // Constructor parametrizado con PASO DE PARÁMETROS POR REFERENCIA CONSTANTE (&)
    // En C++, pasar por referencia 'const Tipo &obj' evita que se cree una copia completa 
    // del objeto en el stack (ahorrando tiempo y memoria), y el 'const' garantiza que no se modificará.
    Linea(const Punto3D &p1_ref, const Punto3D &p2_ref) {
        // Gracias a 'friend class Linea', podemos acceder directamente a los atributos privados de Punto3D:
        p1.x = p1_ref.x; 
        p1.y = p1_ref.y;
        p1.z = p1_ref.z;

        p2.x = p2_ref.x;
        p2.y = p2_ref.y;
        p2.z = p2_ref.z;
        
        // El pizarrón muestra un ejemplo tachado con una cruz roja en la asignación:
        // "p1 = p1_ref;" -> Esto invocaría al operador de asignación por defecto.
        // También muestra una validación condicional anotada abajo:
        // if (p1.x < p2.x) { ... }
    }
};

// =====================================================================================
// FUNCIÓN PRINCIPAL: main()
// =====================================================================================
int main() {
    std::cout << "--- Demostracion de Conceptos de POO desde la Pizarra ---" << std::endl;

    // 1. Creación de instancias de Punto3D en el Stack (Memoria Estática de la función)
    Punto3D p1; 
    Punto3D p2;

    // Modificamos algunos valores usando los setters (suponiendo lógica del programa)
    p1.setX(1.5); p1.setY(2.0); p1.setZ(0.0);
    p2.setX(4.5); p2.setY(6.0); p2.setZ(0.0);

    // 2. Construcción de una Linea pasando los puntos por referencia
    // Aquí se ejecuta el constructor: Linea l(p1, p2);
    Linea l(p1, p2);

    // 3. Demostración de asignación (Instancia p3 toma los valores de p1)
    Punto3D p3;
    p3 = p1; // Copia miembro a miembro en el stack

    std::cout << "Codigo ejecutado correctamente de acuerdo al diagrama de la clase." << std::endl;
    return 0;
}