/**
 * @file integral.h
 * @brief Deklaracja klasy PiCalculator do obliczania warto�ci liczby Pi metod� numerycznej ca�ki.
 *
 * @details
 * Biblioteka ta pozwala na obliczenie warto�ci liczby Pi za pomoc� metody numerycznej
 * ca�ki prostok�t�w. Obliczenia mog� by� r�wnolegle wykonywane z u�yciem wielow�tkowo�ci,
 * co przyspiesza czas wykonywania w przypadku du�ych zakres�w oblicze�.
 *
 * ## Kluczowe cechy:
 * - Obs�uga podzia�u pracy na wiele w�tk�w.
 * - Pomiar czasu wykonywania oblicze�.
 * - Wysoka precyzja dzi�ki du�ej liczbie przedzia��w.
 *
 * ## Wykorzystywane biblioteki:
 * - `<vector>`: Przechowuje wyniki cz�ciowych oblicze� dla poszczeg�lnych w�tk�w.
 * - `<thread>`: Pozwala na uruchamianie w�tk�w do r�wnoleg�ego przetwarzania segment�w danych.
 *
 * ## Przyk�ad u�ycia:
 * @code
 * #include "integral.h"
 *
 * int main() {
 *     PiCalculator calculator(1000000, 4); // 1 000 000 przedzia��w, 4 w�tki
 *     double pi = calculator.calculate();
 *     double time = calculator.getExecutionTime();
 *
 *     std::cout << "Pi = " << pi << std::endl;
 *     std::cout << "Czas wykonania: " << time << " sekund" << std::endl;
 *     return 0;
 * }
 * @endcode
 *
 * @note Liczba przedzia��w i w�tk�w wp�ywa na precyzj� i czas oblicze�.
 */

#pragma once
#include <vector>
#include <thread>

 /**
  * @class PiCalculator
  * @brief A class to calculate the value of Pi using numerical integration.
  */
class PiCalculator {
public:
    /**
     * @brief Constructs a PiCalculator with the specified number of intervals and threads.
     * @param intervals The number of intervals for numerical integration.
     * @param threads The number of threads to use for parallel computation.
     */
    PiCalculator(long long intervals, int threads);

    /**
     * @brief Calculates the value of Pi using numerical integration.
     * @return The computed value of Pi.
     */
    double calculate();

    /**
     * @brief Retrieves the execution time of the last calculation.
     * @return The execution time in seconds.
     */
    double getExecutionTime() const;

private:
    /**
     * @brief Computes the contribution to Pi from a segment of the interval.
     * @param start The start index of the interval segment.
     * @param end The end index of the interval segment.
     * @return The computed partial result for the segment.
     */
    double computeSegment(long long start, long long end);

    /**
     * @brief Worker function for parallel computation of Pi segments.
     * @param calculator A pointer to the PiCalculator instance.
     * @param start The start index of the interval segment.
     * @param end The end index of the interval segment.
     * @param result Reference to a double where the result will be stored.
     */
    static void worker(PiCalculator* calculator, long long start, long long end, double& result);

    long long intervals_; ///< The total number of intervals for integration.
    int threads_; ///< The number of threads for parallel computation.
    double executionTime_; ///< The execution time of the last calculation.
    std::vector<double> results_; ///< Storage for partial results from each thread.
};
