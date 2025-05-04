#pragma once

#include <cstdint>
/**
 * @brief Clase que implementa un montículo máximo para el algoritmo de ordenamiento por montículos.
 */
class Heap {
  private:
    uint32_t heapSize;  ///< Tamaño actual del montículo.

  public:
    /**
     * @brief Constructor que construye un montículo máximo a partir de un arreglo.
     *
     * @param A Arreglo de elementos a convertir en montículo.
     * @param n Tamaño del arreglo.
     */
    Heap(uint32_t* A, uint32_t n);

    /**
     * @brief Obtiene el índice del padre de un nodo.
     *
     * @param i Índice del nodo hijo.
     * @return uint32_t Índice del nodo padre.
     */
    uint32_t findParent(uint32_t i);
    /**
     * @brief Obtiene el índice del hijo izquierdo de un nodo.
     *
     * @param i Índice del nodo padre.
     * @return uint32_t Índice del hijo izquierdo.
     */
    uint32_t findLeftChild(uint32_t i);

    /**
     * @brief Obtiene el índice del hijo derecho de un nodo.
     *
     * @param i Índice del nodo padre.
     * @return uint32_t Índice del hijo derecho.
     */
    uint32_t findRightChild(uint32_t i);

    /**
     * @brief Mantiene la propiedad de montículo máximo en un subárbol.
     *
     * @param A Arreglo que representa el montículo.
     * @param i Índice del nodo raíz del subárbol.
     */
    void maxHeapify(uint32_t* A, uint32_t i);
    /**
     * @brief Reduce el tamaño del montículo en uno.
     */
    void decreaseHeapSize();
};
