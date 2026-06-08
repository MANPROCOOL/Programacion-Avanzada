#include <iostream>
#include <utility> // Biblioteca necesaria para usar 'std::pair' y 'std::make_pair'
#include <string>  // Biblioteca necesaria para usar 'std::string'

using namespace std;

int main() {
    // =========================================================================
    // EXPLICACIÓN DE STD::PAIR:
    // Un 'pair' es una estructura de la librería estándar que permite almacenar
    // dos elementos (que pueden ser de igual o diferente tipo) en un solo objeto.
    // El primer elemento se accede con '.first' y el segundo con '.second'.
    // =========================================================================

    cout << "--- GUIA PRACTICA DE STD::PAIR INSPIRADA EN LA PIZARRA ---\n\n";

    // -------------------------------------------------------------------------
    // CASO 1: Declaración clásica y asignación de valores elemento por elemento.
    // -------------------------------------------------------------------------
    // Declaramos un par llamado 'p1' que guardará dos números enteros (int, int)
    pair<int, int> p1; 
    
    // Asignamos el valor 8 al primer elemento
    p1.first = 8;
    // Asignamos el valor 10 al segundo elemento
    p1.second = 10;

    cout << "Par p1: (" << p1.first << ", " << p1.second << ")\n";


    // -------------------------------------------------------------------------
    // CASO 2: Inicialización directa usando llaves { } (Disponible desde C++11)
    // -------------------------------------------------------------------------
    // Declaramos un par llamado 'p2' que guarda un decimal y un entero (float, int)
    // Se inicializa inmediatamente con los valores 5.8 y 7.
    pair<float, int> p2 = {5.8, 7};

    cout << "Par p2: (" << p2.first << ", " << p2.second << ")\n";


    // -------------------------------------------------------------------------
    // CASO 3: Inicialización usando la función helper 'make_pair'
    // -------------------------------------------------------------------------
    // 'make_pair' deduce automáticamente los tipos de datos sin tener que especificarlos de nuevo.
    // Creamos 'p3' que guarda dos decimales (float, float) con los valores 7.1 y 3.8.
    pair<float, float> p3 = make_pair(7.1, 3.8);

    cout << "Par p3: (" << p3.first << ", " << p3.second << ")\n";


    // -------------------------------------------------------------------------
    // CASO 4: Pares Anidados (Estructuras complejas) -> Explicación del diagrama
    // -------------------------------------------------------------------------
    // Aquí es donde el código se vuelve interesante y corresponde al dibujo de la derecha.
    // Declaramos 'p4', un par donde:
    //   - El primer elemento (.first) es un entero (int).
    //   - El segundo elemento (.second) es OTRO PAR entero compuesto de dos cadenas (pair<string, string>).
    pair<int, pair<string, string>> p4 = make_pair(8, make_pair("Hola", "Adios"));

    /* EXPLICACIÓN DEL DIAGRAMA DE LA PIZARRA:
       El profesor dibujó cajas dentro de cajas para representar cómo se almacena p4 en memoria:
       
       [ Variable p4 ] -------------------------------------------------------+
       |                                                                      |
       |  p4.first  ==> [ 8 ]                                                 |
       |                                                                      |
       |  p4.second ==> [ Sub-par interno ] -------------------------------+  |
       |                |                                                  |  |
       |                | (p4.second).first  ==> [ "Hola" ]                |  |
       |                |                                                  |  |
       |                | (p4.second).second ==> [ "Adios" ]               |  |
       |                +--------------------------------------------------+  |
       +----------------------------------------------------------------------+
    */

    cout << "\nValores iniciales de p4:";
    cout << "\n - p4.first: " << p4.first;
    cout << "\n - p4.second.first: " << p4.second.first;
    cout << "\n - p4.second.second: " << p4.second.second << "\n";


    // -------------------------------------------------------------------------
    // CASO 5: Modificación de elementos en un par anidado
    // -------------------------------------------------------------------------
    // Para acceder al último elemento ("Adios") y cambiarlo por "Bye", debemos:
    // 1. Entrar al segundo elemento de p4 usando: p4.second (esto nos da el par interno).
    // 2. Modificar el segundo elemento de ese par interno usando: .second
    (p4.second).second = "Bye"; // Los paréntesis ayudan a entender la jerarquía

    cout << "\nValores modificados de p4 (despues del cambio):";
    cout << "\n - p4.first: " << p4.first;
    cout << "\n - p4.second.first: " << p4.second.first;
    cout << "\n - p4.second.second (Modificado): " << p4.second.second << "\n";


    return 0; // Fin del programa con éxito
}