#include <iostream>

// Definición del píxel
struct Pixel {
    int r; 
    int g; 
    int b;
};

// Definición del TDA Icono
class Icono {
private:
    int H;
    int W;
    Pixel **imagen;

public:
    // Constructor para inicializar la matriz de píxeles
    Icono(int filas, int columnas) {
        H = filas;
        W = columnas;
        imagen = new Pixel*[H];
        for (int i = 0; i < H; i++) {
            imagen[i] = new Pixel[W];
        }
    }

    // Destructor para evitar memory leaks
    ~Icono() {
        for (int i = 0; i < H; i++) {
            delete[] imagen[i];
        }
        delete[] imagen;
    }

    // Método auxiliar para configurar la imagen en el main
    void setPixel(int i, int j, int r, int g, int b) {
        imagen[i][j].r = r;
        imagen[i][j].g = g;
        imagen[i][j].b = b;
    }

    // Operaciones expuestas según el enunciado
    int getWidth() { return W; }
    int getHeight() { return H; }
    Pixel* pixelInPos(int i, int j) { return &imagen[i][j]; }

    // =======================================================
    // TODO: IMPLEMENTA ESTE MÉTODO
    // =======================================================
    Pixel* getBrightAndGrayRow(int i, float alpha) {

        int ancho = getWidth(); 
        Pixel* resultado = new Pixel[ancho];
        for (int j = 0; j < ancho; j++){
            Pixel* actual = pixelInPos(i,j);
            resultado[j].r = actual->r * 0.3 * alpha;
            resultado[j].g = actual->g * 0.59 * alpha;
            resultado[j].b = actual->b * 0.11 * alpha;
        }
        return resultado; // Reemplaza esto con tu arreglo resultante
    }
};

int main() {
    // Optimización de lectura para jueces en línea
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int H, W;
    int fila_objetivo;
    float alpha;

    // Leer tamaño, fila a transformar y el factor alpha
    if (!(std::cin >> H >> W >> fila_objetivo >> alpha)) return 0;

    Icono icono(H, W);

    // Leer la matriz de píxeles (cada píxel tiene 3 enteros R G B)
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int r, g, b;
            std::cin >> r >> g >> b;
            icono.setPixel(i, j, r, g, b);
        }
    }

    // Llamada a tu algoritmo
    Pixel* fila_transformada = icono.getBrightAndGrayRow(fila_objetivo, alpha);

    // Imprimir el resultado esperado si el puntero no es nulo
    if (fila_transformada != nullptr) {
        int ancho = icono.getWidth();
        for (int j = 0; j < ancho; j++) {
            std::cout << "(" << fila_transformada[j].r << "," 
                             << fila_transformada[j].g << "," 
                             << fila_transformada[j].b << ")" 
                      << (j == ancho - 1 ? "" : " ");
        }
        std::cout << "\n";

        // Liberar la memoria del arreglo devuelto por tu función
        delete[] fila_transformada;
    }

    return 0;
}