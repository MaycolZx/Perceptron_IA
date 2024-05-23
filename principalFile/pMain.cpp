#include "./codeTest.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Función para leer un elemento de un archivo CSV basado en su índice
void leerElementoCSV(const std::string &nombreArchivo, int indiceColumna,
                     std::vector<int> &resultados) {
  std::ifstream archivo(nombreArchivo);
  std::string linea;

  while (std::getline(archivo, linea)) {
    std::stringstream ss(linea);
    std::string elemento;
    int indice = 0;

    while (std::getline(ss, elemento, ',')) {
      if (indice == indiceColumna) {
        try {
          int valor = std::stoi(elemento);
          resultados.push_back(valor);
        } catch (const std::exception &e) {
          std::cerr << "Error al convertir a entero: " << e.what() << std::endl;
          // Puedes manejar el error de conversión aquí
        }
        break;
      }
      indice++;
    }
  }
  archivo.close();
}

// Función para escribir un vector<vector<float>> en un archivo CSV
void escribirCSV(const vector<vector<float>> &datos,
                 const string &nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (archivo.is_open()) {
    for (const auto &fila : datos) {
      for (size_t i = 0; i < fila.size(); ++i) {
        archivo << fila[i];
        if (i != fila.size() - 1)
          archivo << ",";
      }
      archivo << endl;
    }
    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
  } else {
    cout << "No se pudo abrir el archivo " << nombreArchivo
         << " para escritura." << endl;
  }
}

// Función para leer valores flotantes desde un archivo CSV
vector<vector<float>> leerCSV(const string &nombreArchivo) {
  vector<vector<float>> datos;
  ifstream archivo(nombreArchivo);
  if (archivo.is_open()) {
    string linea;
    while (getline(archivo, linea)) {
      stringstream ss(linea);
      vector<float> fila;
      string valor;
      while (getline(ss, valor, ',')) {
        fila.push_back(stof(valor));
      }
      datos.push_back(fila);
    }
    archivo.close();
    cout << "Datos leídos desde " << nombreArchivo << endl;
  } else {
    cout << "No se pudo abrir el archivo " << nombreArchivo << " para lectura."
         << endl;
  }
  return datos;
}

vector<vector<float>> vectoresRandomPesos(int limitNeurons = 10,
                                          int precision = 2) {
  vector<vector<float>> pesosRandom;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0f, 1.0f);

  for (int j = 0; j < limitNeurons; j++) {
    vector<float> pesosVector;
    for (int i = 0; i < 784; i++) {
      float numero_aleatorio = dis(gen) * 100.0f / 100.0f;
      pesosVector.push_back(numero_aleatorio);
    }
    pesosRandom.push_back(pesosVector);
  }
  // Que pesos tiene :Print()
  // for (int i = 0; i < 10; i++) {
  //  for (int j = 0; j < 15; j++) {
  //    cout << std::fixed << std::setprecision(2) << pesosRandom[i][j] << "";
  //  }
  //  cout << endl;
  //}
  return pesosRandom;
}

float sigmoide(float x) { return 1.0f / (1.0f + std::exp(-x)); }

// bool reLU(int valor) { return valor > 0; }

// float reLU(float x) { return (x > 0) ? x : 0; }
float reLU(float x) {
  if (x > 1) {
    return 1;
  } else {
    return 0;
  }
}

float precisionEntrenamiento(float numeroCorrecto, float numeroTotal) {
  float precisionE = numeroCorrecto / numeroTotal;
  return precisionE;
}

