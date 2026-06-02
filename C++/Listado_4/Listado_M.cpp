#include<bits/stdc++.h>

using namespace std;
//Implement the class Box  
class Box{
    int l, b, h; // Atributos de la caja

public:
    Box() { // 1. Constructor por defecto
        l = 0;
        b = 0;
        h = 0;
    }
    Box(int length, int breadth, int height) { // 2. Constructor con parametros
        l = length;
        b = breadth;
        h = height;
    }

    Box(Box& old_box) { // 3. Constructor de copia 
        l = old_box.l; //Tambien podria usar los metodos get
        b = old_box.b;
        h = old_box.h;
    }
    
    int getLength(){ // Return box's length
        return l;
    }
    int getBreadth (){ // Return box's breadth
        return b;
    }
    int getHeight (){  //Return box's height
        return h;
    }
    long long CalculateVolume(){ // Return the volume of the box
        return (long long)l*b*h;
    }
    bool operator<(Box& comparando){
		if (l < comparando.getLength()) {return true;}
		else if (l == comparando.getLength() && b < comparando.getBreadth()) {return true;}
		else if (l == comparando.getLength() && b == comparando.getBreadth() && h < comparando.getHeight()) {return true;}
		else {return false;}
	}
};

// Sobrecarga del operador << de forma global
ostream& operator<<(ostream& out, Box& B) { //no podria ir dentro de la clase porque el operador se ejecutaria
    out << B.getLength() << " " << B.getBreadth() << " " << B.getHeight(); //lo que tiene a su izquierda
    return out;
}

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)


void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}