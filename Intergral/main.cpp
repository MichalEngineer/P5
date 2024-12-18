/**
 * @file main.cpp
 * @brief G³ówny plik programu do obliczania liczby Pi za pomoc¹ numerycznej ca³ki.
 *
 * @details
 * Program oferuje dwa tryby dzia³ania:
 * - Uruchomienie testów automatycznych dla ró¿nych liczby podzia³ów i w¹tków.
 * - Rêczne obliczanie przybli¿onej wartoœci liczby Pi dla podanej liczby podzia³ów i w¹tków.
 *
 * Wyniki testów s¹ zapisywane w pliku CSV, a u¿ytkownik mo¿e œledziæ czas obliczeñ oraz przybli¿on¹ wartoœæ liczby Pi.
 *
 * ## Wykorzystywane biblioteki:
 * - `<iostream>`: Standardowa biblioteka wejœcia/wyjœcia, u¿ywana do komunikacji z u¿ytkownikiem (wypisywanie wyników i pobieranie danych).
 * - `<iomanip>`: Biblioteka do manipulacji formatem wyjœcia, u¿ywana w celu ustawienia precyzyjnoœci wyœwietlanej wartoœci liczby Pi.
 * - `<fstream>`: Biblioteka umo¿liwiaj¹ca zapis wyników do pliku CSV.
 * - `"integral.h"`: Nag³ówek klasy `PiCalculator` zawieraj¹cej metody obliczania liczby Pi.
 */

#include <iostream>   ///< Biblioteka do obs³ugi wejœcia/wyjœcia, w tym wypisywania na ekranie.
#include <iomanip>    ///< Biblioteka do manipulacji formatem wyjœcia (np. ustawianie precyzji liczby zmiennoprzecinkowej).
#include <fstream>    ///< Biblioteka do obs³ugi plików, w tym zapisywania wyników do pliku CSV.
#include "integral.h" ///< Nag³ówek klasy PiCalculator, zawieraj¹cy deklaracje metod obliczaj¹cych liczbê Pi.

 /**
  * @brief Funkcja do uruchamiania testów automatycznych obliczeñ liczby Pi dla ró¿nych liczby podzia³ów i w¹tków.
  *
  * @details
  * Funkcja ta przeprowadza testy automatyczne, obliczaj¹c wartoœæ liczby Pi dla ró¿nych liczby podzia³ów
  * i w¹tków. Wyniki s¹ zapisywane w pliku CSV oraz wypisywane na ekranie.
  */
void runTests() {
    // Lista liczby podzia³ów (w ró¿nych skalach) u¿ywanych w testach.
    const std::vector<long long> intervalsList = { 100000000, 1000000000, 3000000000 };

    // Maksymalna liczba w¹tków, które bêd¹ testowane w ramach testów automatycznych.
    const int maxThreads = 50;

    // Otwarcie pliku wynikowego, do którego bêd¹ zapisywane rezultaty testów w formacie CSV.
    std::ofstream resultsFile("results.csv");

    // Zapisanie nag³ówka do pliku CSV (nag³ówki dla ka¿dego typu danych, który bêdzie zapisywany).
    resultsFile << "Intervals,Threads,Time (s),Pi Approximation\n";

    // Pêtla przechodz¹ca przez ka¿dy przypadek liczby podzia³ów (z listy intervalsList).
    for (auto intervals : intervalsList) {
        // Pêtla przechodz¹ca przez liczbê w¹tków, które bêd¹ testowane.
        for (int threads = 1; threads <= maxThreads; ++threads) {
            // Tworzenie obiektu kalkulatora, który obliczy wartoœæ Pi dla aktualnej liczby podzia³ów i w¹tków.
            PiCalculator calculator(intervals, threads);

            // Obliczanie przybli¿onej wartoœci liczby Pi oraz czasu potrzebnego na obliczenie.
            double pi = calculator.calculate();
            double time = calculator.getExecutionTime();

            // Zapisanie wyników obliczeñ do pliku CSV (liczba podzia³ów, liczba w¹tków, czas wykonania, przybli¿ona wartoœæ Pi).
            resultsFile << intervals << "," << threads << "," << time << "," << pi << "\n";

            // Wypisanie wyników na ekranie dla u¿ytkownika.
            std::cout << "Intervals: " << intervals
                << ", Threads: " << threads
                << ", Time: " << time
                << " s, Pi: " << pi << "\n";
        }
    }

    // Zamkniêcie pliku po zakoñczeniu zapisywania wyników.
    resultsFile.close();

    // Wypisanie komunikatu, ¿e testy zosta³y zakoñczone, a wyniki zosta³y zapisane w pliku.
    std::cout << "Testy zakoñczone. Wyniki zapisano w pliku 'results.csv'.\n";
}

