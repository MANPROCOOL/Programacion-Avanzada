#include "JugadorAleatorio.h"
#include "EvPlayerByPepe.h"
#include "JugadorChico.h"
#include "JugadorOptimo.h"
#include "Tournament.h"
#include <iostream>
#include <memory>
// g++ -std=c++20 -O3 -march=native -DNDEBUG -pthread main.cpp -o torneo

int main() {
  Tournament t;

  // Agregar JugadorOptimo
  t.addPlayer(
      []() { return std::make_shared<JugadorOptimo>("Optimo_DP"); });
  // Agregar JugadorEV
  t.addPlayer(
      []() { return std::make_shared<EvPlayerByPepe>("Pepe"); });
  // Agregar Jugadores Aleatorios
  t.addPlayer(
      []() { return std::make_shared<JugadorAleatorio>("Bot_Random_1"); });

  t.addPlayer(
      []() { return std::make_shared<JugadorAleatorio>("Bot_Random_2"); });

  t.addPlayer(
      []() { return std::make_shared<JugadorAleatorio>("Bot_Random_3"); });

  // Agregar el nuevo jugador básico
  t.addPlayer(
      []() { return std::make_shared<JugadorChico>("Nicolas soto"); }); // <-- NUEVO

  // Ejecución en paralelo
  t.runParallel(100000);
  t.displayResults();

  return 0;
}