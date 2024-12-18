/**
 * @file integral.cpp
 * @brief Implementacja klasy PiCalculator do obliczania wartości liczby Pi metodą numerycznej całki.
 *
 * @details
 * Implementacja umożliwia obliczenie przybliżonej wartości liczby Pi metodą numerycznego całkowania
 * prostokątów. Obliczenia są równolegle wykonywane przez wiele wątków, co pozwala na przyspieszenie
 * procesu obliczeniowego w przypadku dużej liczby przedziałów.
 *
 * ## Wykorzystywane biblioteki:
 * - `<iostream>`: Używana do wyświetlania wyników na standardowe wyjście (np. w przykładach testowych).
 * - `<cmath>`: Używana do wykonywania operacji matematycznych, takich jak obliczanie wartości funkcji.
 * - `<chrono>`: Używana do pomiaru czasu wykonania obliczeń, aby zmierzyć wydajność algorytmu.
 * - `<mutex>`: Choć w tym przypadku nie jest używana w kodzie, może być przydatna w przyszłości do
 *   synchronizacji dostępu do wspólnych zasobów, gdyby była taka potrzeba.
 */

#include "integral.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <mutex>

 /**
  * @brief Konstruktor klasy PiCalculator.
  * @param intervals Liczba przedziałów dla całkowania numerycznego.
  * @param threads Liczba wątków do wykorzystania w obliczeniach.
  */
PiCalculator::PiCalculator(long long intervals, int threads)
    : intervals_(intervals), threads_(threads), executionTime_(0) {
}

/**
 * @brief Oblicza wartość liczby Pi za pomocą numerycznej całki prostokątów.
 *
 * @details
 * Obliczenia są podzielone na segmenty, które są przetwarzane równolegle przez wiele wątków.
 * Następnie wyniki częściowe są sumowane, a czas wykonywania jest mierzony.
 *
 * @return Przybliżona wartość liczby Pi.
 */
double PiCalculator::calculate() {
    results_.resize(threads_);
    auto start_time = std::chrono::high_resolution_clock::now();

    // Tworzenie i uruchamianie wątków.
    std::vector<std::thread> workers;
    long long segment_size = intervals_ / threads_;
    for (int i = 0; i < threads_; ++i) {
        long long start = i * segment_size;
        long long end = (i == threads_ - 1) ? intervals_ : (i + 1) * segment_size;
        workers.emplace_back(worker, this, start, end, std::ref(results_[i]));
    }

    // Oczekiwanie na zakończenie pracy wątków.
    for (auto& thread : workers) {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    executionTime_ = elapsed.count();

    // Sumowanie wyników częściowych.
    double total_sum = 0.0;
    for (double partial : results_) {
        total_sum += partial;
    }

    return total_sum * 4.0; // Mnożenie przez 4 zgodnie z wzorem na całkę liczby Pi.
}

/**
 * @brief Zwraca czas wykonania ostatniego obliczenia.
 * @return Czas wykonania w sekundach.
 */
double PiCalculator::getExecutionTime() const {
    return executionTime_;
}

/**
 * @brief Oblicza wkład w wartość liczby Pi z danego segmentu przedziału.
 *
 * @param start Początek segmentu (indeks).
 * @param end Koniec segmentu (indeks).
 * @return Wynik częściowy dla podanego segmentu.
 */
double PiCalculator::computeSegment(long long start, long long end) {
    double sum = 0.0;
    double step = 1.0 / intervals_;
    for (long long i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        sum += 1.0 / (1.0 + x * x);
    }
    return sum * step; // Skalowanie wyniku na podstawie długości kroku.
}

/**
 * @brief Funkcja robocza używana przez wątki do obliczania segmentów całki.
 *
 * @param calculator Wskaźnik na instancję klasy PiCalculator.
 * @param start Początek segmentu (indeks).
 * @param end Koniec segmentu (indeks).
 * @param result Referencja na zmienną, w której zostanie zapisany wynik częściowy.
 */
void PiCalculator::worker(PiCalculator* calculator, long long start, long long end, double& result) {
    result = calculator->computeSegment(start, end);
}
