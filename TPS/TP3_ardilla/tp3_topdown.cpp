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
int cant_llamados = 0;
int f(int i, int j){
  cant_llamados++;
  if(i < 0){
    return -INF;
  }else if(i==0){
    return nueces[0][j];
  }
  if ((j + 1 < m) && (j - 1 >= 0)){
    //puedo saltar a ambos arboles aledaños. En c++ solo puedo calcular
    //el maximo de a dos. Primero calculo este maximo y luego comparo con
    //la opcion de seguir por el arbol actual
    int max_izq_der = max(f(i-2, j+1), f(i-2, j-1));
    return nueces[i][j] + max(f(i-1, j), max_izq_der);
  }else if (j + 1 < m) {
    //solo puedo saltar al arbol derecho
    //comparo con la cant de nueces que puedo obtener manteniendome o cambiando de arbol
    return nueces[i][j] + max(f(i-1, j), f(i-2, j + 1));
  }else{
    //solo puedo saltar al arbol izquierdo
    //comparo con la cant de nueces que puedo obtener manteniendome o cambiando de arbol
    return nueces[i][j] + max(f(i-1, j), f(i-2, j - 1));
  }
}

int main(){
  cout << f(5, 1) << endl;
  cout << "La cantidad de llamados recursivos para obtener la respuesta fue de " << cant_llamados << endl;
  /*
  En cada llamado recursivo se van abriendo 3 posibilidades si j = 1 (el arbol del medio)
  o dos posibilidades si j = 0 o j = 2 (los arboles de los extremos).
  Si los arboles fueran muchos j -> inf entonces esperaria que todos los arboles
  tuvieran 3 opciones y la complejidad exacta seria omega(3**n)
  */
  cout << 3*3*3*3 << endl; //difiere mucho de la cantidad de llamados realizados. preguntar
  //si la hipotesis de la complejidad es correcta
}
