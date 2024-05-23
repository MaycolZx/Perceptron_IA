#include <GL/freeglut.h>
#include <GL/glut.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

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
vector<float> valoresBar = {1500};
// Dimensiones de la ventana
int windowWidth = 800;
int windowHeight = 600;

// Valores del vector de ejemplo
std::vector<float> values;
std::vector<float> valuesErr;
// std::vector<float> values = {
//     10.5, 20.0, 35.5, 50.0, 65.5, 80.0, 95.0, 10.5, 20.0, 35.5,
//     50.0, 65.5,
//     80.0, 95.0, 10.5, 20.0, 35.5, 50.0, 65.5, 80.0, 95.0, 10.5,
//     20.0, 35.5,
//     50.0, 65.5, 80.0, 95.0, 10.5, 20.0, 35.5, 50.0, 65.5, 80.0,
//     95.0};
// Margen de desplazamiento para los ejes
float axisOffset = 10.0f;

void storeValue(string nombreF, int totalD) {
  std::vector<vector<float>> dataPair = leerCSV("./error.csv");
  float precision = 0;
  for (int i = 0; i < dataPair.size(); i++) {
    precision = (dataPair[i][0] / 100) * 100;
    values.push_back(precision);
    precision = (dataPair[i][1]);
    valuesErr.push_back(precision);
  }
}
// Función para inicializar OpenGL
void initGL() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Color de fondo blanco
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-axisOffset, 600 + axisOffset, -axisOffset,
             100 + axisOffset); // Ajustar el sistema de coordenadas
}

// Función para dibujar texto
void drawText(float x, float y, std::string text) {
  glRasterPos2f(x, y);
  for (char c : text) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
  }
}

// Función para dibujar barras
void display() {
  glClear(GL_COLOR_BUFFER_BIT); // Limpiar la pantalla

  // Configuración del color de las barras
  glColor3f(1.0f, 0.0f, 0.0f); // Color azul para las barras

  // float barWidth = 10.0f; // Ancho de cada barra
  // float gap = 5.0f;       // Espacio entre las barras
  //
  // for (size_t i = 0; i < values.size(); ++i) {
  //   float x = axisOffset + i * (barWidth + gap); // Posición X de la barra
  //   float y = values[i]; // Altura de la barra basada en el valor del vector
  //
  //   glBegin(GL_QUADS);                    // Dibujar un cuadrilátero (barra)
  //   glVertex2f(x, axisOffset);            // Vértice inferior izquierdo
  //   glVertex2f(x + barWidth, axisOffset); // Vértice inferior derecho
  //   glVertex2f(x + barWidth, axisOffset + y); // Vértice superior derecho
  //   glVertex2f(x, axisOffset + y);            // Vértice superior izquierdo
  //   glEnd();
  //
  //   // Dibujar el índice debajo de la barra
  //   drawText(x + barWidth / 14, axisOffset - 5, std::to_string(i));
  // }
  for (size_t i = 0; i < values.size(); ++i) {
    float x = axisOffset + i * 10;       // Posición X del punto (índice)
    float y = axisOffset + valuesErr[i]; // Posición Y del punto (valor)

    glPointSize(5.0); // Tamaño del punto
    glBegin(GL_POINTS);
    glVertex2f(x, y); // Dibujar el punto
    glEnd();

    // Dibujar el índice debajo del punto
    drawText(x - 2, axisOffset - 5, std::to_string(i));
  }
  glColor3f(0.0f, 0.0f, 1.0f); // Color azul para las barras
  for (size_t i = 0; i < values.size(); ++i) {
    float x = axisOffset + i * 10;    // Posición X del punto (índice)
    float y = axisOffset + values[i]; // Posición Y del punto (valor)

    glPointSize(5.0); // Tamaño del punto
    glBegin(GL_POINTS);
    glVertex2f(x, y); // Dibujar el punto
    glEnd();

    // Dibujar el índice debajo del punto
    drawText(x - 2, axisOffset - 5, std::to_string(i));
  }

  // Dibujar las etiquetas del eje Y
  for (int i = 0; i <= 100; i += 10) {
    drawText(axisOffset - 10, axisOffset + i, std::to_string(i));
  }

  // Dibujar los ejes de coordenadas
  glColor3f(0.0f, 0.0f, 0.0f); // Color negro para los ejes
  glLineWidth(2.0f);           // Grosor de las líneas de los ejes

  glBegin(GL_LINES);
  // Eje X
  glVertex2f(axisOffset, axisOffset);
  glVertex2f(1000.0f + axisOffset, axisOffset);

  // Eje Y
  glVertex2f(axisOffset, axisOffset);
  glVertex2f(axisOffset, 100.0f + axisOffset);
  glEnd();

  glFlush(); // Forzar la ejecución de comandos GL
}

// Función para manejar el redimensionamiento de la ventana
void reshape(GLsizei width, GLsizei height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-axisOffset, 1050 + axisOffset, -axisOffset, 110 + axisOffset);
  windowWidth = width;
  windowHeight = height;
}

int main(int argc, char **argv) {
  // Inicializar GLUT
  string nombre01 = "./error01.csv";
  storeValue(nombre01, 100);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Grafica de Barras con Ejes de Coordenadas");

  // Inicializar configuración de OpenGL
  initGL();

  // Registrar funciones de retrollamada
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  // Iniciar el bucle de eventos de GLUT
  glutMainLoop();
  return 0;
}
