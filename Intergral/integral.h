/**
 * @file integral.h
 * @brief Deklaracja klasy PiCalculator do obliczania wartoœci liczby Pi metod¹ numerycznej ca³ki.
 *
 * @details
 * Biblioteka ta pozwala na obliczenie wartoœci liczby Pi za pomoc¹ metody numerycznej
 * ca³ki prostok¹tów. Obliczenia mog¹ byæ równolegle wykonywane z u¿yciem wielow¹tkowoœci,
 * co przyspiesza czas wykonywania w przypadku du¿ych zakresów obliczeñ.
 *
 * ## Kluczowe cechy:
 * - Obs³uga podzia³u pracy na wiele w¹tków.
 * - Pomiar czasu wykonywania obliczeñ.
 * - Wysoka precyzja dziêki du¿ej liczbie przedzia³ów.
 *
 * ## Wykorzystywane biblioteki:
 * - `<vector>`: Przechowuje wyniki czêœciowych obliczeñ dla poszczególnych w¹tków.
 * - `<thread>`: Pozwala na uruchamianie w¹tków do równoleg³ego przetwarzania segmentów danych.
 *
 * ## Przyk³ad u¿ycia:
 * @code
 * #include "integral.h"
 *
 * int main() {
 *     PiCalculator calculator(1000000, 4); // 1 000 000 przedzia³ów, 4 w¹tki
 *     double pi = calculator.calculate();
 *     double time = calculator.getExecutionTime();
 *
 *     std::cout << "Pi = " << pi << std::endl;
 *     std::cout << "Czas wykonania: " << time << " sekund" << std::endl;
 *     return 0;
 * }
 * @endcode
 *
 * @note Liczba przedzia³ów i w¹tków wp³ywa na precyzjê i czas obliczeñ.
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
