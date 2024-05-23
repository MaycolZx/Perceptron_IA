#ifndef CODETEST_H
#define CODETEST_H
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

// float sigmoide(float x) { return 1.0f / (1.0f + std::exp(-x)); }
// bool reLU(int valor) { return valor > 0; }
// float reLU(float x) { return (x > 0) ? x : 0; }

class codeTestPJ {
public:
  codeTestPJ();
   ~codeTestPJ();
  void codeTestProbamos(int numGeneracion);
  int multiplicarMatrices(std::vector<std::vector<float>> &matriz1,
                        std::vector<std::vector<float>> &matriz2);
private:
  int numeroValidA = 0;
  vector<vector<float>> leerCSV(const string &nombreArchivo);
  vector<vector<float>> valoresRpesos = leerCSV("./pesosss49.csv");
  void agregarNumeroCSV(const std::string &nombreArchivo, float numero, int numGeneracion);
  vector<int> recalculandoPesos(vector<vector<float>> &matxPesos,
                              vector<vector<float>> &inputN,
                              vector<vector<float>> &resulFunct);
  float precisionEntrenamiento(float numeroCorrecto, float numeroTotal);
  float reLU(float x);
  //Funciones Debug
  void printRPesos();
};

codeTestPJ::codeTestPJ() {}

codeTestPJ::~codeTestPJ() {}

void codeTestPJ::agregarNumeroCSV(const std::string &nombreArchivo, float numero, int numGeneracion) {
  // Abrir el archivo en modo de añadir (append)
  std::ofstream archivo(nombreArchivo, std::ios::app);
  // Comprobar si el archivo se abrió correctamente
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
    return;
  }
  // Escribir el número en el archivo seguido de una nueva línea
  archivo <<"El numero de Generacion es: "<< numGeneracion <<", "<< numero << std::endl;
  archivo.close();
}

void codeTestPJ::printRPesos(){
  for (const auto &fila : valoresRpesos) {
    for (const auto &valor : fila) {
      cout << valor << " ";
    }
    cout << endl;
  }
}

vector<vector<float>> codeTestPJ::leerCSV(const string &nombreArchivo) {
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

float codeTestPJ::reLU(float x) {
  if (x > 14000) {
    return 1;
  } else {
    return 0;
  }
}

float codeTestPJ::precisionEntrenamiento(float numeroCorrecto, float numeroTotal) {
  float precisionE = numeroCorrecto / numeroTotal;
  return precisionE;
}

vector<int> codeTestPJ::recalculandoPesos(vector<vector<float>> &matxPesos,
                              vector<vector<float>> &inputN,
                              vector<vector<float>> &resulFunct) {
  int valorTivo = inputN[0][0];
  cout << "Valor objetivo: " << valorTivo << endl;
  float tazaAp = 0.5;
  vector<int> indexSearch = {};
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
  return indexSearch;
}


int codeTestPJ::multiplicarMatrices(std::vector<std::vector<float>> &matriz1,
                        std::vector<std::vector<float>> &matriz2) {
  float biasV = 0;
  int filas_matriz1 = matriz1.size();
  int columnas_matriz1 = matriz1[0].size();
  int filas_matriz2 = matriz2.size() - 1;
  int columnas_matriz2 = matriz2[0].size();
  cout << "Matriz 01 es : " << filas_matriz1 << " x " << columnas_matriz1
       << endl;
  cout << "Matriz 02 es: " << filas_matriz2 << " x " << columnas_matriz2
       << endl;

  if (columnas_matriz1 != filas_matriz2) {
    std::cerr << "Error: Las matrices no son compatibles para multiplicación."
              << std::endl;
    return 0;
  }
  float opResult = 0.0f;
  int epocIndex = 0;
  std::vector<std::vector<float>> resultado(
      filas_matriz1, std::vector<float>(columnas_matriz2, 0.0f));

  // for (int i = 0; i < filas_matriz1; ++i) {
  //   for (int j = 0; j < columnas_matriz2; ++j) {
  //     resultado[i][j] = 0.0f;
  //   }
  // }
  for (int i = 0; i < filas_matriz1; ++i) {
    for (int j = 0; j < columnas_matriz2; ++j) {
      for (int k = 0; k < columnas_matriz1; ++k) {
        resultado[i][j] += matriz1[i][k] * matriz2[k + 1][j];
      }
      resultado[i][j] += biasV;
      }
  }
  vector<int> rCond = recalculandoPesos(matriz1, matriz2, resultado);
  if (rCond.size() == 0) {
    numeroValidA++;
  }
  return 1;
}

void codeTestPJ::codeTestProbamos(int numGeneracion) {
  // std::ifstream archivo("E:\\DOWNLOAD\\mnist.csv");//Descomentar de estas en windows
  std::ifstream archivo("./mnist_test.csv");
  std::string linea;

  int contadorTMP = 0;
  while (std::getline(archivo, linea)) {
    cout << "Data-#" << contadorTMP << " del CSV" << endl;
    vector<vector<float>> inputVector;
    vector<float> numeros;
    string numero_str;
    for (char caracter : linea) {
      if (caracter != ',') {
        numero_str += caracter;
      } else {
        numeros.push_back(std::stoi(numero_str));
        numero_str = "";
      }
    }
    numeros.push_back(std::stoi(numero_str));
    for (int numero : numeros) {
      vector<float> valoresIngresoM;
      valoresIngresoM.push_back(numero);
      inputVector.push_back(valoresIngresoM);
    }
    cout << "El tamano del vector es: " << inputVector.size() << endl;
    multiplicarMatrices(valoresRpesos, inputVector);
    contadorTMP++;
  }

  float valPr = precisionEntrenamiento(numeroValidA, 10000.0f);
  cout << "La precision del entrenamiento es de: " << valPr << endl;
  std::string nombreArchivo = "generacionesLvlPrec.csv";
  agregarNumeroCSV(nombreArchivo, valPr, numGeneracion);
  archivo.close();
}

#endif
