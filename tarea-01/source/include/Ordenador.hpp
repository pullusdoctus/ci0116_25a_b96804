#pragma once

/*
Credits
Author: Prof. Arturo Camacho, Universidad de Costa Rica
 
Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#include <cstdint>
#include <string>

class Ordenador {
  private:
  // Metodos auxiliares
  void intercambiar(uint32_t* A, uint32_t i, uint32_t j) const;
  void mergeSort(uint32_t* A, uint32_t p, uint32_t r) const;
  void merge(uint32_t* A, uint32_t p, uint32_t q, uint32_t r) const;
  public:
  Ordenador() = default;
  ~Ordenador() = default;
  /* Nota:
   - Si no planea implementar algunos de los métodos de ordenamiento, no los borre.
   - Simplemente déjelos con el cuerpo vacío para evitar errores de compilación, ya
     que se ejecutará el mismo main para todas las tareas.
   - Recuerde hacer uso de programación defensiva y documentar los métodos con formato Doxygen, por ejemplo.
   - No cambié la firma de los métodos de la clase Ordenador.
   - No lance excepciones para el manejo de errores.
     Ante un error, basta con que el método no modifique el arreglo original y que no cause la caída del programa.
  */ 

  void ordenamientoPorSeleccion(uint32_t *A, uint32_t n) const;
  void ordenamientoPorInserccion(uint32_t *A, uint32_t n) const;
  void ordenamientoPorMezcla(uint32_t *A, uint32_t n) const;
  void ordenamientoPorMonticulos(uint32_t *A, uint32_t n) const;
  void ordenamientoRapido(uint32_t *A, uint32_t n) const;
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