vector<int> recalculandoPesos(vector<vector<float>> &matxPesos,
                              vector<vector<int>> &inputN,
                              vector<vector<float>> &resulFunct) {
  // Peso = peso + n(t-o)*xi
  int valorTivo = inputN[0][0];
  cout << "Valor objetivo: " << valorTivo << endl;
  float tazaAp = 0.5;
  vector<int> indexSearch = {};
  cout << "Tamano index: " << indexSearch.size() << endl;
  for (int i = 0; i < resulFunct.size(); i++) {
    float valActivation = reLU(resulFunct[i][0]);
    cout << "#" << i << "-valor de Act: " << valActivation << endl;
    // if ((valorTivo == i && valActivation == 0) ||
    //     (valActivation == 1 && i != valorTivo)) {
    //   indexSearch.push_back(i);
    // }
    if (valorTivo == i && valActivation == 0) {
      indexSearch.push_back(i);
    }
    if (valActivation == 1 && i != valorTivo) {
      indexSearch.push_back(i);
    }
  }
  cout << "Tamano index-Segundo: " << indexSearch.size() << endl;
  // system("clear");
  int valorWaobt = 0;
  if (!indexSearch.empty()) {
    for (int i = 0; i < indexSearch.size(); i++) {
      cout << "Valor del index: " << indexSearch[i] << endl;
      if (indexSearch[i] == valorTivo) {
        valorWaobt = 1;
      } else {
        valorWaobt = 0;
      }
      float valActivation = reLU(resulFunct[indexSearch[i]][0]);
      // vector<float> valorPesosIndex = matxPesos[i];
      for (int k = 0; k < matxPesos[i].size(); k++) {
        matxPesos[indexSearch[i]][k] =
            matxPesos[indexSearch[i]][k] +
            (tazaAp * (valorWaobt - valActivation) * inputN[k + 1][0]);
      }
    }
  }
  return indexSearch;
}

// Función para multiplicar dos matrices representadas como vectores de vectores
std::vector<std::vector<float>>
multiplicarMatrices(std::vector<std::vector<float>> &matriz1,
                    std::vector<std::vector<int>> &matriz2) {
  float biasV = 0;
  int filas_matriz1 = matriz1.size();
  int columnas_matriz1 = matriz1[0].size();
  int filas_matriz2 = matriz2.size() - 1;
  int columnas_matriz2 = matriz2[0].size();
  cout << "Matriz 01 es : " << filas_matriz1 << " x " << columnas_matriz1
       << endl;
  cout << "Matriz 02 es: " << filas_matriz2 << " x " << columnas_matriz2
       << endl;

  // Verificar que las matrices sean multiplicables
  if (columnas_matriz1 != filas_matriz2) {
    std::cerr << "Error: Las matrices no son compatibles para multiplicación."
              << std::endl;
    return std::vector<std::vector<float>>(); // Devolver matriz vacía en caso
                                              // de error
  }

  // Crear la matriz resultado inicializada con ceros
  float opResult = 0.0f;

  int epocIndex = 0;
  std::vector<std::vector<float>> resultado(
      filas_matriz1, std::vector<float>(columnas_matriz2, 0.0f));

  while (true) {
    // Realizar la multiplicación de matrices
    for (int i = 0; i < filas_matriz1; ++i) {
      for (int j = 0; j < columnas_matriz2; ++j) {
        resultado[i][j] = 0.0f;
      }
    }

    cout << "Epoca-#" << epocIndex << endl;
    for (int i = 0; i < filas_matriz1; ++i) {
      for (int j = 0; j < columnas_matriz2; ++j) {
        for (int k = 0; k < columnas_matriz1; ++k) {
          resultado[i][j] += matriz1[i][k] * matriz2[k + 1][j];
        }
        resultado[i][j] += biasV;
        // cout << "Un resultado es: " << resultado[i][j] << endl;
        cout << "#-" << i << " " << fixed << setprecision(8) << resultado[i][j]
             << endl;
      }
      // resultado[i].push_back();
    }
    vector<int> rCond = recalculandoPesos(matriz1, matriz2, resultado);
    if (rCond.size() == 0) {
      break;
    }
    epocIndex++;
    // system("sleep 2");
  }
  // vector<vector<float>> datos = {
  //     {1.2, 3.4, 5.6}, {7.8, 9.0, 1.2}, {3.4, 5.6, 7.8}};
  string nombreArchivo = "datosPesos.csv";

  escribirCSV(matriz1, nombreArchivo);
  // vector<vector<float>> datosLeidos = leerCSV(nombreArchivo);

  // Imprimir los datos leídos
  // for (const auto &fila : datosLeidos) {
  //   for (const auto &valor : fila) {
  //     cout << valor << " ";
  //   }
  //   cout << endl;
  // }
  vector<vector<float>> valorTmpR;
  return valorTmpR;
}

