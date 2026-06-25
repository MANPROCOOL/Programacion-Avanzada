#ifndef EVPLAYERBYPEPE_H
#define EVPLAYERBYPEPE_H

#include "Jugador.h"
#include "Actuacion.h"
#include "Anotador.h"
#include "Marcador.h"
#include <map>
#include <string>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

class JugadorFlores : public Jugador { // Basado en la logica de valor esperado: puntaje * probabilidad
private:
    string nombreEstudiante;

    class Recomendacion {
    public:
        string juego;         // nombre de la categoría (ej. "full")
        double ev;            // valor esperado calculado
        vector<int> guardar;  // índices de los dados que conviene conservar
    };

    static const map<string, int> maxPts;   // puntajes máximos de cada categoría, definido abajo

    // UTILIDADES

    int max2(int a, int b) const { return a > b ? a : b; }
    int min2(int a, int b) const { return a < b ? a : b; }

    // Devuelve true si x está en el vector v
    bool contiene(const vector<int>& v, int x) const {
        for (int e : v) if (e == x) return true;
        return false;
    }

    // Combinatorio C(n,k) iterativo
    int comb(int n, int k) const {
        if (k < 0 || k > n) return 0;
        if (k > n - k) k = n - k; 
        int res = 1;
        for (int i = 1; i <= k; ++i) res = res * (n - i + 1) / i;
        return res;
    }

    // Probabilidad binomial de al menos 'necesarios' éxitos en 'r' intentos
    double probBinomial(int r, int necesarios, double p) const { // p = prob en cada intento
        double prob = 0.0;
        for (int k = necesarios; k <= r; ++k)
            prob += comb(r, k) * pow(p, k) * pow(1.0 - p, r - k);
        return prob;
    }

    // Valor esperado de una binomial truncada a 'limite' éxitos (para chicas)
    double expectedBinomial(int r, double p, int limite) const {
        double esperanza = 0.0;
        for (int k = 0; k <= r; ++k) {
            double prob = comb(r, k) * pow(p, k) * pow(1.0 - p, r - k);
            esperanza += min2(k, limite) * prob; // limitamos el conteo a 'limite'
        }
        return esperanza;
    }

public:
    JugadorFlores(string nom = "JugadorFlores") : Jugador(nom) {
        nombreEstudiante = "José Flores";
    }

    string getNombreEstudiante() const { return nombreEstudiante; }

    // ====================================================================================================================================================
    // MÉTODO PRINCIPAL

    int jugar(const map<string, Marcador>& marcadores,
              const vector<Actuacion>& actuacionesPosibles,
              const vector<int>& dados,
              const Anotacion& /*resultadoPrevio*/) override {

        if (actuacionesPosibles.empty()) return 0;   // sin acciones, retorno 0

        // Hay una anotación PERFECTA disponible? tomemosla
        for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) {
            const Actuacion& a = actuacionesPosibles[i];
            if (a.accion == "anotar" && a.anotacion.puntos > 0) { //acciones de tipo "anotar" con puntos positivos
                string juego = a.anotacion.juego;
                size_t pos = juego.find(" (de la 1ra mano)");           //busca el indice del sobre, si no devuelve invalid index
                if (pos != string::npos) juego = juego.substr(0, pos); // quitar sufijo de sobre
                if (maxPts.count(juego) && a.anotacion.puntos == maxPts.at(juego)) { // verificamos si el puntaje del candidato es el maximo posible
                    return i;   // anotación perfecta inmediata, sin arriesgar
                }
            }
        }

