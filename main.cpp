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
    clock_t t = clock();

    //key
    std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");
    //plaintext
    std::bitset<64> message("0000000100100011010001010110011110001001101010111100110111101111");
    //ciphertext
//    std::bitset<64> message("1000010111101000000100110101010000001111000010101011010000000101");

//    DES *des = new DES(message);
	DES *des = new DES(false);//true-false encryptor-decryptor
    des->Cipher(message,key);
    t = clock() - t;
    std::cout << "Execution time " << t << " clicks " << (((float) t) / CLOCKS_PER_SEC) << " seconds" << endl;
    return 0;
}