void vamosAcrearVector() {
  // std::ifstream archivo("E:\\DOWNLOAD\\mnist.csv");//Descomentar de estas en
  // window y cambiar de direccion

  vector<vector<float>> valoresRpesos = leerCSV("./pesosss49.csv");
  // vector<vector<float>> valoresRpesos(10, vector<float>(784, 0.0f));

  // vector<vector<float>> valoresRpesos = vectoresRandomPesos();
  std::ifstream archivo("./mnist.csv");
  std::string linea;

  // int contadorTMP = 0;
  while (std::getline(archivo, linea)) {
    // std::getline(archivo, linea);
    vector<vector<int>> inputVector;
    vector<int> numeros;
    string numero_str;
    int valorRI;
    int contadorTMPa = 1;
    for (char caracter : linea) {
      if (caracter != ',') {
        numero_str += caracter;
      } else {
        valorRI = std::stoi(numero_str);
        if (contadorTMPa == 1) {
          numeros.push_back(std::stoi(numero_str));
          contadorTMPa = 2;
          continue;
        }
        if (valorRI > 127.5) {
          numeros.push_back(0);
        } else {
          numeros.push_back(1);
        }
        numero_str = "";
      }
    }
    numeros.push_back(std::stoi(numero_str));
    for (int numero : numeros) {
      vector<int> valoresIngresoM;
      valoresIngresoM.push_back(numero);
      inputVector.push_back(valoresIngresoM);
    }
    // for (int i = 0; i < inputVector.size(); i++) {
    //   for (int j = 0; j < inputVector[i].size(); j++) {
    //     cout << inputVector[i][j] << " ";
    //   }
    // }
    // cout << endl << "Este es el limite del primero " << endl;
    //
    cout << "El tamano del vector es: " << inputVector.size() << endl;
    std::vector<std::vector<float>> resultado =
        multiplicarMatrices(valoresRpesos, inputVector);
    // contadorTMP++;
    // if (contadorTMP == 3) {
    //   break;
    // }
  }
  archivo.close();
}

// Función para sumar dos matrices representadas como vectores de vectores
// std::vector<std::vector<float>>
// sumarMatrices(const std::vector<std::vector<float>> &matriz1,
//               const std::vector<std::vector<float>> &matriz2) {
//   int filas = matriz1.size();
//   int columnas = matriz1[0].size();
//
//   // Verificar que las matrices tengan las mismas dimensiones
//   if (filas != matriz2.size() || columnas != matriz2[0].size()) {
//     std::cerr << "Error: Las matrices tienen dimensiones diferentes."
//               << std::endl;
//     return std::vector<std::vector<float>>(); // Devolver matriz vacía en
//     caso
//                                               // de error
//   }
//
//   // Crear la matriz resultado inicializada con ceros
//   std::vector<std::vector<float>> resultado(filas,
//                                             std::vector<float>(columnas,
//                                             0.0f));
//
//   // Realizar la suma de matrices
//   for (int i = 0; i < filas; ++i) {
//     for (int j = 0; j < columnas; ++j) {
//       resultado[i][j] = matriz1[i][j] + matriz2[i][j];
//     }
//   }
//
//   return resultado;
// }

float costDif(int valorDeseado) {
  float wave02[10] = {};
  float resultadoCost = 0;
  for (int i = 0; i < 10; i++) {
    if (i == valorDeseado) {
      resultadoCost += pow(wave02[i] - 1, 2);
      continue;
    }
    resultadoCost += wave02[i];
  }
  return resultadoCost;
}

