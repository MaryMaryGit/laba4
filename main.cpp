#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <curl/curl.h>
#include <Windows.h>
#include "svg.h"
#include "histogram.h"
#include <windows.h>

using namespace std;
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {

     auto data_size = item_size * item_count;
     stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
     buffer->write(reinterpret_cast<char*>(items), data_size);
      return data_size;

}

Input
download(const string& address)
{

    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        double connect;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if(CURLE_OK == res)
        {
            res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect);

                cerr <<"Connect: " << connect;

        }
        curl_easy_cleanup(curl);

        if(res)
        {
            cout <<  curl_easy_strerror(res);
            exit(1);
        }
    }
        return read_input(buffer, false);
}

struct ConsoleArguments {
    bool valid;
    bool use_remote_file;
    const char* remote_file_address;
    bool use_svg_output;
};

ConsoleArguments parse_arguments(int argc, char* argv[]) {
    ConsoleArguments res;
    res.valid = false;
    res.use_remote_file = false;
    res.use_svg_output = true;
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-format") == 0) {
            if ((i+1) < argc) {
                if (strcmp(argv[i+1], "svg") == 0)
                    res.use_svg_output = true;
                else if (strcmp(argv[i+1], "txt") == 0)
                    res.use_svg_output = false;
                else return res;
            } else return res;
            i += 1;
        } else {
            res.use_remote_file = true;
            res.remote_file_address = argv[i];
        }
        ++i;
    }
    res.valid = true;
    return res;
}

void print_usage_message(const char* progname) {
    cerr << "Error: wrong format. TIP: " << progname << " [-format {svg|txt}] [input URL]"
         << endl;
}

int main(int argc, char* argv[]) {

    ConsoleArguments args = parse_arguments(argc, argv);
    if (!args.valid) {
        print_usage_message(argv[0]);
        return 0;
    }

    Input input;
    if (args.use_remote_file) {
        input = download(args.remote_file_address);
    } else {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    if (args.use_svg_output)
        show_histogram_svg(bins);
    else
        show_histogram_text(bins);

    return 0;

}
