#ifndef JUGADORCHICO_H
#define JUGADORCHICO_H

#include "Jugador.h"
#include "Actuacion.h"
#include "Marcador.h"
#include <algorithm>
#include <map>
#include <random>
#include <string>
#include <vector>

/**
 * Jugador básico que solo analiza las "chicas" (balas, tontos, trenes,
 * cuadras, quinas, senas) usando valor esperado. Para el resto de jugadas
 * (escalera, full, poker, grande) actúa aleatoriamente.
 * Autor: nicolas soto
 */
class JugadorChico : public Jugador {
private:
    std::string nombreEstudiante;

    // Clase interna para encapsular la recomendación de una chica
    class RecomendacionChica {
    public:
        std::string juego;
        int puntosMax;          // 5 * valor
        double prob;            // probabilidad de completar
        std::vector<int> guardar;   // índices de dados a conservar
        std::vector<int> voltear;   // índices de dados a voltear (complementos)

        RecomendacionChica() : puntosMax(0), prob(0.0) {}

        RecomendacionChica(std::string j, int pts, double p,
                           std::vector<int> g, std::vector<int> v)
            : juego(j), puntosMax(pts), prob(p),
              guardar(g), voltear(v) {}

        double ev() const { return puntosMax * prob; }
    };

public:
    JugadorChico(std::string nom = "ChicoAnalyst")
        : Jugador(nom), nombreEstudiante("nicolas soto") {}

    std::string getNombreEstudiante() const { return nombreEstudiante; }

    // ---------------------------------------------------------------------
    // Método principal: decide la acción según el estado del turno.
    // ---------------------------------------------------------------------
    int jugar(const std::map<std::string, Marcador>& marcadores,
              const std::vector<Actuacion>& actuacionesPosibles,
              const std::vector<int>& dados,
              const Anotacion& /*resultadoPrevio*/) override {

        // Si no hay opciones, elegir la primera (seguridad)
        if (actuacionesPosibles.empty())
            return 0;

        // Fase de anotación: la primera acción no es "lanzar"
        if (actuacionesPosibles[0].accion != "lanzar") {
            return elegirMejorAnotacion(actuacionesPosibles);
        }

        // Fase de lanzamiento: analizar chicas disponibles
        const Marcador& marc = marcadores.at(nombre);
        std::vector<RecomendacionChica> candidatos;

        // Solo considerar chicas no anotadas
        if (!marc.yaAnotado("balas"))
            candidatos.push_back(analizarChica(dados, 1));
        if (!marc.yaAnotado("tontos"))
            candidatos.push_back(analizarChica(dados, 2));
        if (!marc.yaAnotado("trenes"))
            candidatos.push_back(analizarChica(dados, 3));
        if (!marc.yaAnotado("cuadras"))
            candidatos.push_back(analizarChica(dados, 4));
        if (!marc.yaAnotado("quinas"))
            candidatos.push_back(analizarChica(dados, 5));
        if (!marc.yaAnotado("senas"))
            candidatos.push_back(analizarChica(dados, 6));

        // Si no hay chicas disponibles, actuar aleatoriamente
        if (candidatos.empty()) {
            return elegirAleatorio(actuacionesPosibles);
        }

        // Elegir la chica con mayor valor esperado
        auto mejor = std::max_element(
            candidatos.begin(), candidatos.end(),
            [](const RecomendacionChica& a, const RecomendacionChica& b) {
                return a.ev() < b.ev();
            });

        // Buscar la acción "lanzar" que coincida con los índices a relanzar
        return buscarActuacionLanzar(actuacionesPosibles, mejor->guardar);
    }

private:
    // ---------------------------------------------------------------------
    // Analiza una chica (valor v) y devuelve la recomendación.
    // Copia la lógica de JugadorFlores::analizarChica.
    // ---------------------------------------------------------------------
    RecomendacionChica analizarChica(const std::vector<int>& dados, int v) const {
        static const std::map<int, std::string> nombreChica = {
            {1, "balas"}, {2, "tontos"}, {3, "trenes"},
            {4, "cuadras"}, {5, "quinas"}, {6, "senas"}
        };

        std::vector<int> exactos;      // dados que valen exactamente v
        std::vector<int> complementos; // dados que valen 7-v (vuelques)

        for (int i = 0; i < 5; ++i) {
            if (dados[i] == v)
                exactos.push_back(i);
            else if (dados[i] == 7 - v)
                complementos.push_back(i);
        }

        // Solo se pueden usar hasta 2 complementos
        int vuelquesUtiles = std::min((int)complementos.size(), 2);
        int dadosUtiles = (int)exactos.size() + vuelquesUtiles;
        int dadosARelanzar = 5 - dadosUtiles;

        // Guardar exactos y los complementos útiles (estos últimos se voltearán)
        std::vector<int> guardar = exactos;
        std::vector<int> voltear;
        for (int i = 0; i < vuelquesUtiles; ++i) {
            guardar.push_back(complementos[i]);
            voltear.push_back(complementos[i]);
        }

        // Probabilidad de que los dados relanzados salgan exactamente v
        double prob = 1.0;
        for (int i = 0; i < dadosARelanzar; ++i)
            prob *= 1.0 / 6.0;

        return RecomendacionChica(
            nombreChica.at(v),
            v * 5,          // puntaje máximo
            prob,
            guardar,
            voltear
        );
    }

