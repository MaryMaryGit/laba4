
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;
string add_text_to();
void svg_begin(double width, double height);
void svg_end();
void svg_rect(double x, double y, double width, double height, string stroke, string fill);
void svg_text(double left, double baseline, string text);
void show_histogram_svg(const vector<size_t>& bins);
string brightness (size_t bin,size_t max_count);
