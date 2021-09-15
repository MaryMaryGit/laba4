
#include <iostream>
#include <string>
#include <vector>
#include "svg.h"
using namespace std;
string
add_text_to()
{
    stringstream buffer;
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD mask_2 = 0x0000ff;
   if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_2;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v"<<version_major<<"."<<version_minor<<"(build"<<build<<")\n";

    }
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH+1;
    GetComputerNameA(computer_name, &size);
    buffer<<"Computer name:" <<computer_name;
    return buffer.str();
    return 0;
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}


void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x= '" << x << "' y= '" << y << "' width= '" << width << "' height= '" << height << "' stroke= '" << stroke << "' fill= '" << fill << "' />\n";
}
void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}


string brightness (size_t bin,size_t max_count)
{
    int pr;
    string s="#";
    if (max_count == 0) return "Error";
    else {
    pr=10 - (bin * 9) / max_count;

    for(int i=0;i<3;i++)
    {
        if (pr > 9) pr = 9;
      s += to_string(pr);
    }
   return s;
}}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }


    const bool scaling_needed = (max_count * BLOCK_WIDTH) > MAX_ASTERISK;
    double scaling_factor;
    if (scaling_needed)
    {
        scaling_factor = static_cast<double>(MAX_ASTERISK) / (max_count * BLOCK_WIDTH);
    }
    else {
        scaling_factor = 1;
    }
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 50;
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin*scaling_factor;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        string fill;
        fill=brightness(bin,max_count);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", fill);
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, top + TEXT_BASELINE,add_text_to());
    svg_end();

}
