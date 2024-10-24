#include "pila.hpp"
#include "math.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


class super_string {
 private:
 struct nodo {
 nodo *left = nullptr, *right = nullptr;
 int index;
 char c;
 nodo(int index, char c) {}
 nodo(){}
 };
 int height = 0; // Altura del árbol
 int length = 0; // Largo del super-string
 nodo* root = nullptr; // Raíz del super-string
 public:
 super_string() {}
 void juntar(super_string &s);
 void juntarHelp(nodo* actual);
 void agregar(char c); // Insertar un caracter en la última posición
 // En la izquierda esta el super_string a y en la derecha el super_string b
 void separar(int i, super_string &a, super_string &b);
 void separarHelp(nodo* actual, super_string &arbol, int index_min, int index_max);
 void reverso(); // No debe cambiar la altura del árbol
 void reversoHelp(nodo* actual, Pila &p);
 int recortar(); // Retorna this->height después de recortar
 string stringizar(); // Debe ser O(n)
 void stringizarHelp(nodo* actual, char* &caracteres, int &pos);
 void limpiar(); // Se deben borrar todos los nodos del super-string
 void limpiarHelp(nodo* actual); 
 void mostrar();
 void mostrarHelp(nodo* actual);
};

/*****
* void super_string::juntar
******
* Juntar dos super_strings con ayuda de la funcion juntarHelp y actualiza heigth y length.
******
* Input:
* super_string& s : Referencia al super_string a juntar con el actual.
******
* Returns:
* void, Modifica el super_string actual.
*****/


void super_string::juntar(super_string &s){
    if(s.root == nullptr) return;
    juntarHelp(s.root);
    height = height + s.height;
    length = length + s.length;
}
/*****
* void super_string::juntarHelp
******
* recorre el arbol a partir de un nodo y se llama recursivamente agregando el valor en inorder
******
* Input:
* nodo* s_actual : nodo actual del arbol
******
* Returns:
* void, Modifica el super_string actual.
*****/

void super_string::juntarHelp(nodo* s_actual){

    if (s_actual == nullptr) return;

    juntarHelp(s_actual->left);
    agregar(s_actual->c);
    juntarHelp(s_actual->right);


}

/*****
* void super_string::agregar
******
* Agregar un caracter al final del super_string.
******
* Input:
* char c : Caracter a agregar.
******
* Returns:
* void, Modifica el estado del super_string actual.
*****/

void super_string::agregar(char c) {
    if (root == nullptr)
    {
        root = new nodo;
        root->index = 0;
        root->c = c;
        return;
    }

    int indice = 0;
    nodo* actual = root;
    while (actual->right != nullptr)
    {
        actual = actual->right;
        indice = actual->index;

    }
    actual->right = new nodo;
    actual->right->c = c;
    actual->right->index = ++indice;
    height++;
    length++;


}
/*****
* void super_string::separar
******
* Separar el super_string en dos partes en el índice dado con ayuda de separarHelp.
******
* Input:
* int i : Índice de separación.
* super_string& a : Referencia al super_string para almacenar la parte izquierda.
* super_string& b : Referencia al super_string para almacenar la parte derecha.
******
* Returns:
* void, Modifica el estado de los super_strings a y b.
*****/


void super_string::separar(int i, super_string &a, super_string &b){
    
    a.limpiar();
    b.limpiar();
    separarHelp(root, a, 0, i);
    separarHelp(root, b, i, length);
}

/*****
* void super_string::separarHelp
******
* Función auxiliar para separar el super_string agregando en preorden el char.
******
* Input:
* nodo* actual : Puntero al nodo actual del super_string.
* super_string& arbol : Referencia al super_string para almacenar la parte separada.
* int index_min : Índice mínimo para la separación.
* int index_max : Índice máximo para la separación.
******
* Returns:
* void, modifica el super_string dado.
*****/


void super_string::separarHelp(nodo*actual, super_string &arbol, int index_min, int index_max){
    if(actual == nullptr) return;

    if(actual->index >= index_min && actual->index <= index_max){
        arbol.agregar(actual->c);
    }

    separarHelp(actual->left, arbol, index_min, index_max);
    separarHelp(actual->right, arbol, index_min, index_max);

}

