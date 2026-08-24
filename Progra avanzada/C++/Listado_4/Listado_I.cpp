#include <iostream>
#include <string>

using namespace std;

class Student {
private:

    int edad, standard;
    string nombre;
    string apellido;

    string entero_a_texto(int numero) {
        if (numero == 0) return "0";
        string texto = "";
        while (numero > 0) {
            int digito = numero % 10;
            char caracter = digito + '0';
            texto = caracter + texto;
            numero = numero / 10;
        }
        return texto;
    }

public:
    //SETTERS Y GETTERS
    void set_age(int a) { edad = a; }
    int get_age() { return edad; }

    void set_first_name(string fn) { nombre = fn; }
    string get_first_name() { return nombre; }

    void set_last_name(string ln) { apellido = ln; }
    string get_last_name() { return apellido; }

    void set_standard(int s) { standard = s; }
    int get_standard() { return standard; }

    string to_string() {
        string edad_texto = entero_a_texto(edad);
        string standard_texto = entero_a_texto(standard);
        string resultado = edad_texto + "," + nombre + "," + apellido + "," + standard_texto;
        
        return resultado;
    }
};

int main() {
    int age, standard;
    string first_name, last_name;
    
    cin >> age >> first_name >> last_name >> standard;
    
    Student st;
    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);
    
    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    cout << "\n";
    cout << st.to_string();
    
    return 0;
}