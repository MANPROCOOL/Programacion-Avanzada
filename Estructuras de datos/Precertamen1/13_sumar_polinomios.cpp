#include <iostream>
#include <algorithm> // Para std::max

// TDA monomio básico asumido por el contexto
struct monomio {
    float coeficiente;
};

class polinomio {
private:
    monomio *P;
    int grado; 

public:
    // Constructor por defecto
    polinomio() : P(nullptr), grado(-1) {}

    // Constructor que inicializa el polinomio con un grado específico
    polinomio(int g) {
        grado = g;
        P = new monomio[grado + 1];
        for (int i = 0; i <= grado; i++) {
            P[i].coeficiente = 0.0f;
        }
    }

    // Constructor de copia (necesario porque la función retorna un polinomio por valor)
    polinomio(const polinomio& otro) {
        grado = otro.grado;
        if (grado >= 0) {
            P = new monomio[grado + 1];
            for (int i = 0; i <= grado; i++) {
                P[i].coeficiente = otro.P[i].coeficiente;
            }
        } else {
            P = nullptr;
        }
    }

    // Destructor
    ~polinomio() {
        if (P != nullptr) {
            delete[] P;
        }
    }

    // Operaciones del TDA exigidas
    int getGrado() {
        return grado;
    }

    float getMonomio(int e) {
        if (e < 0 || e > grado) {
            return 0.0f;
        }
        return P[e].coeficiente;
    }

    void setMonomio(float c, int e) {
        if (e < 0) return;

        // Si el exponente supera el grado actual, ampliamos el arreglo
        if (e > grado) {
            int nuevoGrado = e;
            monomio* nuevoP = new monomio[nuevoGrado + 1];

            // Copiamos los coeficientes existentes
            for (int i = 0; i <= grado; i++) {
                nuevoP[i] = P[i];
            }
            // Rellenamos con 0.0 los nuevos exponentes intermedios
            for (int i = grado + 1; i <= nuevoGrado; i++) {
                nuevoP[i].coeficiente = 0.0f;
            }

            // Liberamos el arreglo anterior y actualizamos puntero y grado
            delete[] P;
            P = nuevoP;
            grado = nuevoGrado;
        }

        // Asignamos el valor en el exponente indicado
        P[e].coeficiente = c;
    }

    // Método auxiliar para el juez virtual
    void print() {
        bool primero = true;
        for (int i = grado; i >= 0; i--) {
            float c = getMonomio(i);
            if (c != 0.0f || (grado == 0 && i == 0)) {
                if (!primero && c > 0) std::cout << "+";
                std::cout << c;
                if (i > 0) std::cout << "x^" << i;
                primero = false;
            }
        }
        if (primero) std::cout << "0";
        std::cout << "\n";
    }
};

// =======================================================
// TODO: IMPLEMENTA ESTA FUNCIÓN
// =======================================================
polinomio sumarPolinomios(polinomio *p1, polinomio *p2) {
    // RESTRICCIÓN DE COMPLEJIDAD: O(max{n, m})
    
    polinomio resultado;    
    int maximogrado = (p1->getGrado() >= p2->getGrado()) ? p1->getGrado(): p2->getGrado();
    for (int i = 0; i < maximogrado; i++){
        resultado.setMonomio(p1->getMonomio(i) + p2->getMonomio(i), i);
    }
    return resultado; // Reemplaza esto con tu objeto polinomio resultante
}

int main() {
    // Optimización de I/O para jueces en línea
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int grado1, grado2;

    // Lectura del primer polinomio
    if (!(std::cin >> grado1)) return 0;
    polinomio p1(grado1);
    for (int i = 0; i <= grado1; i++) {
        float c;
        std::cin >> c;
        p1.setMonomio(c, i);
    }

    // Lectura del segundo polinomio
    std::cin >> grado2;
    polinomio p2(grado2);
    for (int i = 0; i <= grado2; i++) {
        float c;
        std::cin >> c;
        p2.setMonomio(c, i);
    }

    // Llamada a tu función
    polinomio resultado = sumarPolinomios(&p1, &p2);

    // Salida esperada
    resultado.print();

    return 0;
}