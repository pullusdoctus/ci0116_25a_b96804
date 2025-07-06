# Tarea Programada 3

## Descripción

Esta última tarea programada resuelve un problema de logística utilizando algoritmos de grafos. A partir de los datos en un archivo CSV, se construye un grafo entre ciudades.

## Funcionalidades

1. Determinar la mejor ciudad para ubicar equipo y minimizar tiempos de distribución.
2. Encontrar la mejor ciudad para enviar ayuda a una ciudad dada.
3. Identificar el par de ciudades más distantes y mostrar su ruta y tiempo de viaje.
4. Identificar el par de ciudades diferentes más cercanas y mostrar su ruta y tiempo de viaje.
5. Listar todas las ciudades ordenadas por su tiempo promedio de viaje hacia las demás.

## Compilación y ejecución

Para su facilidad, se provee un archivo Makefile con los siguientes comandos:

```bash
# compila el programa en caso de ser necesario
make

# ejecuta el programa
make run

# elimina archivos binarios generados durante la compilación
make clean
```

Además de ejecutar el programa con `make run`, también se puede ejecutar directamente desde la terminal. El binario ejecutable se encuentra en el directorio 'bin', generado durante la compilación. Desde `ci0116-25a-b96804/tarea-03`, el comando de ejecución es `bin/executable`.

## Resultados

Para un reporte detallado de los resultados, ver el directorio [doc](./doc/).