        // Fase de lanzamiento
        if (actuacionesPosibles[0].accion == "lanzar") {
            const Marcador& marc = marcadores.at(nombre);
            vector<Recomendacion> recs;      // recomendaciones para cada categoría libre

            for (int v = 1; v <= 6; ++v) { // Generar recomendaciones de chicas (1..6)
                string juego = nombreChica(v);
                if (!marc.yaAnotado(juego)) recs.push_back(analizarChica(dados, v));
            }

            if (!marc.yaAnotado("escalera")) recs.push_back(analizarEscalera(dados)); // Generar recomendaciones de jugadas mayores
            if (!marc.yaAnotado("full"))     recs.push_back(analizarFull(dados));
            if (!marc.yaAnotado("poker"))    recs.push_back(analizarPoker(dados));
            if (!marc.yaAnotado("grande"))   recs.push_back(analizarGrande(dados, "grande"));
            if (!marc.yaAnotado("grande2"))  recs.push_back(analizarGrande(dados, "grande2"));

            if (recs.empty()) return elegirAleatorio(actuacionesPosibles); // sin categorías libres retorna aleatorio de las diosponibles (poriacaso)

            // Elegir la recomendación con mayor EV
            double bestEV = recs[0].ev;
            int bestIdx = 0;
            for (int i = 1; i < (int)recs.size(); ++i) {
                if (recs[i].ev > bestEV) { bestEV = recs[i].ev; bestIdx = i; }
            }

            const Recomendacion& mejor = recs[bestIdx];
            return buscarActuacionLanzar(actuacionesPosibles, mejor.guardar); // busca la accion y devuelve el indice
        }

        // Fase de anotación
        for (int i = 0; i < (int)actuacionesPosibles.size(); ++i) { //¿hay un sobre pendiente eficiente del primer intento?
            const Actuacion& a = actuacionesPosibles[i];
            if (a.accion == "anotar" && a.anotacion.juego.find("(de la 1ra mano)") != string::npos) { // es un sobre si tiene 1era mano en algun indice
                string juegoBase = a.anotacion.juego.substr(0, a.anotacion.juego.find(" (de la 1ra mano)"));
                int pmax = maxPts.count(juegoBase) ? maxPts.at(juegoBase) : a.anotacion.puntos;
                if (pmax > 0 && a.anotacion.puntos >= pmax * 0.8) {
                    return i;   // sobre eficiente, lo tomamos sin dudar
                }
            }
        }
        return elegirMejorAnotacion(actuacionesPosibles, marcadores.at(nombre)); // Si no hay sobre pendiente, elegir la mejor anotación disponible
    }

