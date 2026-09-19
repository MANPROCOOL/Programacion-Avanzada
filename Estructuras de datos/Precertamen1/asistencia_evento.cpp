#include <iostream>
#include <string>

// Definición del struct según el enunciado
struct Persona {
    std::string nombre; // Dato personal de ejemplo
};

// Definición del TDA AsistenciaEvento
class AsistenciaEvento {
private:
    bool* asistencia;
    Persona* inscritos;
    int cantidad_de_inscritos;

public:
    // Constructor para inicializar los datos de prueba
    AsistenciaEvento(int n) {
        cantidad_de_inscritos = n;
        asistencia = new bool[n];
        inscritos = new Persona[n];
    }

    ~AsistenciaEvento() {
        delete[] asistencia;
        delete[] inscritos;
    }

    // Método auxiliar para configurar datos en el main
    void registrarPersona(int i, std::string nombre, bool asistio) {
        inscritos[i].nombre = nombre;
        asistencia[i] = asistio;
    }

    // ==========================================================
    // Operaciones del TDA (implementadas para simular el juez)
    // ==========================================================
    Persona getInscrito(int i) {
        return inscritos[i];
    }

    int selectAsistente(int j) {
        int conteo_asistentes = 0;
        // Asumiendo que j empieza en 1 (el primer asistente es j=1)
        for (int i = 0; i < cantidad_de_inscritos; i++) {
            if (asistencia[i]) {
                conteo_asistentes++;
                if (conteo_asistentes == j) {
                    return i;
                }
            }
        }
        return -1; // Retorna -1 cuando no existe el j-ésimo asistente
    }

    int getCantidadDeInscritos() {
        return cantidad_de_inscritos;
    }
};

// =======================================================
// TODO: IMPLEMENTA ESTA FUNCIÓN
// =======================================================
// Se agregó "int &k" por referencia para saber de qué tamaño es el arreglo resultante
Persona* datosAsistentes(AsistenciaEvento *AE, int &k) {
    // RESTRICCIÓN: Complejidad O(k). 
    // ESTÁ PROHIBIDO usar un for desde 0 hasta AE->getCantidadDeInscritos().

    k = 0; 
    
    // 1. Necesitas descubrir cuántos asistentes reales hay (k) sin recorrer todo.
    //    Usa un while llamando a AE->selectAsistente(j). Empieza buscando el j=1.
    //    Sigue aumentando 'j' hasta que selectAsistente te retorne -1.
    //    Cuando te retorne -1, ya sabes cuántos asistentes hay (k).
    
    // 2. Ahora que sabes k, crea el arreglo dinámico: 
    //    Persona* arregloAsistentes = new Persona[k];
    
    // 3. Vuelve a iterar j desde 1 hasta k. 
    //    - Obtén el índice real usando selectAsistente(j).
    //    - Usa ese índice en getInscrito(indice) para traer los datos.
    //    - Guárdalos en arregloAsistentes[j-1].
    
    // 4. Retorna el arreglo.

    return nullptr;
}

int main() {
    // Optimización de lectura
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N; // Cantidad total de inscritos
    if (!(std::cin >> N)) return 0;

    AsistenciaEvento evento(N);

    // Lectura de los inscritos: nombre y si asistió (1) o no (0)
    for (int i = 0; i < N; i++) {
        std::string nombre;
        int asistio;
        std::cin >> nombre >> asistio;
        evento.registrarPersona(i, nombre, asistio == 1);
    }

    int k_asistentes = 0;
    
    // Llamada a tu algoritmo
    Persona* resultado = datosAsistentes(&evento, k_asistentes);

    // Salida esperada
    if (resultado != nullptr) {
        for (int i = 0; i < k_asistentes; i++) {
            std::cout << resultado[i].nombre << (i == k_asistentes - 1 ? "" : " ");
        }
        std::cout << "\n";

        // Liberar la memoria devuelta por tu función
        delete[] resultado;
    } else if (k_asistentes == 0) {
        std::cout << "Nadie asistio\n";
    }

    return 0;
}