    // ---------------------------------------------------------------------
    // Construye el vector de índices a relanzar (complemento de guardar).
    // ---------------------------------------------------------------------
    std::vector<int> indicesRelanzar(const std::vector<int>& guardar) const {
        std::vector<bool> guardado(5, false);
        for (int i : guardar) guardado[i] = true;
        std::vector<int> relanzar;
        for (int i = 0; i < 5; ++i)
            if (!guardado[i]) relanzar.push_back(i);
        return relanzar;
    }

    // ---------------------------------------------------------------------
    // Busca en actuacionesPosibles una acción "lanzar" que coincida con
    // los índices a relanzar. Si no hay coincidencia exacta, elige la más
    // parecida (mayor número de índices comunes).
    // ---------------------------------------------------------------------
    int buscarActuacionLanzar(const std::vector<Actuacion>& actuaciones,
                              const std::vector<int>& guardar) const {
        std::vector<int> objetivo = indicesRelanzar(guardar);
        std::sort(objetivo.begin(), objetivo.end());

        int mejorIdx = 0;
        int maxCoincidencias = -1;

        for (int i = 0; i < (int)actuaciones.size(); ++i) {
            if (actuaciones[i].accion != "lanzar") continue;

            std::vector<int> actIdx = actuaciones[i].indiceDados;
            std::sort(actIdx.begin(), actIdx.end());

            // Coincidencia exacta
            if (actIdx == objetivo)
                return i;

            // Calcular cuántos índices coinciden
            int comunes = 0;
            for (int idx : actIdx) {
                if (std::find(objetivo.begin(), objetivo.end(), idx) != objetivo.end())
                    ++comunes;
            }
            if (comunes > maxCoincidencias) {
                maxCoincidencias = comunes;
                mejorIdx = i;
            }
        }
        return mejorIdx;
    }

    // ---------------------------------------------------------------------
    // Elección aleatoria entre todas las acciones disponibles.
    // ---------------------------------------------------------------------
    int elegirAleatorio(const std::vector<Actuacion>& actuaciones) const {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, actuaciones.size() - 1);
        return dist(gen);
    }

    // ---------------------------------------------------------------------
    // Fase de anotación: elige la acción con mayor puntaje.
    // Si hay "dormida", la prioriza (puntuación muy alta).
    // ---------------------------------------------------------------------
    int elegirMejorAnotacion(const std::vector<Actuacion>& actuaciones) const {
        int mejorIdx = 0;
        int mejorPts = -9999;

        for (int i = 0; i < (int)actuaciones.size(); ++i) {
            const Actuacion& act = actuaciones[i];
            int pts = act.anotacion.puntos;

            // Dormida es la mejor opción
            if (act.accion == "dormida")
                pts = 9999;

            // Si es "nada" o similar, no interesa
            if (act.accion == "nada")
                pts = -9999;

            if (pts > mejorPts) {
                mejorPts = pts;
                mejorIdx = i;
            }
        }
        return mejorIdx;
    }
};

#endif // JUGADORCHICO_H