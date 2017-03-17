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

	unsigned short round=1;
	std::cout<<"Input key\t\t"<<key<<std::endl;
	//parity drop on key input
    std::bitset<56> cypherKey=ParityDrop();
    //print output of parity drop
	std::cout<<"Parity drop\t\t"<<cypherKey<<std::endl;
	//declare the parts
	std::bitset<28> left_part,right_part;
	//we need to break the key on the 27 bit to two parts
	for (int i = 28; i < 56; i++) {
		left_part.set(i-28,cypherKey[i]);
	}
	for (int i = 0; i < 28; i++) {
		right_part.set(i,cypherKey[i]);
	}
	do{
		//print the 2 parts
		std::cout<<"Left Part\t\t"<<left_part<<std::endl;
		std::cout<<"Right Part\t\t"<<right_part<<std::endl;
		//set the shift value
		//1 on rounds 1,2,9,16
		//2 on all other rounds
		unsigned short shift=2;
		if ((round == 1)||(round == 2)||(round == 9)||(round == 16)) {
			shift--;
		}
		//and then left shift both parts
		left_part=left_part<<shift;
		right_part=right_part<<shift;
		//print the 2 parts
		std::cout<<"Left  Shifted Part\t"<<left_part<<std::endl;
		std::cout<<"Right Shifted Part\t"<<right_part<<std::endl;
		//then merge them
		std::bitset<56> merged;
		//apply the left part to the left of the merged
		for (int i = 55; i > 27; i--) {
			merged.set(i,left_part[i-28]);
		}
		//apply the right part to the left of the merged
		for (int i = 27; i > 0; i--) {
			merged.set(i,right_part[i]);
		}
		std::cout<<"Merged output\t\t"<<merged<<std::endl;
		//and compress
		std::bitset<48> compressed= KeyCompression(merged);
		std::cout<<"Compressed merged\t"<<compressed<<std::endl;
		//set the compressed output as the key of the round
		keys[round-1]=compressed;
		round++;
		//this will repeat for the 16 keys and the shift will be
	}while(round<=16);
	for (int i = 0; i < 16; ++i) {
		std::cout<<"Output Key "<<i<<" "<<keys[i]<<std::endl;
	}
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

