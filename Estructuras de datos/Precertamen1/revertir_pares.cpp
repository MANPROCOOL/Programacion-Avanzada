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
        if (head->sig == NULL) return; // Lista vacía

        tNodo* curr = head->sig;


        while (curr != NULL) {
            // Buscamos el inicio de una secuencia de pares
            if (curr->info % 2 == 0) {
                tNodo* inicio_pares = curr;
                tNodo* previo_impar = curr->ant; // Puede ser el centinela, eso está bien

                // Avanzamos hasta encontrar el fin de la secuencia de pares
                tNodo* fin_pares = curr;
                int contador = 0;
                
                while (fin_pares != NULL && fin_pares->info % 2 == 0) {
                    contador++;
                    curr = fin_pares->sig; // curr avanza para el futuro
                    if (curr != NULL && curr->info % 2 == 0) {
                        fin_pares = curr;
                    } else {
                        break;
                    }
                }

                // Si encontramos al menos 2 pares contiguos, invertimos la sublista
                if (contador >= 2) {
                    tNodo* siguiente_impar = fin_pares->sig;
                    
                    // Proceso de inversión de punteros dentro de la sublista de pares
                    tNodo* nodo_actual = inicio_pares;
                    tNodo* temp = NULL;
                    
                    while (nodo_actual != siguiente_impar) {
                        temp = nodo_actual->sig;
                        // Intercambiamos sig y ant
                        nodo_actual->sig = nodo_actual->ant;
                        nodo_actual->ant = temp;
                        
                        nodo_actual = temp; // avanzo al sgte nodo
                    }

                    // Reconectamos la sublista invertida con el resto de la lista original
                    previo_impar->sig = fin_pares;
                    fin_pares->ant = previo_impar;
                    
                    inicio_pares->sig = siguiente_impar; // inicio_pares ahora es el final de la sublista
                    if (siguiente_impar != NULL) {
                        siguiente_impar->ant = inicio_pares;
                    } else {
                        // Si el siguiente es NULL, significa que la secuencia par llegó al final de la lista
                        tail = inicio_pares;
                    }
                }
            } else {
                curr = curr->sig; // si no encontramos un par, pasamos de largo
            }
        }
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