/*****
* void super_string::reverso
******
* Invertir el contenido del super_string usando una pila pala almacenar los char.
******
* Input:
* No tiene parámetros adicionales.
******
* Returns:
* void, Modifica el estado del super_string actual invirtiendo su contenido.
*****/


void super_string::reverso(){
    Pila p;

    reversoHelp(root, p);
    limpiar();
    while (!p.estaVacia())
    {
        agregar(p.mostrar());
        p.pop();
    }
    
    

}

/*****
* void super_string::reversoHelp
******
* Función auxiliar para invertir el contenido del super_string agregando los char en inorder.
******
* Input:
* nodo* actual : Puntero al nodo actual del super_string.
* Pila& p : Referencia a una pila para ayudar en la reversión.
******
* Returns:
* void, No hay retorno explícito.
*****/


void super_string::reversoHelp(nodo* actual, Pila &p){
    if (actual == nullptr) return;

    reversoHelp(actual->left, p);
    p.push(actual->c);
    p.mostrar();
    reversoHelp(actual->right, p);
}

/*****
* string super_string::stringizar
******
* Convertir el contenido del super_string en una cadena de caracteres.
******
* Input:
* No tiene parámetros adicionales.
******
* Returns:
* string, Super-string generado.
*****/


string super_string::stringizar() {
    if(root == nullptr) return "";

    int contador = 0;
    //nodo* actual = root;
    char* palabra = new char[length];
/* 
    while (actual != nullptr)
    {
        palabra[contador++] = actual->c;
        actual = actual->right;
    } */
    stringizarHelp(root, palabra, contador);
  
    string str(palabra, length+1);
    delete[] palabra;
    return str;    

}

/*****
* void spuer_string::stringizarHelp
******
* Función auxiliar para convertir el contenido del super_string en una cadena de caracteres agregandolos aun char.
******
* Input:
* nodo* actual : Puntero al nodo actual del super_string.
* char*& caracteres : Referencia a un arreglo de caracteres para almacenar la cadena.
* int& pos : Referencia a la posición actual en el arreglo de caracteres.
******
* Returns:
* void, No hay retorno explícito.
*****/


void super_string::stringizarHelp(nodo* actual, char* &caracteres, int &pos) {
    if (actual == nullptr) return;

    stringizarHelp(actual->left, caracteres, pos);
    caracteres[pos++] = actual->c;
    stringizarHelp(actual->right, caracteres, pos);
}

/*****
* void super_string::limpiar
******
* Limpiar el super_string eliminando todos los nodos del árbol y reseteando sus valores.
******
* Input:
* No tiene parámetros adicionales.
******
* Returns:
* void, Modifica el estado del super_string actual.
*****/


void super_string::limpiar(){
    limpiarHelp(root);
    root = nullptr;
    length = 0;
    height = 0;

}

/*****
* void super_string::limpiarHelp
******
* Función auxiliar para limpiar el super_string eliminando los nodos en postorden.
******
* Input:
* nodo* actual : Puntero al nodo actual del super_string.
******
* Returns:
* void, No hay retorno explícito.
*****/


void super_string::limpiarHelp(nodo* actual){
    if (actual == nullptr) return;

    limpiarHelp(actual->left);
    limpiarHelp(actual->right);

    
    delete actual;



    
}

/*****
* void super_string::mostrar
******
* Mostrar el contenido del super_string en la consola.
******
* Input:
* No tiene parámetros adicionales.
******
* Returns:
* void, Imprime en la consola el contenido del super_string actual.
*****/


void super_string::mostrar() {
    if (root == nullptr) {
        cout << "El super_string está vacío." << endl;
        return;
    }
    mostrarHelp(root); 
    cout << endl;
}

/*****
* void super_string::mostrarHelp
******
* Función auxiliar para mostrar el contenido del super_string mostrando el caracter en inorder.
******
* Input:
* nodo* actual : Puntero al nodo actual del super_string.
******
* Returns:
* void, No hay retorno explícito.
*****/


