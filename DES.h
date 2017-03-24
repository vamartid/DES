#ifndef DES_H
#define DES_H

#include <bitset>
#include <iostream>       // std::cout
using std::cout;
using std::cin;
using std::endl;
#include <bitset>         // std::bitset
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <string>
using std::string;
#include <iomanip>
using std::setfill;
#include <sstream>

#include "OutputStreamController.h"

class DES {

private:
	//fields
    bool type;//declares if the object is encryptor or decryptor
	std::bitset<48> keys[16];

    //functions
    int Type(int);
    std::bitset<56> ParityDrop(std::bitset<64>);
    void Rotate(std::bitset<28>& , unsigned short );
    std::bitset<48> KeyCompression( std::bitset<56> );
    void KeyGen(std::bitset<64>);
    std::bitset<64> Permutate( std::bitset<64> , unsigned short []);
    std::bitset<32> Permutate( std::bitset<32> , unsigned short []);
    std::bitset<4> S(std::bitset<6>,int);
    std::bitset<32> F(std::bitset<32>, std::bitset<48>);
    void Rounds(std::bitset<64>&);
public:
    OutputStreamController osc;// maybe will be set public
    DES(bool);
    DES(const DES& );
    virtual ~DES();
    std::bitset<64> Cipher(std::bitset<64> , std::bitset<64> );


};

#endif /* DES_H */
