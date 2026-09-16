#include <iostream>

// El tipo de dato se cambia a int para ajustarse a la señal espacial
typedef int tElemLista;

// Nodo de la lista doblemente enlazada
struct tNodo {
    tElemLista info;
    tNodo* sig;
    tNodo* ant; // Puntero al nodo anterior
};

class tLista {
private:
    tNodo* head;           // Nodo centinela inicial
    tNodo* tail;           // Puntero al último nodo
    tNodo* curr;           // Puntero al nodo previo a la posición actual
    unsigned int listSize; // Tamaño actual de la lista
    unsigned int pos;      // Posición lógica actual (0 <= pos <= listSize)

public:
    // Constructor (inicializa nodo centinela)
    tLista() {
        curr = tail = head = new tNodo;
        head->sig = NULL;
        head->ant = NULL;
        listSize = 0;
        pos = 0;
    }

    // Destructor
    ~tLista() {
        clear();
        delete head;
    }

    // Vacía la lista
    void clear() {
        curr = head;
        pos = 0;
        while (head->sig != NULL) {
            tNodo* temp = head->sig;
            head->sig = temp->sig;
            delete temp;
        }
        head->sig = NULL;
        curr = tail = head;
        listSize = 0;
        pos = 0;
    }

    // Agrega al final de la lista
    void append(tElemLista item) {
        tNodo* aux = new tNodo;
        aux->info = item;
        aux->sig = NULL;
        aux->ant = tail;

        tail->sig = aux;
        tail = aux;
        listSize++;
    }

    // Método de utilidad para imprimir el resultado para el juez
    void print() const {
        // Recordar que head es centinela, el primer valor real es head->sig
        tNodo* temp = head->sig; 
        while (temp != NULL) {
            std::cout << temp->info << (temp->sig != NULL ? " " : "");
            temp = temp->sig;
        }
        std::cout << "\n";
    }

    // =======================================================
    // TODO: IMPLEMENTA ESTE MÉTODO
    // =======================================================
    void revertirPares() {
        // RESTRICCIONES DEL COMITÉ ESTANDARIZADOR / JUEZ:
        // 1. Complejidad O(N).
        // 2. NO puedes usar "new" (no crear nuevos nodos).
        // 3. NO puedes intercambiar los valores "info".
        // 4. Solo puedes modificar los punteros "sig" y "ant".
        // 5. NO usar métodos de alto nivel (insert, erase, moveToPos).
        
        // PISTA: Tu primer nodo de datos es head->sig
        
        
        
    }
};

int main() {
    // Optimización de lectura para jueces en línea
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    // Leer la cantidad de datos
    if (!(std::cin >> N)) return 0;

    tLista lista;

    // Leer la señal y cargarla en la lista
    for (int i = 0; i < N; i++) {
        int valor;
        std::cin >> valor;
        lista.append(valor);
    }

    // Llamada a tu algoritmo
    lista.revertirPares();

    // Salida esperada
    lista.print();

    return 0;
}