#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función recursiva que busca si se puede armar la cadena desde un índice específico
bool solve(int index, const string& loginAttempt, const vector<string>& passwords, 
           vector<string>& result, bool bad_indices[]) {
    
    // CASO BASE: Si el índice llegó al final de la cadena, significa que logramos 
    // segmentar todo el loginAttempt con éxito utilizando las contraseñas.
    if (index == loginAttempt.length()) {
        return true;
    }
    
    // OPTIMIZACIÓN (Memoización): Si este índice ya está marcado como verdadero (true),
    // significa que en una ruta previa ya intentamos buscar desde aquí y falló.
    // Retornamos falso de inmediato para evitar cálculos repetidos (evita TLE).
    if (bad_indices[index]) {
        return false;
    }
    
    // Bucle clásico para probar cada una de las contraseñas disponibles en el vector
    for (int i = 0; i < passwords.size(); ++i) {
        string pwd = passwords[i]; // Obtenemos la contraseña actual
        int len = pwd.length();     // Guardamos su longitud
        
        // Verificamos dos condiciones antes de avanzar:
        // 1. Que la longitud de la contraseña no se pase del límite de lo que queda de cadena.
        // 2. Que la contraseña coincida exactamente con el fragmento de la cadena a partir de 'index'.
        if (index + len <= loginAttempt.length() && loginAttempt.compare(index, len, pwd) == 0) {
            
            // Si coincide, guardamos temporalmente esta contraseña en el vector de resultados
            result.push_back(pwd);
            
            // Llamamos recursivamente a la función, pero avanzando el índice la longitud de la contraseña
            if (solve(index + len, loginAttempt, passwords, result, bad_indices)) {
                return true; // Si la llamada recursiva tuvo éxito, propagamos el true hacia arriba
            }
            
            // BACKTRACKING: Si la llamada recursiva falló, significa que esta contraseña no 
            // servía para este camino. La eliminamos del resultado para probar con la siguiente.
            result.pop_back();
        }
    }
    
    // Si el bucle termina y ninguna contraseña funcionó a partir de esta posición,
    // marcamos este índice como "malo" en nuestro arreglo para no volver a evaluar esta posición.
    bad_indices[index] = true;
    return false;
}

// Función principal exigida por el problema
string passwordCracker(vector<string> passwords, string loginAttempt) {
    vector<string> result;          // Vector para almacenar el camino de contraseñas correctas
    bool bad_indices[2005] = {false}; // Arreglo booleano para recordar los índices que fracasaron
    
    // Iniciamos la recursión desde el índice 0 (el inicio de la cadena)
    if (solve(0, loginAttempt, passwords, result, bad_indices)) {
        string output = "";
        // Bucle clásico para unir las contraseñas guardadas en un solo string separado por espacios
        for (int i = 0; i < result.size(); ++i) {
            output += result[i];
            if (i < result.size() - 1) output += " "; // Añade espacio solo si no es la última palabra
        }
        return output;
    }
    
    // Si la función solve retornó falso, significa que es imposible construir la cadena
    return "WRONG PASSWORD";
}

int main() {
    int t;
    if (!(cin >> t)) return 0; // Leer la cantidad de casos de prueba
    
    while (t--) {
        int n;
        cin >> n; // Leer la cantidad de contraseñas de este caso
        
        vector<string> passwords(n);
        for (int i = 0; i < n; ++i) {
            cin >> passwords[i]; // Leer cada una de las contraseñas
        }
        
        string loginAttempt;
        cin >> loginAttempt; // Leer la cadena que se intenta descifrar
        
        // Imprimir el resultado retornado por la función
        cout << passwordCracker(passwords, loginAttempt) << "\n";
    }
    return 0;
}