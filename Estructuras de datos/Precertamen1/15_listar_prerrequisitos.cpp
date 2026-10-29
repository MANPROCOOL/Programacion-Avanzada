#include <iostream>
#include <string>

// Struct Curso según la especificación del enunciado
struct Curso {
    int id;         // Identificador numérico del curso (0 a N-1)
    std::string sigla;   // Sigla
    int semestre;   // Semestre que corresponde por malla
    int creditos;   // Créditos del curso
};

class Malla {
private:
    Curso *cursos;          // Arreglo de cursos de la malla
    bool **prerrequisitos;  // Matriz booleana [N][N]
    int N;                  // Cantidad de cursos de la malla

public:
    // Constructor para inicializar una malla de ejemplo
    Malla(int cantidadCursos) {
        N = cantidadCursos;
        cursos = new Curso[N];
        
        prerrequisitos = new bool*[N];
        for (int i = 0; i < N; i++) {
            prerrequisitos[i] = new bool[N];
            for (int j = 0; j < N; j++) {
                prerrequisitos[i][j] = false;
            }
        }
    }

    // Destructor
    ~Malla() {
        delete[] cursos;
        for (int i = 0; i < N; i++) {
            delete[] prerrequisitos[i];
        }
        delete[] prerrequisitos;
    }

    // Método auxiliar para configurar un curso
    void setCurso(int id, std::string sigla, int sem, int cred) {
        if (id >= 0 && id < N) {
            cursos[id].id = id;
            cursos[id].sigla = sigla;
            cursos[id].semestre = sem;
            cursos[id].creditos = cred;
        }
    }

    // Método auxiliar para establecer una relación de prerrequisito (a es prerrequisito de b)
    void agregarPrerrequisito(int id_a, int id_b) {
        if (id_a >= 0 && id_a < N && id_b >= 0 && id_b < N) {
            prerrequisitos[id_a][id_b] = true;
        }
    }

    Curso* getCursoPtr(int id) {
        if (id >= 0 && id < N) return &cursos[id];
        return nullptr;
    }

    // =======================================================
    // TODO: IMPLEMENTA ESTE MÉTODO
    // =======================================================
    // Nota: Se agrega el parámetro 'int &cant' por referencia para 
    // retornar el tamaño del arreglo resultante sin gastar memoria extra.
    Curso* listarPrerrequisitos(Curso *a, int &cant) {
        if (a == nullptr) {
            cant = 0;
            return nullptr;
        }
        int reales = 0;
        for (int i = 0; i < N; i++) { // Pasada 1: Contar los prerrequisitos sin pedir memoria extra
            if (prerrequisitos[cursos[i].id][a->id]) {
                reales++;
            }
        }
        cant = reales;
        if (reales == 0) { // Si no tiene prerrequisitos, retornamos nullptr de inmediato
            return nullptr;
        }
        // Pasada 2: Reservar ÚNICAMENTE la memoria justa y necesaria
        Curso* final = new Curso[reales];
        int idx = 0;
        for (int i = 0; i < N; i++) {
            if (prerrequisitos[cursos[i].id][a->id]) {
                final[idx++] = cursos[i];
            }
        }
        return final;
    }
};

int main() {
    // Optimización de I/O para pruebas
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int totalCursos;
    if (!(std::cin >> totalCursos)) return 0;

    Malla malla(totalCursos);

    // Leer los cursos
    for (int i = 0; i < totalCursos; i++) {
        std::string sigla;
        int sem, cred;
        std::cin >> sigla >> sem >> cred;
        malla.setCurso(i, sigla, sem, cred);
    }

    // Leer la cantidad de relaciones de prerrequisitos
    int totalPrerrequisitos;
    std::cin >> totalPrerrequisitos;
    for (int i = 0; i < totalPrerrequisitos; i++) {
        int id_a, id_b; // id_a es prerrequisito de id_b
        std::cin >> id_a >> id_b;
        malla.agregarPrerrequisito(id_a, id_b);
    }

    // ID del curso a consultar
    int targetId;
    std::cin >> targetId;

    Curso* objetivo = malla.getCursoPtr(targetId);
    int cantidadPrerrequisitos = 0;

    // Llamada a tu método
    Curso* listaPrereq = malla.listarPrerrequisitos(objetivo, cantidadPrerrequisitos);

    // Salida esperada
    if (listaPrereq != nullptr && cantidadPrerrequisitos > 0) {
        std::cout << "Prerrequisitos de " << objetivo->sigla << ":\n";
        for (int i = 0; i < cantidadPrerrequisitos; i++) {
            std::cout << "- " << listaPrereq[i].sigla 
                      << " (Semestre " << listaPrereq[i].semestre << ")\n";
        }
        delete[] listaPrereq; // Liberar la memoria retornada
    } else {
        std::cout << "El curso " << objetivo->sigla << " no tiene prerrequisitos.\n";
    }

    return 0;
}