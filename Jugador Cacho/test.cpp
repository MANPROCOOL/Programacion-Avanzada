#include "EvPlayerByPepe.h"
#include "JugadorAleatorio.h"
#include "Anotador.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>   

// Estructura para acumular resultados en cada hilo
struct ThreadResult {
    std::map<std::string, double> sumaPts;
    std::map<std::string, int>    vecesMax;
    std::map<std::string, int>    vecesCero;
    std::map<std::string, int>    vecesMedia;
    int victorias = 0;
    double sumaTotalPuntos = 0.0;
};

int main() {
    const int N = 1000000; // ajusta este numero segun cuantas partidas quieras

    // Juegos en orden de planilla
    const std::vector<std::string> juegos = {
        "balas","tontos","trenes","cuadras","quinas","senas",
        "escalera","full","poker","grande","grande2"
    };

    // Puntaje maximo posible por juego
    const std::map<std::string,int> maxPts = {
        {"balas",4},{"tontos",8},{"trenes",12},{"cuadras",16},
        {"quinas",20},{"senas",24},{"escalera",25},{"full",35},
        {"poker",45},{"grande",50},{"grande2",50}
    };

    // Iniciar cronómetro
    auto start = std::chrono::high_resolution_clock::now();

    // Determinar numero de hilos disponibles
    int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;

    std::vector<ThreadResult> resultados(numThreads);
    std::vector<std::thread> workers;
    std::atomic<int> siguientePartida{0};

    // Funcion que ejecuta cada hilo
    auto worker = [&](int id) {
        ThreadResult& res = resultados[id];
        // Inicializar mapas
        for (const auto& j : juegos) {
            res.sumaPts[j] = 0.0;
            res.vecesMax[j] = 0;
            res.vecesCero[j] = 0;
            res.vecesMedia[j] = 0;
        }

        while (true) {
            int idx = siguientePartida.fetch_add(1);
            if (idx >= N) break;

            // Crear jugadores y jugar una partida
            auto flores = std::make_shared<JugadorFlores>();
            auto rival  = std::make_shared<JugadorAleatorio>("Rival");
            Anotador a({flores, rival});
            auto ganadores = a.hacerJugar();

            const Marcador& m = a.marcadores["JugadorFlores"];
            res.sumaTotalPuntos += m.suma;

            if (std::find(ganadores.begin(), ganadores.end(), "JugadorFlores") != ganadores.end())
                res.victorias++;

            for (const auto& j : juegos) {
                int pts = m.puntajes.at(j);
                if (pts < 0) continue; // por seguridad
                res.sumaPts[j] += pts;
                int pmax = maxPts.at(j);
                if (pts == pmax)      res.vecesMax[j]++;
                else if (pts == 0)    res.vecesCero[j]++;
                else                  res.vecesMedia[j]++;
            }
        }
    };

    // Lanzar hilos
    for (int t = 0; t < numThreads; ++t)
        workers.emplace_back(worker, t);
    for (auto& th : workers) th.join();

    // Detener cronómetro
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    double totalSegundos = duration.count() / 1000.0;
    double promedioMs = (totalSegundos / N) * 1000.0;

    // Combinar resultados de todos los hilos
    std::map<std::string, double> sumaPts;
    std::map<std::string, int>    vecesMax, vecesCero, vecesMedia;
    int totalVictorias = 0;
    double sumaTotalPuntos = 0.0;

    for (const auto& j : juegos) {
        sumaPts[j] = 0.0;
        vecesMax[j] = 0;
        vecesCero[j] = 0;
        vecesMedia[j] = 0;
    }

    for (const auto& res : resultados) {
        totalVictorias += res.victorias;
        sumaTotalPuntos += res.sumaTotalPuntos;
        for (const auto& j : juegos) {
            sumaPts[j] += res.sumaPts.at(j);
            vecesMax[j] += res.vecesMax.at(j);
            vecesCero[j] += res.vecesCero.at(j);
            vecesMedia[j] += res.vecesMedia.at(j);
        }
    }

    // ---- Imprimir resultados (sin tildes) ----
    std::cout << "============================================================" << std::endl;
    std::cout << "  ANALISIS DE JugadorFlores -- " << N << " partidas vs Aleatorio" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "  Victorias : " << totalVictorias << " (" << 100.0*totalVictorias/N << "%)" << std::endl;
    std::cout << "  Puntaje medio: " << sumaTotalPuntos/N << std::endl;
    std::cout << std::endl;

    // Mostrar tiempos
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "  Tiempo total de ejecucion: " << std::fixed << std::setprecision(3) << totalSegundos << " segundos" << std::endl;
    std::cout << "  Tiempo promedio por partida: " << std::fixed << std::setprecision(3) << promedioMs << " ms" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    // Cabecera tabla
    std::cout << std::left
              << std::setw(12) << "Juego"
              << std::right
              << std::setw(8)  << "Media"
              << std::setw(8)  << "Max"
              << std::setw(8)  << "Efic%"
              << std::setw(9)  << "DeMano%"
              << std::setw(9)  << "Parcial%"
              << std::setw(8)  << "Cero%"
              << std::endl;
    std::cout << std::string(62, '-') << std::endl;

    // Chicas - usamos vector para evitar problemas de deduccion
    const std::vector<std::string> chicas = {"balas","tontos","trenes","cuadras","quinas","senas"};
    for (const auto& j : chicas) {
        double media   = sumaPts.at(j) / N;
        int    pmax    = maxPts.at(j);
        double efic    = 100.0 * media / pmax;
        double pctMax  = 100.0 * vecesMax.at(j)  / N;
        double pctMed  = 100.0 * vecesMedia.at(j) / N;
        double pctCero = 100.0 * vecesCero.at(j) / N;

        std::cout << std::left  << std::setw(12) << j
                  << std::right
                  << std::setw(8)  << media
                  << std::setw(8)  << pmax
                  << std::setw(8)  << efic
                  << std::setw(9)  << pctMax
                  << std::setw(9)  << pctMed
                  << std::setw(8)  << pctCero
                  << std::endl;
    }

    std::cout << std::string(62, '-') << std::endl;

    // Mayores
    const std::vector<std::string> mayores = {"escalera","full","poker","grande","grande2"};
    for (const auto& j : mayores) {
        double media   = sumaPts.at(j) / N;
        int    pmax    = maxPts.at(j);
        double efic    = 100.0 * media / pmax;
        double pctMax  = 100.0 * vecesMax.at(j)  / N;
        double pctMed  = 100.0 * vecesMedia.at(j) / N;
        double pctCero = 100.0 * vecesCero.at(j) / N;

        std::cout << std::left  << std::setw(12) << j
                  << std::right
                  << std::setw(8)  << media
                  << std::setw(8)  << pmax
                  << std::setw(8)  << efic
                  << std::setw(9)  << pctMax
                  << std::setw(9)  << pctMed
                  << std::setw(8)  << pctCero
                  << std::endl;
    }

    std::cout << std::string(62, '-') << std::endl;

    // Totales
    double totalChicas  = 0, totalMayores = 0;
    for (const auto& j : chicas)
        totalChicas += sumaPts.at(j);
    for (const auto& j : mayores)
        totalMayores += sumaPts.at(j);

    std::cout << std::left  << std::setw(12) << "CHICAS"
              << std::right << std::setw(8)  << totalChicas/N << std::endl;
    std::cout << std::left  << std::setw(12) << "MAYORES"
              << std::right << std::setw(8)  << totalMayores/N << std::endl;
    std::cout << std::left  << std::setw(12) << "TOTAL"
              << std::right << std::setw(8)  << (totalChicas+totalMayores)/N << std::endl;

    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "COMO LEER LA TABLA:" << std::endl;
    std::cout << "  Media    = puntos medios anotados en ese juego" << std::endl;
    std::cout << "  Max      = puntaje maximo posible (de mano)" << std::endl;
    std::cout << "  Efic%    = Media/Max * 100  (que % del maximo logramos)" << std::endl;
    std::cout << "  DeMano%  = % de partidas donde anotamos el maximo exacto" << std::endl;
    std::cout << "  Parcial% = % de partidas donde anotamos algo entre 0 y max" << std::endl;
    std::cout << "  Cero%    = % de partidas donde anotamos 0 (tachar o vacio)" << std::endl;

    return 0;
}