private:

    // ANÁLISIS DE JUGADAS (cálculo de valor esperado y dados a conservar)

    string nombreChica(int v) const {
        static const map<int, string> nombres = {
            {1, "balas"}, {2, "tontos"}, {3, "trenes"},
            {4, "cuadras"}, {5, "quinas"}, {6, "senas"}
        };
        return nombres.at(v);
    }

    // Chicas
    Recomendacion analizarChica(const vector<int>& dados, int v) const {
        vector<int> guardar;
        int vuelquesUtiles = 0;
        // Guardar todos los dados exactos (valor == v)
        for (int i = 0; i < 5; ++i) {
            if (dados[i] == v) guardar.push_back(i);
        }
        // Guardar hasta 2 complementos (7 - v) que cuentan como v
        for (int i = 0; i < 5 && vuelquesUtiles < 2; ++i) {
            if (dados[i] == 7 - v) {
                guardar.push_back(i);
                vuelquesUtiles++;
            }
        }

        int dadosUtiles = (int)guardar.size();          // dados que ya suman
        int r = 5 - dadosUtiles;                        // dados a relanzar
        double exp_exact_nuevos = r * (1.0 / 6.0);      // esperanza de nuevos exactos
        int limite_compl = max2(0, 2 - vuelquesUtiles); // complementos adicionales que caben
        double exp_compl_nuevos = expectedBinomial(r, 1.0/6.0, limite_compl); // valor esperado de nuevos complementos (truncado a limite_compl)
        double puntosEsperados = v * (dadosUtiles + exp_exact_nuevos + exp_compl_nuevos); // puntos totales esperados = valor * (dados que ya suman + los que esperamos sumar)
        return Recomendacion{nombreChica(v), puntosEsperados, guardar}; // devolvemos la recomendación
    }

    // Escalera (corregida)
    Recomendacion analizarEscalera(const vector<int>& dados) const {
        const int objetivos[3][5] = {{1,2,3,4,5}, {2,3,4,5,6}, {1,3,4,5,6}};

        double mejorEV = -1.0;
        vector<int> mejorGuardar;

        for (int esc = 0; esc < 3; ++esc) {
            const int* obj = objetivos[esc];
            bool cubierto[5] = {false};
            vector<int> guardarTmp;
            int complementosGuardados = 0;
        
            // Pasada 1: asignar dados exactos a sus slots
            for (int idx = 0; idx < 5; ++idx) {
                for (int j = 0; j < 5; ++j) {
                    if (!cubierto[j] && dados[idx] == obj[j]) {
                        cubierto[j] = true;
                        guardarTmp.push_back(idx);
                        break;
                    }
                }
            }
            // Pasada 2: asignar vuelques a los slots que quedaron libres
            for (int idx = 0; idx < 5; ++idx) {
                if (contiene(guardarTmp, idx)) continue;
                for (int j = 0; j < 5; ++j) {
                    if (!cubierto[j] && 7 - dados[idx] == obj[j]) {
                        cubierto[j] = true;
                        guardarTmp.push_back(idx);
                        complementosGuardados++;   // sumamos el complemento
                        break;
                    }
                }
            }
            int faltan = 0;
            for (int j = 0; j < 5; ++j) if (!cubierto[j]) faltan++;
            int r = 5 - (int)guardarTmp.size();
            double perms = 1.0;
            for (int k = 0; k < faltan; ++k) perms *= (r - k); // Número de permutaciones de 'faltan' slots en 'r' dados: r×(r-1)×...×(r-faltan+1)
            double probMano       = (faltan == 0) ? 1.0 : perms / pow(6.0, r);
            double probCualquiera = (faltan == 0) ? 1.0 : perms / pow(3.0, r);  
            bool tieneVuelque = (complementosGuardados > 0); // Si hay vuelque guardado, el techo baja a 20 pts (no podemos lograrla de mano)

            double ev = tieneVuelque ? 20.0 * probCualquiera : 25.0 * probMano + 20.0 * (probCualquiera - probMano);
            double permsTodos = 120.0; // Comparar contra relanzar los 5 dados desde cero (5! = 120)
            double evTodos = 25.0 * (permsTodos / pow(6.0, 5)) + 20.0 * (permsTodos / pow(3.0, 5) - permsTodos / pow(6.0, 5));

            if (evTodos > ev) { // si es mejor relanzar todo...
                ev = evTodos;
                guardarTmp.clear();
            }
            if (ev > mejorEV) { // encontrar la mejor jugada que guarda algo
                mejorEV = ev;
                mejorGuardar = guardarTmp;
            }
        }
        return Recomendacion{"escalera", mejorEV, mejorGuardar};
    }

    // Full House
    double probabilidadFull(int r, int faltaTrio, int faltaPar, double p) const { // P(completar trío + par con 'r' dados restantes, necesitando 'faltaTrio' y 'faltaPar')
        double prob = 0.0;
        for (int k = faltaTrio; k <= r - faltaPar; ++k) { // k éxitos para el trío
            int j = r - k;                                 // dados restantes para el par
            if (j >= faltaPar) {
                prob += comb(r, k) * comb(r - k, j) * pow(p, k) * pow(p, j) * pow(1.0 - 2.0*p, r - k - j); // Suma sobre todas las formas de distribuir los k éxitos del trío entre los r dados.
            }
        }
        return prob;
    }

    // Full
    Recomendacion analizarFull(const vector<int>& dados) const {
        double mejorEV = -1.0;
        vector<int> mejorGuardar;
        int mejorTrioValor = 0, mejorParValor = 0;

        // Buscar el mejor valor para trío y par (contando naturales + complementos)
        int maxTrio = 0, maxPar = 0;
        for (int x = 1; x <= 6; ++x) {
            int cuenta = 0;
            for (int v : dados) if (v == x || 7 - v == x) cuenta++;
            if (cuenta >= 3 && cuenta > maxTrio) { maxTrio = cuenta; mejorTrioValor = x; }
            if (cuenta >= 2 && cuenta > maxPar && x != mejorTrioValor) {
                maxPar = cuenta; mejorParValor = x;
            }
        }
        vector<int> idxTrioNat, idxTrioCompl; // Separar índices: naturales (valor exacto) y complementos (vuelques) para trío y par
        vector<int> idxParNat, idxParCompl;
        for (int i = 0; i < 5; ++i) {
            int v = dados[i];
            if (v == mejorTrioValor) idxTrioNat.push_back(i);
            else if (7 - v == mejorTrioValor) idxTrioCompl.push_back(i);
            if (v == mejorParValor) idxParNat.push_back(i);
            else if (7 - v == mejorParValor) idxParCompl.push_back(i);
        }
        // Conservar hasta 3 del trío y 2 del par, priorizando naturales sobre complementos
        vector<int> guardarFinal;
        int guardadosTrio = 0, guardadosPar = 0;
        for (int idx : idxTrioNat) {
            if (guardadosTrio >= 3) break;
            guardarFinal.push_back(idx); guardadosTrio++;
        }
        for (int idx : idxTrioCompl) {
            if (guardadosTrio >= 3) break;
            guardarFinal.push_back(idx); guardadosTrio++;
        }
        for (int idx : idxParNat) {
            if (guardadosPar >= 2) break;
            guardarFinal.push_back(idx); guardadosPar++;
        }
        for (int idx : idxParCompl) {
            if (guardadosPar >= 2) break;
            guardarFinal.push_back(idx); guardadosPar++;
        }
        int r = 5 - (int)guardarFinal.size();    // dados a relanzar

        // Contar cuántos del trío y del par quedaron realmente guardados
        int cuentaTrioGuardado = 0;
        for (int idx : guardarFinal) {
            int v = dados[idx];
            if (v == mejorTrioValor || 7 - v == mejorTrioValor) cuentaTrioGuardado++; //cuantos elementos del par y del trio guardamos
        }
        int cuentaParGuardado = (int)guardarFinal.size() - cuentaTrioGuardado;
        int faltaTrio = max2(0, 3 - cuentaTrioGuardado); //uso max por redundancia
        int faltaPar  = max2(0, 2 - cuentaParGuardado);

        double probTotal = probabilidadFull(r, faltaTrio, faltaPar, 1.0/3.0);
        double probMano  = probabilidadFull(r, faltaTrio, faltaPar, 1.0/6.0);

        // Si hay algún complemento guardado, el techo es 30 pts (full de huevo), no 35
        bool tieneVuelque = false;
        for (int idx : guardarFinal) {
            int v = dados[idx];
            if ((v == mejorTrioValor || v == mejorParValor) == false)
                tieneVuelque = true;
        }

        double ev = tieneVuelque ? 30.0 * probTotal : 35.0 * probMano + 30.0 * (probTotal - probMano);

        if (ev > mejorEV) {
            mejorEV = ev;
            mejorGuardar = guardarFinal;
        }
        return Recomendacion{"full", ev, mejorGuardar};
    }

    // Poker
    Recomendacion analizarPoker(const vector<int>& dados) const {
        double mejorEV = -1.0;
        vector<int> mejorGuardar;
        for (int valorObjetivo = 1; valorObjetivo <= 6; ++valorObjetivo) {// probar cada valor de los dadoscomo candidato a póker
            vector<int> naturales, complementos;
            for (int i = 0; i < 5; ++i) {
                if (dados[i] == valorObjetivo) naturales.push_back(i);
                else if (7 - dados[i] == valorObjetivo) complementos.push_back(i);
            }
            if (naturales.empty() && complementos.empty()) continue;// sin dados útiles para este valor, probamos el siguiente

            // Conservar hasta 4 dados, priorizando naturales sobre complementos
            vector<int> guardarTmp;
            for (int idx : naturales) {
                if ((int)guardarTmp.size() >= 4) break;
                guardarTmp.push_back(idx);
            }
            for (int idx : complementos) {
                if ((int)guardarTmp.size() >= 4) break;
                guardarTmp.push_back(idx);
            }
            if (guardarTmp.empty()) continue;

            int cuenta = (int)guardarTmp.size(); // dados útiles guardados
            int r = 5 - cuenta;                  // dados a relanzar
            int necesarios = max2(0, 4 - cuenta);// cuántos éxitos faltan para el cuarteto            
            double probTotal = probBinomial(r, necesarios, 1.0/3.0); // P(completar) con exactos (1/6) o vuelques (1/3) por dado
            double probMano  = probBinomial(r, necesarios, 1.0/6.0);
            // Si hay un complemento guardado, el techo baja a 40 pts (póker de huevo)
            bool tieneVuelque = false;
            for (int idx : guardarTmp) {
                if (dados[idx] != valorObjetivo) { tieneVuelque = true; break; }
            }
            double ev = tieneVuelque ? 40.0 * probTotal : 45.0 * probMano + 40.0 * (probTotal - probMano);
            double evTodos = 0.0; // Comparar con relanzar los 5 dados desde cero (EV base de referencia)
            for (int v = 1; v <= 6; ++v) {
                double probTotalV = probBinomial(5, 4, 1.0/3.0); //relanza 5 y que salga de mano
                double probManoV  = probBinomial(5, 4, 1.0/6.0); // que salga con vuelques (huevo)
                double evV = 40.0 * probTotalV + 5.0 * probManoV;   // 45 si es mano, 40 si es huevo
                if (evV > evTodos) evTodos = evV;
            }

            if (evTodos > ev) { // relanzar todo es mejor
                ev = evTodos;
                guardarTmp.clear(); 
            }
            if (ev > mejorEV) { // Guarda el mejor poker encontrado hasta el momento
                mejorEV = ev;
                mejorGuardar = guardarTmp;
            }
        }
        return Recomendacion{"poker", mejorEV, mejorGuardar};
    }

    // Grande
    Recomendacion analizarGrande(const vector<int>& dados, const string& juego) const {
        double mejorEV = -1.0;
        vector<int> mejorGuardar;
        const int familias[3][2] = {{1,6},{2,5},{3,4}}; // familias (natural y complemento)

        for (int f = 0; f < 3; ++f) {
            int a = familias[f][0], b = familias[f][1];
            vector<int> natural, complementos; // no distingo entre nat y compl, si todos fueran nat seria dormida y ganaria insta.
            for (int i = 0; i < 5; ++i) {
                if (dados[i] == a || dados[i] == b) natural.push_back(i); // natural de la familia
                else if (7 - dados[i] == a || 7 - dados[i] == b) complementos.push_back(i); // complemento útil
            }
            if (natural.empty() && complementos.empty()) continue; // ningún dado sirve para esta familia

            // Conservar hasta 4 dados, priorizando naturales sobre complementos
            vector<int> guardarTmp; //hasta 4 nmas, porque si tuvieramos 5, la funcion mejor jugada la hayaria antes
            for (int idx : natural) {
                if ((int)guardarTmp.size() >= 4) break;
                guardarTmp.push_back(idx);
            }
            for (int idx : complementos) {
                if ((int)guardarTmp.size() >= 4) break;
                guardarTmp.push_back(idx);
            }
            if (guardarTmp.empty()) continue; // si esta familia no tiene elementos, pasemos a la otra

            int cuenta = (int)guardarTmp.size();  // dados útiles en mano
            int r = 5 - cuenta;                   // dados a relanzar
            int necesarios = max2(0, 4 - cuenta); // cuántos faltan para la grande
            double prob = probBinomial(r, necesarios, 1.0/3.0);
            double ev = 50.0 * prob;

            if (cuenta <= 2)      ev *= 0.15;  // muy improbable de completar
            else if (cuenta == 3) ev *= 0.65;  // posible pero arriesgado
            // cuenta >= 4: EV sin descuento, vale la pena perseguirla

            if (ev > mejorEV) {
                mejorEV = ev;
                mejorGuardar = guardarTmp;
            }
        }
        return Recomendacion{juego, mejorEV, mejorGuardar};
    }

    // FASE DE ANOTACIÓN (valoración de acciones no-lanzar)

    int elegirMejorAnotacion(const vector<Actuacion>& act, const Marcador& marc) const {
        int mejor = 0;
        double mejorScore = -1e9;
        int pendientes = marc.porAnotar; // casillas que aún faltan

        for (int i = 0; i < (int)act.size(); ++i) {
            double s = -1000.0;
            const Actuacion& a = act[i];

            if (a.accion == "dormida") { //dormida gana instantaneamente, prioridad absoluta
                s = 10000.0;                      
            } else if (a.accion == "anotar") { //si hayamos una accion anotar, la valoramos
                s = a.anotacion.puntos;
                if (a.anotacion.puntos > 0) { //solo valoramos la accion si no es "tachar", osea, si da puntos
                    string juego = a.anotacion.juego; 
                    size_t pos = juego.find(" (de la 1ra mano)");          // era de un sobre anterior?
                    if (pos != string::npos) juego = juego.substr(0, pos); // limpiar sufijo
                    if (a.anotacion.puntos == maxPts.at(juego))
                        s += a.anotacion.puntos * 0.4; // bonus por anotación perfecta, prefiere anotar directo a elejir sobre
                    if (pendientes <= 3) s += 5.0;     // urgencia al final, quedan pocas manos asique cualquier cosa sirve
                }
            } else if (a.accion == "sobre") {
                string juego = a.anotacion.juego;
                int pts = a.anotacion.puntos;
                int pmax = maxPts.count(juego) ? maxPts.at(juego) : pts;
                double eficiencia = (double)pts / pmax;

                if (pts == pmax) { // Jugada perfecta: el sobre no puede mejorarla
                    s = pts;
                } else if (eficiencia >= 0.5) { // Jugada decente: el sobre permite intentar la versión perfecta
                    s = pts + 3.0;              // bonus por la oportunidad de mejora
                } else { // Jugada mala: arriesgarse probablemente termine en 0
                    s = pts * 0.6;
                }
                if (pendientes <= 3) s += 5.0; // urgencia al final
            }

            if (s > mejorScore) { // guardar la mejor opción
                mejorScore = s;
                mejor = i;
            }
        }
        return mejor; // Retornamos el indice de la mejor accion
    }

    // BÚSQUEDA DE ACCIÓN "LANZAR"
    int buscarActuacionLanzar(const vector<Actuacion>& act, const vector<int>& guardar) const {
        // 1. Calcular índices a relanzar (los que NO están en guardar)
        vector<int> relanzar;
        for (int i = 0; i < 5; ++i) {
            bool conservado = false;
            for (int idx : guardar) if (idx == i) { conservado = true; break; }
            if (!conservado) relanzar.push_back(i);    // ya queda en orden ascendente
        }

        int mejorIdx = 0, maxComunes = -1;
        for (int i = 0; i < (int)act.size(); ++i) {
            if (act[i].accion != "lanzar") continue;   // solo nos interesa lanzar

            const vector<int>& idxs = act[i].indiceDados; // ya viene ordenado del motor
            if (idxs == relanzar) return i;               // coincidencia exacta

            // Si no es exacta, contar intersección para encontrar la más parecida
            int comunes = 0;
            for (int x : idxs) if (contiene(relanzar, x)) comunes++;
            if (comunes > maxComunes) {
                maxComunes = comunes;
                mejorIdx = i;
            }
        }
        return mejorIdx;   // mejor aproximación encontrada
    }

    int elegirAleatorio(const vector<Actuacion>& act) const { // Copie el aleatorio del jugador aleatorio, porciacaso...
        static mt19937 gen(random_device{}());
        return uniform_int_distribution<>(0, (int)act.size() - 1)(gen);
    }
};

const map<string, int> JugadorFlores::maxPts = { // Definición del mapa estático de puntajes máximos
    {"balas",4}, {"tontos",8}, {"trenes",12}, {"cuadras",16},
    {"quinas",20}, {"senas",24}, {"escalera",25}, {"full",35},
    {"poker",45}, {"grande",50}, {"grande2",50}
};

#endif