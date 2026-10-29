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
    // 1. Descubrir cuántos asistentes reales hay (k)
    int j = 1; // Comenzamos a contar desde el 1er asistente
    while (AE->selectAsistente(j) != -1) {
        j++;
    }
    
    // Si salió del ciclo, el j actual devolvió -1. 
    // Por lo tanto, la cantidad de asistentes es j - 1.
    k = j - 1; 
    
    // Buenas prácticas: si no hay asistentes, retornamos nulo
    if (k == 0) return nullptr;
    
    // 2. Crear el arreglo dinámico con el tamaño exacto 'k'
    Persona* arregloAsistentes = new Persona[k];
    
    // 3. Volver a iterar desde el 1er asistente hasta el k-ésimo
    for (int i = 1; i <= k; i++) {
        int indiceReal = AE->selectAsistente(i);
        
        // Guardamos en el arreglo (que sí usa índices desde 0, por ende i - 1)
        arregloAsistentes[i - 1] = AE->getInscrito(indiceReal);
    }
    
    // 4. Retornar el arreglo
    return arregloAsistentes;
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