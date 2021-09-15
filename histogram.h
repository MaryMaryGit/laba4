#pragma once
#include <vector>
using namespace std;
struct Input {
    vector<double> numbers;
    size_t bin_count;

};
const vector<size_t> make_histogram(Input data);
Input read_input(istream& in, bool prompt);
void show_histogram_text(const vector<size_t>& bins);
vector<double> input_numbers(istream& in, size_t count);
void find_minmax(const vector<double>& numbers, double& min, double& max);




