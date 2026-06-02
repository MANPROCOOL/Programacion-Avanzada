#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// 1. LA CLASE BASE (PADRE): ANIMAL
// ============================================================================
class Animal {
protected: 
    // Recuerda la pizarra: Si usamos 'protected', permitimos que las clases
    // hijas accedan directamente, pero lo ocultamos del mundo exterior.
    string genero;
    string nombre_cientifico;
    bool extinto;

public:
    // Constructor base
    Animal(string gen = "Desconocido", string nombre = "Desconocido", bool ext = false) 
        : genero(gen), nombre_cientifico(nombre), extinto(ext) {}

    // ¡VIRTUAL ES LA CLAVE DEL POLIMORFISMO!
    // Al poner 'virtual', le decimos a C++: "Oye, si una clase hija tiene su propia 
    // versión de este método, ejecuta la de la clase hija, no la mía".
    virtual void emitir_sonido() {
        cout << "*Sonido de animal genérico*" << endl;
    }

    // Destructor virtual: Siempre que uses polimorfismo con punteros, el destructor 
    // de la clase padre DEBE ser virtual para evitar fugas de memoria (memory leaks).
    virtual ~Animal() {
        cout << "Destruyendo Animal..." << endl;
    }
};


// ============================================================================
// 2. CLASE INTERMEDIA: MAMIFERO (Hereda de Animal)
// ============================================================================
// Tu profesor escribió en la pizarra arriba en rojo: "protected" sobre la herencia.
// Vamos a repasar la tabla que dibujó en el centro de la pizarra:
//
// TIPO DE HERENCIA | PERMISO EN CLASE BASE | PERMISO EN CLASE HIJA
// -----------------------------------------------------------------
// public           | public / protected    | public / protected
// protected        | public / protected    | protected / protected  <-- ESTO HIZO EL PROFESOR
// private          | public / protected    | private / private
//
// Al heredar de forma 'protected', todo lo público y protegido de Animal se vuelve
// 'protected' dentro de Mamifero. Para mantener el ejemplo limpio y poder usarlo 
// en Gato, usaremos herencia pública clásica, pero ten en cuenta esa regla de la tabla.

class Mamifero : public Animal {
public:
    Mamifero(string gen, string nombre, bool ext) : Animal(gen, nombre, ext) {}
    
    virtual ~Mamifero() {
        cout << "Destruyendo Mamifero..." << endl;
    }
};


// ============================================================================
// 3. CLASE HIJA DERIVADA: GATO (Hereda de Mamifero)
// ============================================================================
// Aquí replicamos exactamente lo que escribió tu profesor en la pizarra izquierda:
class Gato : public Mamifero {
public:
    // Constructor de Gato
    Gato() : Mamifero("Felis", "Felis catus", false) {}

    // OVERRIDE: Le avisa al compilador que estamos sobrescribiendo el método del padre.
    // En la pizarra se lee: void emitir_sonido() override { cout << "miau"; }
    void emitir_sonido() override {
        cout << "miau" << endl;
    }

    // El destructor del gato (en la pizarra: ~Gato() { ... })
    ~Gato() override {
        cout << "Destruyendo Gato... ¡Adiós a una de sus 7 vidas!" << endl;
    }
};


// ============================================================================
// 4. FUNCIÓN PRINCIPAL (MAIN) - EXPLICACIÓN DE LOS PUNTEROS DE LA PIZARRA
// ============================================================================
int main() {
    cout << "--- 1. Creación de objetos normales y punteros simples ---" << endl;
    Gato g; // En la pizarra: Gato g;
    
    // El profesor escribió abajo a la izquierda: Animal *pg = &g;
    // Esto es completamente válido. Un puntero de tipo Animal puede guardar 
    // la dirección de memoria de un Gato porque un Gato ES UN Animal.
    Animal* pg = &g; 
    
    cout << "Llamando sonido desde el puntero pg (Animal* apuntando a Gato): ";
    pg->emitir_sonido(); // Gracias al 'virtual' y 'override', imprimirá "miau" y no el genérico.


    cout << "\n--- 2. Explicación de la pizarra derecha (Memoria Dinámica) ---" << endl;
    // Tu profesor escribió: Animal *g = new Gato();
    // NOTA: Para no confundir con la variable 'g' de arriba, lo llamaremos 'ptrGato'.
    Animal* ptrGato = new Gato(); 

    cout << "Llamando sonido desde ptrGato dinámico: ";
    ptrGato->emitir_sonido(); // Imprime "miau"

    // En la pizarra dice explícitamente: delete g;
    // Al hacer delete a un puntero de la clase base (Animal), si el destructor es 
    // VIRTUAL, se llamará en cadena: primero al destructor de ~Gato(), luego ~Mamifero() y al final ~Animal().
    cout << "Liberando memoria con delete:" << endl;
    delete ptrGato; 


    cout << "\n--- 3. ¿Qué significan las X grandes en la pizarra? ---" << endl;
    // Tu profesor tachó con una X gigante las siguientes líneas:
    // Animal a;
    // Animal a2 = new Animal(); (que además tiene un pequeño error de sintaxis en C++)
    //
    // ¿Por qué las tachó? 
    // Probablemente porque en el contexto del diseño de su clase, 'Animal' representa 
    // un concepto abstracto. No existen los animales "genéricos" caminando por la calle; 
    // existen gatos, perros o hipopótamos. Programar un objeto 'Animal' puro no tiene 
    // sentido en la lógica del problema. Queremos obligar al sistema a usar las clases hijas.

    return 0;
}