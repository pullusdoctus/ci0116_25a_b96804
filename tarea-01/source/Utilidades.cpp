#include "Utilidades.hpp"

void Utilidades::intercambiar(uint32_t* A, uint32_t i, uint32_t j) const {
  uint32_t temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

// Función para generar números aleatorios uint32_t
void Utilidades::generarArreglo(uint32_t* A, uint32_t n) {
  // Configuración del generador de números aleatorios
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dist(1, UINT32_MAX - 1);

  // Llenar el arreglo con números aleatorios
  for (uint32_t i = 0; i < n; ++i) {
    A[i] = dist(gen);
  }
}

// Función para copiar un arreglo
void Utilidades::copiarArreglo(const uint32_t* A, uint32_t* B, uint32_t n) {
  for (uint32_t i = 0; i < n; ++i) {
    B[i] = A[i];
  }
}
// Función para ordenar con el método seleccionado y medir el tiempo
double Utilidades::ordenar(const Ordenador& ordenador, uint32_t* A, uint32_t n, int algoritmo) {
  // Iniciar cronómetro
  auto inicio = std::chrono::high_resolution_clock::now();
  // Aplicar el método de ordenamiento seleccionado
  switch (algoritmo) {
    case 1:
        ordenador.ordenamientoPorSeleccion(A, n);
        break;
    case 2:
        ordenador.ordenamientoPorInserccion(A, n);
        break;
    case 3:
        ordenador.ordenamientoPorMezcla(A, n);
        break;
    case 4:
        ordenador.ordenamientoPorMonticulos(A, n);
        break;
    case 5:
        ordenador.ordenamientoRapido(A, n);
        break;
    case 6:
        ordenador.ordenamientoPorResiduos(A, n);
        break;
    default:
        std::cerr << "Método no válido" << std::endl;
        return -1.0;
  }
  // Detener cronómetro
  auto fin = std::chrono::high_resolution_clock::now();
  // Calcular duración en segundos
  std::chrono::duration<double> duracion = fin - inicio;
  return duracion.count();
}

// Función para mostrar el nombre del método seleccionado
std::string Utilidades::nombreAlgoritmo(int algoritmo) {
  switch (algoritmo) {
    case 1: return "Selección";
    case 2: return "Inserción";
    case 3: return "Mezcla";
    case 4: return "Montículos";
    case 5: return "Rápido";
    case 6: return "Residuos";
    default: return "Desconocido";
  }
}
