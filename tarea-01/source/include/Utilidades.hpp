#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#include "Ordenador.hpp"

/**
 * @brief Clase con utilidades para generar arreglos, medir tiempos y más.
 */
class Utilidades {
  public:
    /**
     * @brief Genera un arreglo con números aleatorios.
     *
     * @param A Arreglo a llenar.
     * @param n Tamaño del arreglo.
     */
    void generarArreglo(uint32_t* A, uint32_t n);
    /**
     * @brief Copia los elementos de un arreglo a otro.
     *
     * @param A Arreglo origen.
     * @param B Arreglo destino.
     * @param n Tamaño de los arreglos.
     */
    void copiarArreglo(const uint32_t* A, uint32_t* B, uint32_t n);
    /**
     * @brief Ejecuta un algoritmo de ordenamiento y mide su tiempo de ejecución.
     * 
     * @param ordenador Instancia de Ordenador con los algoritmos.
     * @param A Arreglo a ordenar.
     * @param N Tamaño del arreglo.
     * @param algoritmo Número del algoritmo a usar (1-6).
     * @return double Tiempo en segundos. Retorna -1.0 si el algoritmo es inválido.
     */
    double ordenar(const Ordenador& ordenador, uint32_t* A, uint32_t N, int algoritmo);
    /**
     * @brief Devuelve el nombre del algoritmo según su número.
     *
     * @param algoritmo Número del algoritmo (1-6).
     * @return std::string Nombre del algoritmo.
     */
    std::string nombreAlgoritmo(int algoritmo);
    /**
     * @brief Intercambia dos elementos en un arreglo.
     *
     * @param A Arreglo.
     * @param i Índice del primer elemento.
     * @param j Índice del segundo elemento.
     */
    void intercambiar(uint32_t* A, uint32_t i, uint32_t j) const;
};
