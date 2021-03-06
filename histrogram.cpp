#include <iostream>
#include <vector>
#include "histogram.h"
using namespace std;

vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt) {
    Input data;

    if (prompt) cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt) cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt) cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size()) {
        max = numbers[0];
        min = numbers[0];
        if (numbers.size()) {
            for (double x : numbers) {
                if (x > max) {
                    max = x;
                }
                if (x < min) {
                    min = x;
                }
            }
        }
    }
}

const vector<size_t> make_histogram(Input data) {
 vector<size_t> bins(data.bin_count);
    double min, max;
    find_minmax(data.numbers, min, max);

    if (min == max) {
        for (double number : data.numbers) {
            bins[0]++;
        }
        return bins;
    }
    else {
        for (double number : data.numbers) {
            size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
            if (bin == data.bin_count) {
                bin--;
            }
            bins[bin]++;
        }
        return bins;
    }
}

void show_histogram_text(const vector<size_t>& bins) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }
}
