#pragma once

/*
Credits
Author: Prof. Arturo Camacho, Universidad de Costa Rica
 
Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#include <cstdint>
#include <string>


/**
 * @brief Clase que implementa diversos algoritmos de ordenamiento.
 */
class Ordenador {
  private:
  // Métodos auxiliares para Merge Sort
  /**
   * @brief Implementa el algoritmo de ordenamiento por mezcla de forma recursiva.
   *
   * @param A Arreglo a ordenar.
   * @param p Índice inicial del subarreglo.
   * @param r Índice final del subarreglo.
   */
  void mergeSort(uint32_t* A, uint32_t p, uint32_t r) const;
  /**
   * @brief Combina dos subarreglos ordenados en uno solo.
   *
   * @param A Arreglo principal.
   * @param p Índice inicial del primer subarreglo.
   * @param q Índice final del primer subarreglo.
   * @param r Índice final del segundo subarreglo.
   */
  void merge(uint32_t* A, uint32_t p, uint32_t q, uint32_t r) const;
  // Métodos auxiliares para Quicksort
  /**
   * @brief Ordena un subarreglo usando el algoritmo rápido (quicksort).
   *
   * @param A Arreglo a ordenar.
   * @param p Índice inicial del subarreglo.
   * @param r Índice final del subarreglo.
   */
  void quicksort(uint32_t* A, int32_t p, int32_t r) const;
  /**
   * @brief Particiona el arreglo alrededor de un pivote.
   *
   * @param A Arreglo a particionar.
   * @param p Índice inicial del subarreglo.
   * @param r Índice final del subarreglo (pivote).
   * @return uint32_t Índice del pivote después de la partición.
   */
  uint32_t partition(uint32_t* A, int32_t p, int32_t r) const;
  // Métodos auxiliares para Radix Sort
  /**
   * @brief Ordena un arreglo usando counting sort para un dígito específico.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   * @param r Número de bits por dígito.
   * @param exp Dígito actual a considerar.
   */
  void countingSort(uint32_t* A, uint32_t n, uint32_t r, uint32_t exp) const;
  public:
  Ordenador() = default;
  ~Ordenador() = default;

  /**
   * @brief Ordena un arreglo usando el algoritmo de Selection Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorSeleccion(uint32_t *A, uint32_t n) const;
  /**
   * @brief Ordena un arreglo usando el algoritmo de Insertion Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorInserccion(uint32_t *A, uint32_t n) const;
  /**
   * @brief Ordena un arreglo usando el algoritmo de Merge Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMezcla(uint32_t *A, uint32_t n) const;
  /**
   * @brief Ordena un arreglo usando el algoritmo de Heap Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMonticulos(uint32_t *A, uint32_t n) const;
  /**
   * @brief Ordena un arreglo usando el algoritmo de Quicksort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoRapido(uint32_t *A, uint32_t n) const;
  /**
   * @brief Ordena un arreglo usando el algoritmo de Radix Sort.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorResiduos(uint32_t *A, uint32_t n) const;

  /**
   * @brief Retorna un std::string con los datos de la tarea.
   * 
   * Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
   * 
   * @return std::string Una cadena de texto con los datos de la tarea.
   */
  constexpr const char* imprimirDatosDeTarea() const {
    return "Carné: B96804, Nombre: Jeremy Rojas, Tarea 1";
  }
};
