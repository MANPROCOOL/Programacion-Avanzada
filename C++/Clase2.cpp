#include <cmath>    // Incluimos cmath para usar la función sqrt() (raíz cuadrada)
#include <cstdio>   // Incluimos cstdio para usar printf()

/* * Definición de la clase Punto3D.
 * Una clase es un molde para crear objetos que agrupan datos (atributos) 
 * y funciones (métodos).
 */
class Punto3D {
    // ATRIBUTOS: Por defecto en C++, si no se especifica, son 'private'.
    // Esto significa que solo pueden ser accedidos desde dentro de la clase.
    double x;
    double y;
    double z;
    unsigned char color[3]; // Arreglo para almacenar valores RGB del color

public: // ESPECIFICADOR DE ACCESO: Todo lo que sigue es accesible desde fuera de la clase.

    /* * CONSTRUCTOR: 
     * Es un método especial que se ejecuta automáticamente al crear un objeto.
     * Su función principal es inicializar los atributos.
     */
    Punto3D() {
        x = 0; 
        y = 0; 
        z = 0;
        // Inicializamos los tres canales de color (R, G, B) en 0
        color[0] = color[1] = color[2] = 0;
    }

    /*
     * MÉTODO: distancia_origen
     * Calcula la distancia euclidiana desde el punto (0,0,0) hasta (x,y,z).
     * Fórmula: √(x² + y² + z²)
     */
    double distancia_origen() {
        return sqrt(x*x + y*y + z*z);
    }

    /* * MÉTODOS "GETTERS": 
     * Sirven para obtener (leer) el valor de atributos privados desde el exterior.
     */
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }

    /* * MÉTODOS "SETTERS": 
     * Sirven para asignar o modificar el valor de atributos privados.
     * Permiten validar los datos antes de guardarlos si fuera necesario.
     */
    void setX(double xa) { x = xa; }
    void setY(double ya) { y = ya; }
    void setZ(double za) { z = za; }

}; // Fin de la clase (no olvidar el punto y coma)

/*
 * FUNCIÓN PRINCIPAL (main):
 * Donde comienza la ejecución del programa.
 */
int main() {
    // 1. Creación de un objeto de forma estática (en el stack)
    Punto3D p1; 

    // Uso de un Setter para asignar un valor a 'x'
    p1.setX(-1.14);

    /* * NOTA IMPORTANTE DE LA PIZARRA:
     * p1.x = -1.14; // Esto daría ERROR porque 'x' es un atributo privado.
     * Por eso usamos métodos públicos para interactuar con los datos.
     */

    // 2. Creación de un objeto de forma dinámica (en el heap) usando punteros
    // 'new' reserva memoria y devuelve la dirección del objeto.
    Punto3D *p2 = new Punto3D();

    // Cuando usamos punteros, accedemos a los métodos con el operador flecha '->'
    // Imprimimos la distancia al origen usando printf
    printf("La distancia de p2 al origen es %lf\n", p2->distancia_origen());

    // Liberación de memoria (buena práctica al usar 'new')
    delete p2;

    return 0;
}