void super_string::mostrarHelp(nodo* actual) {
    if (actual == nullptr) {
        return;
    }
    mostrarHelp(actual->left);
    cout << actual->c;
    mostrarHelp(actual->right);
}


/*****
* int super_string::recortar
******
*  calcular y retornar la altura del árbol resultante.
******
* Input:
* No tiene parámetros adicionales.
******
* Returns:
* int aproximado, Altura del árbol después del recorte.
*****/



int super_string::recortar(){
  
    float i = log(length + 1) / log(2); 
    int aproximado = (int)ceil(i);

    return aproximado;
}

/*****
* super_string insertar
******
* funcion que a partir de un string incerta en un indice sus caracteres en el super_string .
******
* Input:
* int i: indice en el cual se quiere insertar el string.
* string s : string que se quiere agregar al super_string.
* super_string palabra: super_string en el que se quiete insertar el string
******
* Returns:
* super_string palabra : super_string actualizado 
*****/


super_string insertar(int i, string s, super_string palabra){
    
    if (i == 0){
        for (char c : s)
        {
            palabra.agregar(c);
        }
        return palabra;
        
    }

    super_string palabra2;
    for (char c : s)
    {
        palabra.agregar(c);
    }
    palabra.juntar(palabra2);
    
    return palabra;

}

/*****
* void eliminar
******
* elimina cierta parte del super_string a partir de dos indices.
******
* Input:
* int numero1: indice en que inicia los caracteres a eliminar.
* int numero2: indice en el que termina los caracteres a eliminar.
* super_string palabra: super_string el cual se quiere eliminar una parte.
******
* Returns:
* super_string a : super_string con la parte ya eliminada
*****/


super_string eliminar(int numero1, int numero2, super_string palabra){
    super_string a, b, c, d;

    palabra.separar(numero1-1,a,b);
    b.separar(numero2,c,d);

    a.juntar(d);
    palabra.limpiar();
    b.limpiar();
    c.limpiar();
    d.limpiar();
    return a;

}

/*****
* void extraerNumeros
******
* a partir de un string extrae los 2 numeros que hay en el si hay solo uno el num2 es 0.
******
* Input:
* const string& texto: referencia al texto que se quiere extraer los numeros.
* int& num1: referencia a la variable para el primer numero. 
* int& num2: referencia a la variable para el segundo numero.
******
* Returns:
* void, No hay retorno explícito.
*****/



void extraerNumeros(const string& texto, int& num1, int& num2) {
    string numero;
    int contador = 0;

    for (char c : texto) {
        if (isdigit(c)) {
            numero += c;
        } else if (!numero.empty()) {
            if (contador == 0) {
                num1 = stoi(numero);
            } else if (contador == 1) {
                num2 = stoi(numero);
            }
            numero.clear();
            contador++;
        }
    }

    if (!numero.empty() && contador == 1) {
        num2 = stoi(numero);
    }
}




int main() {

    super_string palabra;
    ifstream archivo("prueba.txt");
    string linea;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    while (getline(archivo, linea)) {
        cout << linea << endl;

        if (linea == "FIN") {palabra.limpiar(); break;}

        if (linea == "MOSTRAR") {
            palabra.mostrar();
            continue;
        }

        string funcion = linea.substr(0, 8);

        if (funcion == "INSERTAR") {
            int numero1, numero2;
            extraerNumeros(linea, numero1, numero2);
            size_t posEspacio = linea.find(' ', linea.find(' ') + 1);
            string texto = linea.substr(posEspacio + 1);
            palabra = insertar(numero1, texto, palabra);

        }
        
        if (funcion == "ELIMINAR") {
            int numero1, numero2;
            extraerNumeros(linea, numero1, numero2);
            palabra = eliminar(numero1, numero2, palabra);
        }

        if (funcion == "RECORTAR") {
            cout << palabra.recortar() << endl;
        }

        if(funcion == "REVERSO "){
        
            palabra.reverso();
        }
    }

    archivo.close();
    return 0;

}
