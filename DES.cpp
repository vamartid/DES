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
	14, 17, 11, 24,  1,  5,
	 3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

unsigned short initial_permutation[]={
	58, 50, 42, 34, 26, 18, 10,  2,
	60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6,
	64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1,
	59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5,
	63, 55, 47, 39, 31, 23, 15,  7
};

unsigned short final_permutation[]={
	40,  8, 48, 16, 56, 24, 64, 32,
	39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30,
	37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28,
	35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26,
	33,  1, 41,  9, 49, 17, 57, 25
};

//DES::DES(std::bitset<64> m ) {
//    message = m;
//}
DES::DES() {

}
DES::DES(const DES& orig) {
}

DES::~DES() {

}

/**
 * DES is a Block cipher, which takes
 * 64-bit plain text and a 56-bit key
 * and creates a 64-bit cipher text
 */
std::bitset<64>  DES::Cipher(std::bitset<64> message, std::bitset<64> key){
	//declare 64-bit cipher text
	std::bitset<64> ciphertext;
	//generate the keys with keygen function
    KeyGen(key);
    //we have all the keys on the keys field of this object now
    //
    //we can now perform the General Structure of DES algorithm
    //
    //the message is
    std::cout<<"Message\t\t\t"<<message<<std::endl;
    //perform initial permutation
    ciphertext=Permutate(message,initial_permutation);
    std::cout<<"Initial permutation\t"<<ciphertext<<std::endl;
	//we can now perform the rounds
    //->need to be implemented

    //perform final permutation
    ciphertext=Permutate(message,final_permutation);
	std::cout<<"Final permutation\t"<<ciphertext<<std::endl;

    return ciphertext;
}

/**
 * perform key compression on the input
 */
std::bitset<64> DES::Permutate( std::bitset<64> input ,unsigned short permutation[]){
    std::bitset<64> output;
    int pos;//pos will take parity drop value--
    //because the array starts from 1 and not 0
    //also because we go from 63 to 0 we need to parse
    //the array from the start which is 1 so we do 63-1
    //also the value is being subtracted from 63
    //because set function starts from the other position
    for (int i = 63; i >=0; i--) {
		pos=permutation[63-i]-1;
		output.set(i,input[63-pos]);
	}
	return output;
}

/**
 * composes the keys which will be used on the DES algorithm
 * and saves them on the keys[] field
 */
void DES::KeyGen(std::bitset<64> key){
	unsigned short round=1;
	std::cout<<"Input key\t\t"<<key<<std::endl;
	//parity drop on key input
    std::bitset<56> cipherKey=ParityDrop(key);
    //print output of parity drop
	std::cout<<"Parity drop\t\t"<<cipherKey<<std::endl;
	//declare the parts
	std::bitset<28> left_part,right_part;
	//we need to break the key on the 27 bit to two parts
	for (int i = 28; i < 56; i++) {
		left_part.set(i-28,cipherKey[i]);
	}
	for (int i = 0; i < 28; i++) {
		right_part.set(i,cipherKey[i]);
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
		Rotate(left_part,shift);
		Rotate(right_part,shift);
//		left_part=left_part<<shift;
//		right_part=right_part<<shift;
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
		for (int i = 27; i >= 0; i--) {
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
		std::cout<<"Output Key "<<i<<"\t\t"<<keys[i]<<std::endl;
	}
}

/**
 * perform parity drop on the key
 */
std::bitset<56> DES::ParityDrop(std::bitset<64> key){
    std::bitset<56> output;
    int pos;//pos will take parity drop value--
	//because the array starts from 1 and not 0
    //also because we go from 55 to 0 we need to parse
    //the array from the start which is 1 so we do 55-1
	//also the value is being subtracted from 63
	//because set function starts from the other position
	for (int i = 55; i >= 0; i--) {
		pos=parity_drop[55-i]-1;
		output.set(i,key[63-pos]);
	}
	return output;
}

/**
 * cycle shift the bitset m possitions left
 */
void DES::Rotate(std::bitset<28>& b, unsigned short m){
	b = b << m | b >> (28-m);
}

/**
 * perform key compression on the input
 */
std::bitset<48> DES::KeyCompression( std::bitset<56> input ){
    std::bitset<48> output;
    int pos;//pos will take parity drop value--
    //because the array starts from 1 and not 0
    //also because we go from 55 to 0 we need to parse
    //the array from the start which is 1 so we do 55-1
    //also the value is being subtracted from 63
    //because set function starts from the other position
    for (int i = 47; i >=0; i--) {
		pos=compression_permutation[47-i]-1;
		output.set(i,input[55-pos]);
	}
	return output;
}
