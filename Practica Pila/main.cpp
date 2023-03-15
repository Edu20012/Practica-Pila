#include <iostream>
#include <cstring>
#define TAM 255
#define VACIA -1
using namespace std;

// La clase pila ya tiene su funcionalidad completa
class Pila
{
 private:
 int tam;
 int tos;
 char datos [TAM];

 public:
 Pila ()
 {
 tam =TAM;
 tos = VACIA;
 }

 bool vacia ()
 {
 return tos == VACIA;
 }
 bool llena ()
 {
 return tos == tam-1;
 }
 // El siguiente metodo lee el caracter que se encuentra
 // en la cima de la pila
 // Regresa '\0' si esta vacia
 // No modifica tos, solo lee
 char top ()
 {
 char val = '\0'; // caracter de fin de cadena o caracter nulo
 if (!vacia ())
 val = datos [tos];
 return val;

 }
 void push (char val)
 {
 if (!llena ())
 datos [++tos]= val;
 else
 cout << "\nPila llena el dato " << val << " no se puede agregar" << endl;
 }
 char pop ()
 {
 char val='\0'; // caracter de fin de cadena o caracter nulo
 if (!vacia ())
 val = datos [tos--];
 else
 cout << "\nPila vacia, no se puede eliminar" << endl;
 return val;
 }
};

class convierte_expresion
{
 public:
// El metodo postix recibe en ei la expresion en infix
// y la expresion postfix convertida la deja en ep
 void postfix (char ei [], char ep [])
 {
 Pila pa; // esta pila es para convertir de infix a postfix

 int i = 0,j=0;
 while (ei [i] != '\0')
 {
 if (ei [i] >= 'a' && ei [i] <= 'z' || ei [i]>='A' && ei [i] <= 'Z')
 {
 ep [j] = ei [i];
 i++;
 j++;
 }
 else
 if (ei [i]==' (')
 {
 pa.push (ei [i]);
 i++;
 }
 else if (ei [i]==')')
 {
 while ( pa.top () != ' (')
 {
 ep [j]= pa.pop ();
 j++;
 }
 if (pa.top () == ' (')
 {
 pa.pop ();
 }
 i++;
 }

 else if (ei [i]=='+' || ei [i]=='-' || ei [i]=='*' || ei [i]=='/')
 {
 if (ei [i]=='+' || ei [i] == '-')
 {
 while (!pa.vacia () && pa.top () != ' (')
 {
 ep [j]=pa.pop ();
 j++;
 }
 pa.push (ei [i]);
 i++;
 }
 else
 {
 if (ei [i]=='*' || ei [i]=='/')
 {
 while (!pa.vacia () && pa.top () != ' (' && (pa.top ()=='*'|| pa.top ()=='/'))
 {
 ep [j]=pa.pop ();
 j++;
 }

 pa.push (ei [i]);
 i++;
 }
 } }
 else
 {
 cout<<"CARACTER INVALIDO"<<endl;
 ei [i] = '\0';
 }

 }

 while (!pa.vacia ())
 {
 ep [j]=pa.pop ();
 j++;
 }
 ep [j] = '\0';

 }
};
class lista {
 private:
    int tam;
    int n;
    char* datos;
 public:
    lista(int t) {
        tam = t;
        n = 0;
        datos = new char[t];
    }
    ~lista() {
        delete [] datos;
    }
    bool vacia() {
        return n == 0;
    }
    bool llena() {
        return n == tam;
    }
    void insertar(char val) {
        if (!llena()) {
            datos[n++] = val;
        }
    }
    char obtener(int i) {
        return datos[i];
    }
    int longitud() {
        return n;
    }
};
void postfix (char ei [], char ep []) {
    Pila pa;
    lista lista_caracteres(TAM);

    int i = 0,j=0;
    while (ei [i] != '\0') {
        if (ei [i] >= 'a' && ei [i] <= 'z' || ei [i]>='A' && ei [i] <= 'Z') {
            ep [j] = ei [i];
            lista_caracteres.insertar(ei [i]); // agregar caracter a la lista
            i++;
            j++;
        }
        else if (ei [i]=='(') {
            pa.push (ei [i]);
            i++;
        }
        else if (ei [i]==')') {
            while ( pa.top () != '(') {
                ep [j]= pa.pop ();
                j++;
            }
            if (pa.top () == '(') {
                pa.pop ();
            }
            i++;
        }
        else if (ei [i]=='+' || ei [i]=='-' || ei [i]=='*' || ei [i]=='/') {
            if (ei [i]=='+' || ei [i] == '-') {
                while (!pa.vacia () && pa.top () != '(') {
                    ep [j]=pa.pop ();
                    j++;
                }
                pa.push (ei [i]);
                i++;
            }
            else {
                if (ei [i]=='*' || ei [i]=='/') {
                    while (!pa.vacia () && pa.top () != '(' && (pa.top ()=='*'|| pa.top ()=='/')) {
                        ep [j]=pa.pop ();
                        j++;
                    }
                    pa.push (ei [i]);
                    i++;
                }
            }
        }
        else {
            cout<<"CARACTER INVALIDO"<<endl;
            ei [i] = '\0';
        }
    }

    // imprimir la lista de caracteres
    cout << "Lista de caracteres:" << endl;
    for (int k = 0; k < lista_caracteres.longitud(); k++) {
        cout << lista_caracteres.obtener(k) << " ";
    }
    cout << endl;

    while (!pa.vacia ()) {
        ep [j]=pa.pop ();
        j++;
    }
    ep [j] = '\0';
}

int main ()
{
 char expresion_infix [TAM];
 char expresion_postfix [TAM];
 convierte_expresion ce;

 cout << "La expresion en infix solo debe contener:" << endl;
 cout << "1) Caracteres alfabeticos individuales entre los operadores" << endl;
 cout << "2) Operadores aritmeticos basicos: + - * /" << endl;
 cout << "3) Parentesis, pueden ser con anidamientos" << endl;
 cout << "4) Longitud maxima de la expresion: "<< TAM -1 << "\n" << endl;

 cout << "\nEscribe tu expresion en infix:" << endl;
 cin.getline (expresion_infix, TAM-1); // al leer la cadena getline () pone como ultimo caracter '\0'
 ce.postfix (expresion_infix, expresion_postfix);

 cout << "\n**************************************************************" << endl;
 cout << "\nLa cadena infija \n" << expresion_infix << endl;
 cout << "\nConvertida en postfix \n" << expresion_postfix << endl;
 cout << "\n**************************************************************" << endl;

    return 0;
 }
