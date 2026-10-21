// Compilar: g++ -Wall -Wextra -std=c++11 es_palindromo.cpp -o es_palindromo
// Ejecutar: ./es_palindromo
#include <iostream>
#include <stdexcept>
#include <string>

// TDA de caracteres independientes de tus TDA de enteros o nodos.
class tPila {
    struct Nodo {
        char info;
        Nodo* sig;
        Nodo(char x, Nodo* s) : info(x), sig(s) {}
    };
    Nodo* tope;
    int cantidad;
    tPila(const tPila&) = delete;
    tPila& operator=(const tPila&) = delete;
public:
    tPila() : tope(nullptr), cantidad(0) {}
    ~tPila() { clear(); }
    int size() const { return cantidad; }
    void push(char x) {
        tope = new Nodo(x, tope);
        ++cantidad;
    }
    char topValue() const {
        if (!tope) throw std::logic_error("topValue sobre pila vacia");
        return tope->info;
    }
    void pop() {
        if (!tope) throw std::logic_error("pop sobre pila vacia");
        Nodo* viejo = tope;
        tope = tope->sig;
        delete viejo;
        --cantidad;
    }
    void clear() { while (cantidad > 0) pop(); }
};

class tCola {
    struct Nodo {
        char info;
        Nodo* sig;
        explicit Nodo(char x) : info(x), sig(nullptr) {}
    };
    Nodo* frente;
    Nodo* fin;
    int cantidad;
    tCola(const tCola&) = delete;
    tCola& operator=(const tCola&) = delete;
public:
    tCola() : frente(nullptr), fin(nullptr), cantidad(0) {}
    ~tCola() { clear(); }
    int size() const { return cantidad; }
    void enqueue(char x) {
        Nodo* nuevo = new Nodo(x);
        if (fin) fin->sig = nuevo;
        else frente = nuevo;
        fin = nuevo;
        ++cantidad;
    }
    char frontValue() const {
        if (!frente) throw std::logic_error("frontValue sobre cola vacia");
        return frente->info;
    }
    void dequeue() {
        if (!frente) throw std::logic_error("dequeue sobre cola vacia");
        Nodo* viejo = frente;
        frente = frente->sig;
        delete viejo;
        --cantidad;
        if (!frente) fin = nullptr;
    }
    void clear() { while (cantidad > 0) dequeue(); }
};

// Simulacion del TDA del enunciado: su representacion es privada.
// std::string se usa SOLO para cargar las pruebas, fuera de tu algoritmo.
class StringConsumer {
    tCola contenido;
public:
    explicit StringConsumer(const std::string& inicial) {
        for (char c : inicial) contenido.enqueue(c);
    }
    int length() const { return contenido.size(); }
    char extractChar() {
        // La excepcion ayuda a detectar un uso incorrecto durante las pruebas.
        if (length() == 0)
            throw std::logic_error("extractChar sobre StringConsumer vacio");
        char c = contenido.frontValue();
        contenido.dequeue();
        return c;
    }
};

bool esPalindromo(StringConsumer& texto) {

    tPila pilaux;
    tCola colaux;
    int tam = texto.length();
    for (int i = 0; i < tam ; i++){
        pilaux.push(texto.extractChar());
        colaux.enqueue(pilaux.topValue());
    }
    // ahora tengo la cadena duplicada en pila y cola
    while (pilaux.size()){
        if (pilaux.topValue() != colaux.frontValue()){
            return false;
        }
        pilaux.pop(), colaux.dequeue();
    }
    return true;

}

void probar(const std::string& entrada, bool esperado) {
    StringConsumer texto(entrada);
    std::cout << "Entrada: \"" << entrada << "\"\n";
    try {
        bool obtenido = esPalindromo(texto);
        std::cout << "Tu output: " << obtenido << '\n';
        std::cout << "Esperado:  " << esperado << '\n';
        std::cout << (obtenido == esperado ? "OK" : "REVISAR") << "\n\n";
    } catch (const std::exception& error) {
        std::cout << "Tu output: " << error.what() << '\n';
        std::cout << "Esperado:  " << esperado << "\n\n";
    }
}

int main() {
    std::cout << std::boolalpha;
    // Comparacion literal: mayusculas, espacios y signos son caracteres.
    // Se considera palindromo el string vacio.
    probar("", true);
    probar("a", true);
    probar("oso", true);
    probar("seres", true);
    probar("radar", true);
    probar("abba", true);
    probar("aa", true);
    probar("ab", false);
    probar("abca", false);
    probar("casa", false);
    probar("aaaa", true);
    probar("Oso", false);
    return 0;
}
