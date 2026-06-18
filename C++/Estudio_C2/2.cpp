#include <iostream>

using namespace std;

// Usamos arreglos globales tradicionales (el problema dice que N es máximo 20)
// Ponemos tamaño 25 para estar sobrados y no complicarnos con vectores
bool chocan[25][25];
bool incluido[25];

/**
 * Función recursiva que toma decisiones ingrediente por ingrediente
 */
int contar_pizzas(int ingrediente_actual, int total_ingredientes) {
    
    // CASO BASE: Si ya decidimos sobre todos los ingredientes, 
    // significa que logramos armar 1 pizza válida.
    
    if (ingrediente_actual > total_ingredientes) {
        return 1;
    }

    int total_combinaciones = 0;

    // --- DECISIÓN 1: NO INCLUIR el ingrediente actual ---
    // Simplemente pasamos al siguiente ingrediente. Esto siempre es válido.
    total_combinaciones += contar_pizzas(ingrediente_actual + 1, total_ingredientes);


    // --- DECISIÓN 2: SÍ INCLUIR el ingrediente actual ---
    // Pero primero, revisamos si este ingrediente choca con alguno de los que YA están en la pizza.
    bool se_puede_agregar = true;
    for (int i = 1; i <= total_ingredientes; i++) {
        // Si el ingrediente 'i' ya está en la pizza Y choca con el 'ingrediente_actual'
        if (incluido[i] == true && chocan[ingrediente_actual][i] == true) {
            se_puede_agregar = false; // ¡No se puede usar!
        }
    }

    // Si no hubo problemas, simulamos ponerlo en la pizza
    if (se_puede_agregar) {
        incluido[ingrediente_actual] = true; // Lo ponemos
        
        // Evaluamos los siguientes ingredientes con este ya puesto
        total_combinaciones += contar_pizzas(ingrediente_actual + 1, total_ingredientes);
        
        incluido[ingrediente_actual] = false; // Backtracking: lo quitamos para dejar la barra limpia
    }

    return total_combinaciones;
}

int main() {
    int ingredientes, prohibidos;
    cin >> ingredientes >> prohibidos;

    // Inicializamos nuestros arreglos en falso (todo limpio al principio)
    for (int i = 0; i < 25; i++) {
        incluido[i] = false;
        for (int j = 0; j < 25; j++) {
            chocan[i][j] = false;
        }
    }

    // Leemos las combinaciones prohibidas
    for (int i = 0; i < prohibidos; i++) {
        int u, v;
        cin >> u >> v;
        chocan[u][v] = true;
        chocan[v][u] = true;
    }

    // Empezamos a decidir desde el ingrediente 1
    int resultado = contar_pizzas(1, ingredientes);

    cout << resultado << endl;

    return 0;
}