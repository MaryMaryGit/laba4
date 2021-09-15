#include <cassert>
#include <iostream>
#include "C:\Users\mshlk\Documents\cs-lab03-lab04-1\cs-lab03\histogram.h"
#include "C:\Users\mshlk\Documents\cs-lab03-lab04-1\cs-lab03\svg.h"

using namespace std;

string brightness (size_t bin,size_t max_count)
{
    int pr;
    string s="#";
    if (max_count == 0) return "Error";
    else{
    pr=10 - (bin * 9) / max_count;

    for(int i=0;i<3;i++)
    {
      s += to_string(pr);
    }
   return s;
}}


void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, max, min);
    assert(min == 1);
    assert(max == 3);
}
void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, max, min);
    assert(min == -3);
    assert(max == -1);
}
void test_constant() {
    double min = 0;
    double max = 0;
    find_minmax({ 99,99,99 }, max, min);
    assert(min == 99);
    assert(max == 99);
}
void test_onenumber() {
    double min = 0;
    double max = 0;
    find_minmax({ 1 }, max, min);
    assert(min == 1);
    assert(max == 1);
}
void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, max, min);
    assert(min == 0);
    assert(max == 0);
}


void max_count() {
size_t bin = 10;
size_t max_count = bin;
assert( brightness(bin, max_count) == "#111" );
}

void test_bin() {
size_t bin = 0;
size_t max_count = bin;
assert( brightness(bin, max_count) == "Error" );
}




int main()
{

    // Тесты для функции find_minmax
    test_positive();
    test_negative();
    test_constant();
    test_onenumber();
    test_empty();
    test_bin();
    max_count();
    return 0;
}