/**
 * @brief Funkcja g³ówna programu, która umo¿liwia wybór trybu dzia³ania programu.
 *
 * @details
 * Program dzia³a w dwóch trybach:
 * - Uruchomienie testów automatycznych.
 * - Rêczne obliczanie liczby Pi dla podanych przez u¿ytkownika parametrów.
 *
 * U¿ytkownik wybiera tryb dzia³ania, a nastêpnie program realizuje odpowiedni¹ funkcjonalnoœæ.
 * Wyniki obliczeñ s¹ wyœwietlane na ekranie i zapisywane w pliku CSV w przypadku testów automatycznych.
 *
 * @return 0 jeœli program zakoñczy³ siê poprawnie.
 */
int main() {
    // Zmienna przechowuj¹ca wybór u¿ytkownika.
    int option;

    // Wyœwietlenie komunikatu z proœb¹ o wybór jednej z dwóch opcji.
    std::cout << "Wybierz opcje:\n";
    std::cout << "1 - Uruchom testy automatyczne i zapisz wyniki\n";
    std::cout << "2 - Oblicz Pi dla podanej liczby podzia³ów i w¹tków\n";

    // Wczytanie wyboru u¿ytkownika.
    std::cin >> option;

    // Jeœli u¿ytkownik wybierze opcjê 1, uruchomimy testy automatyczne.
    if (option == 1) {
        runTests();  ///< Uruchomienie funkcji przeprowadzaj¹cej testy automatyczne.
    }
    // Jeœli u¿ytkownik wybierze opcjê 2, zapytamy go o parametry i obliczymy liczbê Pi.
    else if (option == 2) {
        long long intervals;  ///< Zmienna do przechowywania liczby przedzia³ów.
        int threads;          ///< Zmienna do przechowywania liczby w¹tków.

        // Poproszenie u¿ytkownika o podanie liczby przedzia³ów do obliczeñ.
        std::cout << "Podaj liczbe podzialow przedzialu (np. 100000000): ";
        std::cin >> intervals;

        // Poproszenie u¿ytkownika o podanie liczby w¹tków do obliczeñ.
        std::cout << "Podaj liczbe watkow (np. 4): ";
        std::cin >> threads;

        // Utworzenie obiektu kalkulatora z odpowiednimi parametrami.
        PiCalculator calculator(intervals, threads);

        // Obliczenie liczby Pi i czasu obliczeñ.
        double pi = calculator.calculate();
        double executionTime = calculator.getExecutionTime();

        // Wyœwietlenie wyników na ekranie z ustawion¹ precyzj¹ na 15 miejsc po przecinku.
        std::cout << std::fixed << std::setprecision(15);
        std::cout << "Przyblizona wartosc liczby Pi: " << pi << "\n";
        std::cout << "Czas obliczen: " << executionTime << " sekund\n";
    }
    // Jeœli u¿ytkownik poda niepoprawn¹ opcjê, wyœwietlamy komunikat o b³êdzie.
    else {
        std::cout << "Niepoprawna opcja. Koniec programu.\n";
    }

    // Zwrócenie wartoœci 0, co oznacza zakoñczenie programu bez b³êdów.
    return 0;
}
