#include "DES.h"

//key actions
unsigned short parity_drop[]={
		  57, 49, 41, 33, 25, 17,  9,
		   1, 58, 50, 42, 34, 26, 18,
		  10,  2, 59, 51, 43, 35, 27,
		  19, 11,  3, 60, 52, 44, 36,
		  63, 55, 47, 39, 31, 23, 15,
		   7, 62, 54, 46, 38, 30, 22,
		  14,  6, 61, 53, 45, 37, 29,
		  21, 13,  5, 28, 20, 12,  4
};

unsigned short compression_permutation[]={
  14, 17, 11, 24,  1, 5,
  3, 28 ,15,  6, 21, 10,
  23, 19, 12,  4, 26, 8,
  16,  7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55,
  30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53,
  46, 42, 50, 36, 29, 32
};

DES::DES(std::bitset<64> m, std::bitset<64> k) {
    message = m;
    key = k;
}

DES::DES(const DES& orig) {
}

DES::~DES() {

}

void DES::KeyGen(){
    std::cout<< key<<std::endl;
	std::bitset<56> cypherKey=ParityDrop();
	std::cout<<cypherKey<<std::endl;

	//we need to break the key on the 27 bit to two parts
	//and then left shift both parts
	//then merge them
	//and compress
	//this will repeat for the 16 keys and the shift will be
	//1 on rounds 1,2,9,16
	//2 on all other rounds

//	std::bitset<48> compressed= KeyCompression(merged_shifted);
//	std::cout<<compressed<<std::endl;

}


/**
 * perform parity drop on the key
 */
std::bitset<56> DES::ParityDrop(){
    std::bitset<56> output;
    int pos;//pos will take parity drop value--
    //because the array starts from 1 and not 0
    //also the value is being substructed from 63
    //because set function starts from the other position
    for (int i = 0; i < 56; i++) {
    	pos=63-(parity_drop[i]-1);
    	output.set(i,key[pos]);
	}
	return output;
}

/**
 * perform key compression on the input
 */
std::bitset<48> DES::KeyCompression( std::bitset<56> input ){
    std::bitset<48> output;
    int pos;//pos will take parity drop value--
    //because the array starts from 1 and not 0
    //also the value is being substructed from 63
    //because set function starts from the other position
    for (int i = 0; i < 48; i++) {
    	pos=63-(parity_drop[i]-1);
    	output.set(i,input[pos]);
	}
	return output;
}
