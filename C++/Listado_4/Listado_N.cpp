//Operator Overloading

#include<iostream>

using namespace std;

class Complex
{
public:
    int a,b;
    void input(string s)
    {
        int v1=0;
        int i=0;
        while(s[i]!='+')
        {
            v1=v1*10+s[i]-'0';
            i++;
        }
        while(s[i]==' ' || s[i]=='+'||s[i]=='i')
        {
            i++;
        }
        int v2=0;
        while(i<(int)s.length())
        {
            v2=v2*10+s[i]-'0';
            i++;
        }
        a=v1;
        b=v2;
    }
};

//Overload operators + and << for the class complex
//+ should add two complex numbers as (a+ib) + (c+id) = (a+c) + i(b+d)

Complex operator+(const Complex& izquierda, const Complex& derecha) {
    Complex result;
    // Sumamos las partes reales de ambos parametros
    result.a = izquierda.a + derecha.a; 
    // Sumamos las partes imaginarias de ambos parametros
    result.b = izquierda.b + derecha.b; 
    // Retornamos el objeto con los nuevos valores
    return result; //retorna un objeto de la clase
}
//<< should print a complex number in the format "a+ib"

ostream& operator<<(ostream& out, Complex& imaginario) { //no podria ir dentro de la clase porque el operador se ejecutaria
    out << imaginario.a << "+i" << imaginario.b;                 //sobre lo que tiene a su izquierda
    return out;
}

int main()
{
    Complex x,y;
    string s1,s2;
    cin>>s1;
    cin>>s2;
    x.input(s1);
    y.input(s2);
    Complex z=x+y;
    cout<<z<<endl;
}