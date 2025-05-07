/**
 * RA 2025: compile with g++ string.cpp -o string -fopenmp
 */

#include <iostream>
#include <string>
#include <chrono>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std::chrono;
using namespace std;

#define STRING_LENGTH (1024UL * 1024UL * 10UL)  // 10MB

// Text init function in C++
void initText(string &s) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    srand(time(0));  // Seed the random generator
    for (int i = 0; i < STRING_LENGTH; i++) {
        s[i] = alpha[rand() % (sizeof(alpha) - 1)];
    }
}

// Iterative search
bool text_suche_iter(string& text_to_search, string& random_string) {
    for (int i = 0; i <= random_string.size() - text_to_search.size(); ++i) {
        if (random_string[i] == text_to_search[0]) {
            for (int j = 1; j < text_to_search.size(); ++j) {
                if (text_to_search[j] != random_string[i + j]) {
                    break;
                } else if (j == text_to_search.size() - 1 && text_to_search[j] == random_string[i + j]) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Parallel search with OpenMP
bool text_suche_rec(string& text_to_search, string& random_string) {
    bool found = false;

    #pragma omp parallel for shared(found)
    for (int i = 0; i <= random_string.size() - text_to_search.size(); ++i) {
        if (found) continue;

        if (random_string[i] == text_to_search[0]) {
            bool match = true;
            for (int j = 1; j < text_to_search.size(); ++j) {
                if (text_to_search[j] != random_string[i + j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                #pragma omp critical
                found = true;
            }
        }
    }

    return found;
}


int main() {
    string random_text(STRING_LENGTH, ' ');
    initText(random_text);

    std::cout << "What string do u want to find: " << std::endl;
    std::string to_search;
    std::cin >> to_search;

    // Time iterative version
    auto start_iter = high_resolution_clock::now();
    bool found_iter = text_suche_iter(to_search, random_text);
    auto stop_iter = high_resolution_clock::now();

    // Time parallel version
    auto start_rec = high_resolution_clock::now();
    bool found_rec = text_suche_rec(to_search, random_text);
    auto stop_rec = high_resolution_clock::now();

    // Output results
    if (found_iter) {
        std::cout << "The text was found !! (iterative)" << endl;
    } else {
        std::cout << "The text was not found (iterative)" << endl;
    }

    if (found_rec) {
        std::cout << "The text was found !! (parallel)" << endl;
    } else {
        std::cout << "The text was not found (parallel)" << endl;
    }

    // Output durations
    auto duration_iter = duration_cast<microseconds>(stop_iter - start_iter);
    auto duration_rec  = duration_cast<microseconds>(stop_rec  - start_rec);

    std::cout << "Iterative version time in microseconds: " << duration_iter.count() << endl;
    std::cout << "Parallel version time in microseconds: "  << duration_rec.count()  << endl;
}

