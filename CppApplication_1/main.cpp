#include <iostream>       // std::cout
using std::cout;
using std::cin;
using std::endl;
#include <string>         // std::string
using std::string;
#include <sstream>
#include <iomanip>
#include <iterator>
using std::istream_iterator;
#include <bitset>         // std::bitset
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include "DES.h"


//use this pls nullptr
//#ifndef NULL
//#define NULL   ((void *) 0)
//#endif

int main(int argc, char** argv) {
    clock_t t;
    t = clock();

    std::bitset<64> message("0101010001101000011001010010000001101101011001010111001101110011");
    std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");

    DES *des = new DES(message);
    des->KeyGen(key);
    t = clock() - t;
    std::cout << "Took " << t << " clicks " << (((float) t) / CLOCKS_PER_SEC) << " seconds" << endl;
    return 0;
}
