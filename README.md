# Simulador de Algoritmos de Planificación de Disco

## Descripción

Este proyecto implementa y compara tres algoritmos clásicos de planificación de disco (Disk Scheduling) utilizados en sistemas operativos para optimizar el movimiento del cabezal del disco duro:

- **FCFS** (First-Come, First-Served)
- **SCAN** (Algoritmo del Ascensor)
- **C-SCAN** (Circular SCAN)

El programa genera solicitudes aleatorias de acceso a cilindros, ejecuta los tres algoritmos y visualiza los resultados mediante gráficos generados con Gnuplot.

## Características

- Simulación de **5000 cilindros** en el disco
- Generación de **1000 solicitudes aleatorias** de acceso
- Posición inicial del cabezal configurable por el usuario
- Cálculo automático de la distancia total recorrida por cada algoritmo
- Visualización gráfica comparativa de:
  - Trayectoria del cabezal para cada algoritmo
  - Rendimiento (movimiento total) en gráfico de barras

## Algoritmos Implementados

### 1. FCFS (First-Come, First-Served)
Atiende las solicitudes en el orden en que llegan, sin optimización. Es el más simple pero generalmente el menos eficiente.

### 2. SCAN (Algoritmo del Ascensor)
El cabezal se mueve en una dirección atendiendo solicitudes hasta llegar al final del disco, luego invierte la dirección y atiende las solicitudes restantes.

### 3. C-SCAN (Circular SCAN)
Similar a SCAN, pero cuando llega al extremo, regresa directamente al inicio y continúa en la misma dirección, tratando el disco como circular.

## Requisitos

- **Compilador C++** (compatible con C++11 o superior)
  - g++ (MinGW en Windows)
  - Visual Studio
  - Clang
- **Gnuplot** (para la generación de gráficos)

### Instalación de Gnuplot en Windows

1. Descargar desde [gnuplot.info](http://www.gnuplot.info/)
2. Instalar y asegurarse de que esté en el PATH del sistema

## Compilación

```bash
g++ assignment3.cpp -o disk_scheduler
```

O con optimización:

```bash
g++ -O2 assignment3.cpp -o disk_scheduler
```

## Uso

1. Ejecutar el programa:
```bash
./disk_scheduler
```

2. Ingresar la posición inicial del cabezal cuando se solicite (entre 0 y 4999)

3. El programa generará automáticamente:
   - 1000 solicitudes aleatorias
   - Archivos de datos (.dat)
   - Dos ventanas de Gnuplot con los gráficos

## Archivos Generados

- **fcfs.dat** - Datos de la trayectoria del algoritmo FCFS
- **scan.dat** - Datos de la trayectoria del algoritmo SCAN
- **cscan.dat** - Datos de la trayectoria del algoritmo C-SCAN
- **performance.dat** - Datos comparativos de rendimiento

## Scripts de Gnuplot

### plot_paths.gp
Genera un gráfico de líneas mostrando la trayectoria del cabezal para los tres algoritmos simultáneamente.

### plot_bars.gp
Genera un gráfico de barras comparando el movimiento total del cabezal para cada algoritmo.

## Ejemplo de Salida

```
Ingrese la posición inicial del cabezal (0 - 4999): 2500

Gráficos generados exitosamente.
=== DISK SCHEDULING SIMULATOR ===
Initial head position: 2500
Generated requests: 1000

---- RESULTS ----
FCFS    total movement: 2456789 cylinders
SCAN    total movement: 7499 cylinders
C-SCAN  total movement: 9999 cylinders
```

## Estructura del Código

```cpp
// Constantes principales
CYLINDERS = 5000  // Número total de cilindros
REQUESTS = 1000   // Número de solicitudes a generar

// Funciones principales
run_fcfs()   - Implementa el algoritmo FCFS
run_scan()   - Implementa el algoritmo SCAN
run_cscan()  - Implementa el algoritmo C-SCAN

// Utilidades
write_path_file()   - Guarda trayectoria en archivo
write_bars_file()   - Guarda datos de rendimiento
generate_graphs()   - Ejecuta Gnuplot
```

## Análisis de Rendimiento

En general:
- **FCFS** suele tener el peor rendimiento (mayor movimiento)
- **SCAN** ofrece un buen balance entre eficiencia y equidad
- **C-SCAN** proporciona tiempos de espera más uniformes

Los resultados específicos dependen de la posición inicial del cabezal y la distribución de las solicitudes.

## Autor

Joshua Mendez

## Licencia

Este proyecto es de código abierto para fines educativos.