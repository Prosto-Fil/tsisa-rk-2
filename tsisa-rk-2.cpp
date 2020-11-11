#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

const double min = -2.0;
const double max = 2.0;
const double probability_mutation = 0.2;

auto random(const double min, const double max) -> double {
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

auto f(const double x, const double y) -> double {
    return cos(x) * cos(y);
}

struct Chromosome {
    double x, y;
    double fit;
    Chromosome() : x(0), y(0), fit(0) {}
    Chromosome(double x_cord, double y_cord) : x(x_cord), y(y_cord), fit(f(x_cord, y_cord)) {}
};

auto comparison_operator(const Chromosome& left, const Chromosome& right) -> bool {
    return left.fit > right.fit;
};

void print_generation(const std::vector<Chromosome>& chrome, unsigned int it) {
    auto fit_mid = 0.0;
    for (const auto& ch : chrome) {
        fit_mid += ch.fit;
    }
    fit_mid = fit_mid / 6;
    std::cout << "N: " << std::setw(13) << std::left << it
        << "Fit_mid: " << std::setw(13) << std::left << fit_mid
        << "Fit_max: " << std::setw(13) << std::left << chrome[0].fit << std::endl;
    for (const auto& ch : chrome) {
        std::cout << "x: " << std::setw(13) << std::left << ch.x
            << "y: " << std::setw(13) << std::left << ch.y
            << "Fit: " << std::setw(13) << std::left << ch.fit << std::endl;
    }
    cout << endl;
}

void GeneticAlgorithm(const int N) {
    std::vector<Chromosome> generation;

    for (unsigned int i = 0; i < 6; i++) {
        generation.emplace_back(random(min, max), random(min, max));
    }

    std::sort(generation.begin(), generation.end(), comparison_operator);
    print_generation(generation, 0);
    for (unsigned int i = 1; i <= N; i++) {
        for (unsigned int j = 0; j < generation.size(); j++) {
            auto probability = random(0, 1);
            if (probability < probability_mutation) {
                auto x = fmod(generation[j].x * random(-5, 5), 2);
                auto y = fmod(generation[j].y * random(-5, 5), 2);
                generation[j] = Chromosome(x, y);
            }
        }

        std::vector<Chromosome> all_pairs;
        for (unsigned int i = 0; i < generation.size(); i++) {
            for (unsigned int j = 0; j < generation.size(); j++) {
                all_pairs.emplace_back(generation[i].x, generation[j].y);
            }
        }
        std::sort(all_pairs.begin(), all_pairs.end(), comparison_operator);

        std::vector<Chromosome> new_generation;
        for (unsigned int i = 0; i < generation.size(); i++) {
            new_generation.emplace_back(all_pairs[i]);
        }

        generation = new_generation;
        print_generation(generation, i);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Вариант №6." << endl << endl;
    cout << "Функция: cos(x) * cos(y)" << endl;
    cout << "Вероятность мутации 20%." << endl;
    cout << "Кол-во точек: 6." << endl;

    std::vector<int> generations_number = { 10 };
    for (const auto& num : generations_number) {
        cout << "Генетический алгоритм для " << num << " числа поколений" << endl;
        GeneticAlgorithm(num);
    }

    return 0;
}
