#ifndef DES_H
#define DES_H

#include <bitset>
#include <iostream>       // std::cout
using std::cout;
using std::cin;
using std::endl;
#include <bitset>         // std::bitset
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

class DES {
private:
	//fields
//	std::bitset<64> message;
//     key;
    std::bitset<48> keys[16];
    //functions
//    void KeyGen();
    std::bitset<56> ParityDrop(std::bitset<64>);
    void Rotate(std::bitset<28>& , unsigned short );
    std::bitset<48> KeyCompression( std::bitset<56> );
    void KeyGen(std::bitset<64>);
    std::bitset<64> Permutate( std::bitset<64> , unsigned short []);
public:
//    DES( std::bitset<64> );
    DES();
    DES(const DES& );
    virtual ~DES();
    std::bitset<64> Cipher(std::bitset<64> , std::bitset<64> );


};

#endif /* DES_H */
