#include <iostream>
#include <string>

// Struct Usuario según la especificación del enunciado
struct Usuario {
    std::string rut;
    int saldo;
};

// Clase TarjetaPip según la especificación del enunciado
class TarjetaPip {
private:
    Usuario* tarjeta;
    int cantidadMovimientosMes;
    int saldoInicialMes;
    int movimientosMes[500];

public:
    TarjetaPip() {
        tarjeta = new Usuario();
        cantidadMovimientosMes = 0;
        saldoInicialMes = 0;
    }

    ~TarjetaPip() {
        delete tarjeta;
    }

    // Métodos para configurar datos desde el main
    void setDatos(std::string rut, int saldoActual, int saldoInicial, int cantMovs) {
        tarjeta->rut = rut;
        tarjeta->saldo = saldoActual;
        saldoInicialMes = saldoInicial;
        cantidadMovimientosMes = cantMovs;
    }

    void setMovimiento(int pos, int monto) {
        if (pos >= 0 && pos < 500) {
            movimientosMes[pos] = monto;
        }
    }

    // Getters indicados en la especificación
    int getCantidadMovimientosMes() { return cantidadMovimientosMes; }
    int getSaldoInicialMes() { return saldoInicialMes; }
    int* getMovimientosMes() { return movimientosMes; }
    Usuario* getTarjeta() { return tarjeta; }

    void cargar(int monto) { tarjeta->saldo += monto; }
    void pagarViaje(int costo) { tarjeta->saldo -= costo; }
};

// =======================================================
// TODO: IMPLEMENTA ESTA FUNCIÓN
// =======================================================
int cuadratura(TarjetaPip *lista, int total) {
    // REGLA DE CUADRATURA:
    // saldoEsperado = saldoInicialMes + suma(movimientosMes)
    // Un usuario NO cumple cuadratura si tarjeta->saldo != saldoEsperado.
    int incorrectos = 0;
    for (int i = 0; i < total; i++){
        int mov = lista[i].getCantidadMovimientosMes();
        int* saldos = lista[i].getMovimientosMes();
        int suma = lista[i].getSaldoInicialMes();
        for (int j = 0; j < mov; j++){
            suma += saldos[j];
        }
        if (suma != lista[i].getTarjeta()->saldo){
            incorrectos++;
        }
    }

    return incorrectos;
}

int main() {
    // Optimización para jueces en línea / pruebas
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int total;
    if (!(std::cin >> total)) return 0;

    TarjetaPip* lista = new TarjetaPip[total];

    for (int i = 0; i < total; i++) {
        std::string rut;
        int saldoActual, saldoInicial, cantMovs;
        std::cin >> rut >> saldoActual >> saldoInicial >> cantMovs;

        lista[i].setDatos(rut, saldoActual, saldoInicial, cantMovs);

        for (int m = 0; m < cantMovs; m++) {
            int monto;
            std::cin >> monto;
            lista[i].setMovimiento(m, monto);
        }
    }

    // Llamada a tu función
    int no_cuadrados = cuadratura(lista, total);

    std::cout << "Tarjetas adulteradas: " << no_cuadrados << "\n";

    delete[] lista;
    return 0;
}