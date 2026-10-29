#include <iostream>
#include <string>
#include <algorithm>

class Editor {
private:
    std::string linea[5000];
    int cantidad_lineas;

public:
    // Constructor básico
    Editor() : cantidad_lineas(0) {}

    // Métodos expuestos según el enunciado
    int get_cantidad_lineas() { 
        return cantidad_lineas; 
    }
    
    char getChar(int i, int j) { 
        return linea[i][j]; 
    }
    
    std::string getLinea(int i) { 
        return linea[i]; 
    }

    // Método auxiliar para construir los objetos en el main
    void agregarLinea(const std::string& texto) {
        if (cantidad_lineas < 5000) {
            linea[cantidad_lineas++] = texto;
        }
    }
};

// =======================================================
// TODO: IMPLEMENTA ESTA FUNCIÓN
// =======================================================
bool* contarVocales(Editor* texto1, Editor* texto2) {
    // RESTRICCIÓN DE COMPLEJIDAD: O(min{n, m} * l)
    int minimo;
    if (texto1->get_cantidad_lineas() <= texto2->get_cantidad_lineas()){
        minimo = texto1->get_cantidad_lineas();
    }
    else {minimo = texto2->get_cantidad_lineas();}
    bool* resultado = new bool[minimo];
    for (int i = 0; i < minimo; i++){
        int voc1 = 0, voc2 = 0;
        std::string linea1, linea2;
        linea1 = texto1->getLinea(i);
        linea2 = texto2->getLinea(i);
        for (int j = 0; j < linea1.size(); j++) {
            char c = linea1[j];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                voc1++;
            }
        }
        
        // Contar vocales en linea2
        for (int j = 0; j < linea2.size(); j++) {
            char c = linea2[j];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                voc2++;
            }
        }
        if (voc1 > voc2){resultado[i]=1;}
        else {resultado[i]=0;}
        voc1 = 0, voc2 = 0;
    }
    return resultado;
}

int main() {
    // Optimización de lectura para jueces en línea
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    
    // Leer número de líneas del primer texto
    if (!(std::cin >> n)) return 0;
    std::cin.ignore(); // Limpiar el salto de línea

    Editor texto1;
    for (int i = 0; i < n; i++) {
        std::string linea_texto;
        std::getline(std::cin, linea_texto);
        texto1.agregarLinea(linea_texto);
    }

    // Leer número de líneas del segundo texto
    std::cin >> m;
    std::cin.ignore();

    Editor texto2;
    for (int i = 0; i < m; i++) {
        std::string linea_texto;
        std::getline(std::cin, linea_texto);
        texto2.agregarLinea(linea_texto);
    }

    // Llamada a tu algoritmo
    bool* resultado = contarVocales(&texto1, &texto2);

    // Salida esperada
    if (resultado != nullptr) {
        int limite = std::min(n, m);
        for (int i = 0; i < limite; i++) {
            std::cout << (resultado[i] ? "true" : "false") << (i == limite - 1 ? "" : " ");
        }
        std::cout << "\n";

        // Liberar la memoria del arreglo devuelto por tu función
        delete[] resultado;
    }

    return 0;
}