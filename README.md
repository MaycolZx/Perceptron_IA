# PERCEPTRON-MNIST

## Integrantes:
- MAYCOL ALEXANDER CANAVERI TACO
- JAIME MATEO GUTIERREZ MUÑOZ
- JHON BERLY TAYPE ALCCACCAHUA 
- LEONARDO ALONSO RAMIREZ QUIROZ

## Windows

## MacOS

## Linux

Primero instalar algunas dependencias segun la distribucion que uses de Linux.

### Ubuntu / Debian

```bash
sudo apt-get update
sudo apt-get install build-essential cmake xorg-dev libglu1-mesa-dev
sudo apt-get install libgl-dev libglfw3-dev
```

### Arch/Linux

```bash
sudo pacman -Syu
sudo pacman -S glfw
```

Para compilar el proyecto usar el siguiente comando:

```bash
make
```

Ahora dirijase al directorio `/bin` y ejecute el programa como `./mi_programa`
Por ahora el codigo solo se ha probado sobre Linux.

![Algoritmo_Genetico](./pictures/FirstAlgoritmoGen.png)

## Problema del viajero

[![Algoritmo_Genetico_Problema_del_Viajero](./pictures/AlgoritmoGen.png)](https://colab.research.google.com/drive/1vmpZAA0UFMOu1crGBipf6v4-MEBGyev-?usp=sharing)

<p style="text-align:center; font-size: 18px;font-weight:bold">Haz click ▲ Haz click</p>

### Si necesita installar GLFW y GlAD manualmente 

1. Primero clonamos el repositorio oficial de GLFW `https://github.com/glfw/glfw`

2. Seguimos los siguintes pasos, esto deberia de instalar GLFW en nuestro sistema

```bash
cd glfw
mkdir build
cd build
cmake ..
make
sudo make install
```
3. Ahora generando el archivo al libreria `libglad.a`

```bash
gcc -c glad.c -o glad.o
ar rcs libglad.a glad.o
```

Nota: El repositorio ya tiene las librerias necesarias para ejecutar el programa por lo que necesita generar la libreria de `libglad.a`
