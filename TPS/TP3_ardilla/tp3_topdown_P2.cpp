#include <iostream>
#include <vector>

using namespace std;
int INF = 1000;
vector<vector<int>> nueces = {
                              {0, 1, 1},
                              {1, 0, 1},
                              {0, 1, 0},
                              {0, 1, 0},
                              {1, 0, 1},
                              {0, 1, 0}
                              };
int n = nueces.size();
int m = nueces[0].size();
vector<vector<int>> DPT(n+1, vector<int>(m));
/*
Idea:
Puedo calcular, para todos los caminos posibles, el beneficio de mantenerme
en el arbol o cambiar de arbol mientras colecto nueces.
La funcion toma la altura y el arbol i en donde estoy, y calcula el max entre todos
los caminos que puedo tomar al elegir mantenerme en el arbol i, y perder -1 de altura,
o camibarme a los arboles i+1 y/o i-1, y perder -2 de altura.
*/
/*
Semantica de la funcion objetivo:
f(i, j): de la maxima cantidad de nueces que se pueden recolectar partiendo
de la altura i y del arbol j.

CASOS BASE:
Si caigo en un arbol no valido, o me pase de la altura permitida, ese camino no es
valido. Devulevo -inf para que no se considere en el maximo:
-inf      si h < 0 or (0<=i+1<=n) or (0<=i-1<=n)   ()
si llego a la altura h, es un camino valido
0         si h = 0
en otro caso, doy el resultado de agarrar la nuez actual mas el maximo
de mantenerme en el arbol, o tomar los caminos de los arboles aledaños
nueces[i][j] + max(f(i-1, j), f(i-2, j-1), f(i-2, j+1))
*/
int cantLlamados = 0;
int f(int i, int j, int k){
  cantLlamados++;
  if(i < 0){
    return -INF;
  }else if(i==0){
    DPT[0][j] = nueces[0][j];
    return DPT[0][j];
  }
  //chequeo si ya calcule el optimo para lo que queda del camino hacia el suelo
  //como nunca llamo a la funcion con valores invalidos para j, pues nunca salto
  //a un arbol que no tengo permitido, y como la altura si llego aqui es >= 0,
  //esto no se va a indefinir
  if (DPT[i][j] != 0) {
    return DPT[i][j];
  }
  if ((j + 1 < m) && (j - 1 >= 0)){
    //puedo saltar a ambos arboles aledaños. En c++ solo puedo calcular
    //el maximo de a dos. Primero calculo este maximo y luego comparo con
    //la opcion de seguir por el arbol actual
    int max_izq_der = max(f(i-k, j+1, k), f(i-k, j-1, k));
    DPT[i][j] = nueces[i][j] + max(f(i-1, j, k), max_izq_der);
    return DPT[i][j];
  }else if (j + 1 < m) {
    //solo puedo saltar al arbol derecho
    //comparo con la cant de nueces que puedo obtener manteniendome o cambiando de arbol
    DPT[i][j] = nueces[i][j] + max(f(i-1, j, k), f(i-k, j + 1, k));
    return DPT[i][j];
  }else{
    //solo puedo saltar al arbol izquierdo
    //comparo con la cant de nueces que puedo obtener manteniendome o cambiando de arbol
    DPT[i][j] = nueces[i][j] + max(f(i-1, j, k), f(i-k, j - 1, k));
    return DPT[i][j];
  }
}

int main(){
  cout << f(5, 1, 4) << endl;
  cout << "La cantidad de llamados recursivos para obtener la respuesta fue de " << cantLlamados << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << DPT[i][j] << " ";
    }
    cout << endl;
  }
}
