#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> nueces = {
                              {0, 1, 1},
                              {1, 0, 1},
                              {0, 1, 0},
                              {0, 1, 0},
                              {1, 0, 1},
                              {0, 1, 0}
                              };
//voy a llenar toda la DPT, y luego uso h, i para darle al usuario lo que
//quiere. Son mas cuentas pero me parece mas provechoso
int n = nueces.size();
int m = nueces[0].size();
vector<vector<int>> DPT(n+1, vector<int>(m));
//necesito que las filas de la DPT incluyan al 0, por eso es la cantidad
//de filas (altura) de los arboles, +1.
//necesito que las filas de la DPT incluyan al 0, por eso es la cantidad
//de filas (altura) de los arboles, +1.
/*
La idea es crear una matriz DPT[h][i] donde h es la altura e i es el arbol.
DPT[h][i] me da la mayor cantidad de nueces que puedo recolectar si parto
de ese arbol a esa altura.
Debo llenar la matriz para los primeros h = 0, h = 1 niveles, a mano, y
luego uso la siguiente recurrencia para armar la DPT:
DPT[h][i] = nueces[h][i] + max(DPT[h-1][i], DPT[h-2][i+1], DPT[h-2][i-1])
siempre que se cumpla 0<=i+1<=cols_nueces para la segunda opcion y
0<=i-1<=cols_nueces para la segunda
*/

void completarDPT(){
  //para los primeros h = 0, h = 1 alturas, calculo la solucion optima a mano
  for (int k = 0; k < m; k++) DPT[0][k] = nueces[0][k];
  for (int k = 0; k < m; k++) DPT[1][k] = DPT[0][k] + nueces[1][k];

  //para las otras alturas h>=2

  for (int i = 2; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ((j + 1 < m) && (j - 1 >= 0)) {
        //si tanto a izquierda como a derecha tengo arboles a los que puedo saltar
        //el max de c++ solo funciona de a dos elementos
        int max_izq_der = max(DPT[i-2][j+1], DPT[i-2][j-1]);
        //ahora lo comparo con la solucion optima de seguir bajando por este arbol
        DPT[i][j] = nueces[i][j] + max(DPT[i-1][j], max_izq_der);
      }else if (j + 1 < m){
        //solo puedo saltar al arbol derecho. Lo comparo con la solucion
        //optima de seguir bajando por este arbol
        DPT[i][j] = nueces[i][j] + max(DPT[i-1][j], DPT[i-2][j+1]);
      }else{
        //solo puedo saltar al arbol izquierdo. Lo comparo con la solucion
        //optima de seguir bajando por este arbol
        DPT[i][j] = nueces[i][j] + max(DPT[i-1][j], DPT[i-2][j-1]);
      }
    }
  }

  return;
}

int main(){
  cout << n << m << endl;
  //cout << DPT_1[2][2] << endl;
  completarDPT();
  cout << "algo malo paso" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << DPT[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
