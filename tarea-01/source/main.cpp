#include "./include/Ordenador.hpp"
#include "./include/Utilidades.hpp"

int main() {
  // Instanciar objetos
  Ordenador ordenador;
  Utilidades utilidades;
  // Imprimir los datos de la tarea
  std::cout << "-------------------------------------------------------------" << std::endl;
  std::cout << ordenador.imprimirDatosDeTarea() << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
  // Preguntar al usuario qué algoritmo desea usar
  int algoritmo;
  std::cout << "Seleccione el algoritmo de ordenamiento:\n";
  std::cout << "1. Ordenamiento por Selección\n";
  std::cout << "2. Ordenamiento por Inserción\n";
  std::cout << "3. Ordenamiento por Mezcla\n";
  std::cout << "4. Ordenamiento por Montículos\n";
  std::cout << "5. Ordenamiento Rápido\n";
  std::cout << "6. Ordenamiento por Residuos\n";
  std::cout << "> ";
  std::cin >> algoritmo;
  // Verificar si el algoritmo seleccionado es válido
  if (algoritmo < 1 || algoritmo > 6) {
    std::cerr << "Error: Algoritmo de ordenamiento no válido." << std::endl;
    return 1;
  }
  std::cout << "\nAlgoritmo seleccionado: " << utilidades.nombreAlgoritmo(algoritmo) << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
  // Definir los tamaños de arreglos
  const uint32_t tamaños[] = {1000, 10000, 100000, 1000000};
  const int numTamaños = 4;
  const int repeticiones = 3;
  // Para cada tamaño de arreglo
  for (int i = 0; i < numTamaños; ++i) {
    uint32_t n = tamaños[i];
    std::cout << "\nProbando con arreglo de tamaño " << n << ":" << std::endl;
    // Crear los arreglos
    uint32_t* A = new uint32_t[n];
    uint32_t* B = new uint32_t[n];
    // Generar el arreglo de números aleatorios
    utilidades.generarArreglo(A, n);
    // Ordenar el arreglo tres veces y medir el tiempo
    for (int j = 0; j < repeticiones; ++j) {
      // Copiar el arreglo original para preservarlo
      utilidades.copiarArreglo(A, B, n);
      // Ordenar y medir tiempo
      double tiempo = utilidades.ordenar(ordenador, B, n, algoritmo);
      // Mostrar el tiempo
      std::cout << "Ejecución " << (j + 1) << ": " 
                << std::fixed << std::setprecision(6) 
                << tiempo << " segundos" << std::endl;
    }
    delete[] A;
    delete[] B;
  }
  std::cout << "\n-------------------------------------------------------------" << std::endl;
  std::cout << "Fin del programa" << std::endl;
  return 0;
}
