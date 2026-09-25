#include <iostream>
#include <string>

struct Curso {
    int id;         // Identificador numérico del curso (0 a N-1)
    std::string sigla;   // Sigla
    int semestre;   // Semestre que corresponde por malla
    int creditos;   // Créditos del curso
};

class Malla {
private:
    Curso *cursos;          // Arreglo de cursos de la malla (ordenado por semestre)
    bool **prerrequisitos;  // Matriz booleana [N][N]
    int N;                  // Cantidad de cursos de la malla

public:
    // Constructor
    Malla(int totalCursos) {
        N = totalCursos;
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

    // Métodos auxiliares para configurar la malla en el main
    void setCurso(int idx, int id, std::string sigla, int sem, int cred) {
        if (idx >= 0 && idx < N) {
            cursos[idx].id = id;
            cursos[idx].sigla = sigla;
            cursos[idx].semestre = sem;
            cursos[idx].creditos = cred;
        }
    }

    void agregarPrerrequisito(int id_a, int id_b) {
        if (id_a >= 0 && id_a < N && id_b >= 0 && id_b < N) {
            prerrequisitos[id_a][id_b] = true;
        }
    }

    Curso* getCursoPtr(int idx) {
        if (idx >= 0 && idx < N) return &cursos[idx];
        return nullptr;
    }

    int getCantidadCursos() const { return N; }

    // ==========================================================
    // Métodos provistos por el TDA según la especificación
    // ==========================================================
    
    // Retorna true si el curso 'a' se encuentra en el arreglo 'aprobados' (de tamaño na)
    bool estaAprobado(Curso a, Curso *aprobados, int na) {
        for (int i = 0; i < na; i++) {
            if (aprobados[i].id == a.id) {
                return true;
            }
        }
        return false;
    }

    // Retorna un arreglo dinámico de tamaño 'n' con los prerrequisitos del curso 'a'
    Curso* listarPrerrequisitos(Curso *a, int &n) {
        if (a == nullptr) {
            n = 0;
            return nullptr;
        }

        int count = 0;
        for (int i = 0; i < N; i++) {
            if (prerrequisitos[i][a->id]) {
                count++;
            }
        }

        n = count;
        if (n == 0) return nullptr;

        Curso* lista = new Curso[n];
        int idx = 0;
        for (int i = 0; i < N; i++) {
            if (prerrequisitos[i][a->id]) {
                lista[idx++] = cursos[i];
            }
        }
        return lista;
    }

    // =======================================================
    // TODO: IMPLEMENTA ESTE MÉTODO
    // =======================================================
    // Parámetros agregados necesarios:
    // - int na: cantidad de cursos en el arreglo 'aprobados'.
    // - int &np: variable por referencia para retornar la cantidad de cursos prioritarios hallados.
    Curso* cursosPorTomar(Curso *aprobados, int na, int &np) {
        // CONDICIONES PARA QUE UN CURSO 'C' SEA PRIORITARIO POR TOMAR:
        // 1. NO debe estar ya aprobado (!estaAprobado(cursos[i], aprobados, na)).
        // 2. TODOS sus prerrequisitos deben estar aprobados (usar listarPrerrequisitos
        //    y verificar con estaAprobado cada uno de ellos).
        np = 0;

        for (int i = 0; i < N; i++) {// Pasada 1: Contar cuántos cursos cumplen los requisitos
            if (!estaAprobado(cursos[i], aprobados, na)) {
                int taman = 0;
                Curso* requi = listarPrerrequisitos(&cursos[i], taman);
                bool puedo = true;

                for (int j = 0; j < taman; j++) {
                    if (!estaAprobado(requi[j], aprobados, na)) {
                        puedo = false;
                    }
                }
                delete[] requi;
                if (puedo) {np++;}
            }
        }
        // Si no hay cursos disponibles, retornamos nullptr
        if (np == 0) {
            return nullptr;
        }
        // Pasada 2: Reservar la memoria EXACTA y llenar el arreglo
        Curso* resultado = new Curso[np];
        for (int i = 0, w = 0; i < N; i++) {
            if (!estaAprobado(cursos[i], aprobados, na)) {
                int taman = 0;
                Curso* requi = listarPrerrequisitos(&cursos[i], taman);
                bool puedo = true;

                for (int j = 0; j < taman; j++) {
                    if (!estaAprobado(requi[j], aprobados, na)) {
                        puedo = false;
                        break;
                    }
                }
                delete[] requi;

                if (puedo) {
                    resultado[w++] = cursos[i];
                }
            }
        }

        return resultado;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int totalCursos;
    if (!(std::cin >> totalCursos)) return 0;

    Malla malla(totalCursos);

    // Cargar los cursos (asumidos ordenados por semestre)
    for (int i = 0; i < totalCursos; i++) {
        int id, sem, cred;
        std::string sigla;
        std::cin >> id >> sigla >> sem >> cred;
        malla.setCurso(i, id, sigla, sem, cred);
    }

    // Cargar prerrequisitos
    int totalPrereq;
    std::cin >> totalPrereq;
    for (int i = 0; i < totalPrereq; i++) {
        int id_a, id_b;
        std::cin >> id_a >> id_b;
        malla.agregarPrerrequisito(id_a, id_b);
    }

    // Cargar cursos aprobados
    int cantAprobados;
    std::cin >> cantAprobados;
    Curso* aprobados = (cantAprobados > 0) ? new Curso[cantAprobados] : nullptr;

    for (int i = 0; i < cantAprobados; i++) {
        int id;
        std::cin >> id;
        // Buscamos el curso para cargarlo en el arreglo de aprobados
        for (int k = 0; k < totalCursos; k++) {
            Curso* c = malla.getCursoPtr(k);
            if (c && c->id == id) {
                aprobados[i] = *c;
                break;
            }
        }
    }

    int np = 0;
    Curso* recomendados = malla.cursosPorTomar(aprobados, cantAprobados, np);

    // Mostrar salida
    std::cout << "Cursos prioritarios a tomar (" << np << "):\n";
    if (recomendados != nullptr && np > 0) {
        for (int i = 0; i < np; i++) {
            std::cout << "- " << recomendados[i].sigla 
                      << " (Semestre " << recomendados[i].semestre << ")\n";
        }
        delete[] recomendados;
    } else {
        std::cout << "No hay cursos disponibles para tomar en este momento.\n";
    }

    if (aprobados != nullptr) delete[] aprobados;

    return 0;
}