int main() {
  // vector<vector<float>> valoresRpesos = vectoresRandomPesos();
  // vector<vector<float>> numerosInput;
  codeTestPJ codeT;
  int contadorATMP = 4;
  // while (contadorATMP <= 100) {
  // vamosAcrearVector(); // Funcion de entrenamiento
  // vector<vector<float>> valoresRpesos = leerCSV("./datosPesos.csv");
  // for (int i = 0; i < valoresRpesos.size(); i++) {
  // for (int j = 0; j < valoresRpesos[0].size(); j++) {
  //   cout << valoresRpesos[0][j] << ", ";
  // }
  // cout << endl;
  // }
  //
  codeT.codeTestProbamos(contadorATMP); // Funcion de TEST
  //
  // contadorATMP++;
  // }
  // for (int indexCsv = 0; indexCsv < 5; indexCsv++) {
  //   numerosInput = vamosAcrearVector(indexCsv);
  //   cout << "El tamano del vector es: " << numerosInput.size() << endl;
  //   std::vector<std::vector<float>> resultado =
  //       multiplicarMatrices(valoresRpesos, numerosInput);
  // }

  // std::vector<int> resultadosMIndex;
  // std::string nombreArchivo = "mnist.csv";
  // int indiceColumnaDeseado = 0;
  //
  // leerElementoCSV(nombreArchivo, indiceColumnaDeseado, resultadosMIndex);
  //
  // // Imprimir los valores leídos
  // for (int valor : resultadosMIndex) {
  //   std::cout << valor << " ";
  // }
  // cout << endl;
  return 0;
}

// otherFunction
// std::vector<std::vector<float>>
// multiplicarMatrices(const std::vector<std::vector<float>> &matriz1,
//                     const std::vector<std::vector<float>> &matriz2) {
//   float biasV = 1;
//   int filas_matriz1 = matriz1.size();
//   int columnas_matriz1 = matriz1[0].size();
//   int filas_matriz2 = matriz2.size() - 1;
//   int columnas_matriz2 = matriz2[0].size();
//   cout << "Matriz 01 es : " << filas_matriz1 << " x " << columnas_matriz1
//        << endl;
//   cout << "Matriz 02 es: " << filas_matriz2 << " x " << columnas_matriz2
//        << endl;
//
//   // Verificar que las matrices sean multiplicables
//   if (columnas_matriz1 != filas_matriz2) {
//     std::cerr << "Error: Las matrices no son compatibles para
//     multiplicación."
//               << std::endl;
//     return std::vector<std::vector<float>>(); // Devolver matriz vacía en
//     caso
//                                               // de error
//   }
//
//   // Crear la matriz resultado inicializada con ceros
//   std::vector<std::vector<float>> resultado(
//       filas_matriz1, std::vector<float>(columnas_matriz2, 0.0f));
//   float opResult = 0.0f;
//   // std::vector<std::vector<float>> resultadoTMP;
//   std::vector<std::vector<double>> resultadoTMP(
//       filas_matriz1, std::vector<double>(columnas_matriz2, 0.0));
//
//   // Realizar la multiplicación de matrices
//   for (int i = 0; i < filas_matriz1; ++i) {
//     for (int j = 0; j < columnas_matriz2; ++j) {
//       opResult = 0.0f;
//       double temp = 0.0f;
//       for (int k = 0; k < columnas_matriz1; ++k) {
//         // resultado[i][j] += matriz1[i][k] * matriz2[k][j + 1];
//         temp = matriz1[i][k] * matriz2[k][j + 1];
//         opResult += temp;
//       }
//       // resultado[i][j] += biasV;
//       cout << "Un resultado es: " << resultado[i][j] << endl;
//       cout << "Un es: " << opResult << endl;
//       // vector<float> vectAdd = {opResult};
//       // resultadoTMP.push_back(vectAdd);
//       resultadoTMP[i][j] = opResult;
//     }
//     // resultado[i].push_back();
//   }
//
//   for (int i = 0; i < resultado.size(); i++) {
//     for (int j = 0; j < resultado[i].size(); j++) {
//       // cout << resultado[i][j] << endl;
//       cout << fixed << setprecision(8) << resultadoTMP[i][j] << endl;
//     }
//   }
//
//   return resultado;
// }
