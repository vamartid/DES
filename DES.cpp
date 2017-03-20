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

unsigned short P_permutatiom[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

unsigned short int S_box[8][4][16] = {
    {//S1
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {//S2
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {//S3
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {//S4
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {//S5
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {//S6
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {//S7
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {//S8
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

unsigned short E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

DES::DES() {
	osc= OutputStreamController(false,true);
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
    osc.Cout("Message\t\t"+message.to_string());
    //perform initial permutation
    ciphertext=Permutate(message,initial_permutation);
    osc.Cout("Initial permutation\t"+ciphertext.to_string());
	//we can now perform the rounds

    //->need to be implemented
    Rounds(ciphertext);

    //perform final permutation
    ciphertext=Permutate(ciphertext,final_permutation);

    osc.Cout("Final permutation\t"+ciphertext.to_string());
//    osc.CoutAll();
    osc.LogSaved("DesLogFile");

    return ciphertext;
}

void DES::Rounds(std::bitset<64> &input ){
	for (short int round=1;round<=16;round++){
		osc.Cout("Round "+std::to_string(round));
		osc.Cout("Round input\t\t"+input.to_string());
		//split the message on 2 equal-sized parts
		//declare the parts
		std::bitset<32> left_part,right_part;
		//we need to break the key on the 27 bit to two parts
		for (int i = 32; i < 64; i++) {
			left_part.set(i-32,input[i]);
		}
		for (int i = 0; i < 32; i++) {
			right_part.set(i,input[i]);
		}
		osc.Cout("Left Part\t\t"+left_part.to_string());
		osc.Cout("Right Part\t\t"+right_part.to_string());
		//send the right part to the F function with the round's key
		std::bitset<32> f_output=F(right_part, keys[round-1]);
		osc.Cout("F output\t\t"+f_output.to_string());
		//XOR the F function output with the left part
		//set that output as the current left part
		left_part=left_part^f_output;
		osc.Cout("XOR(Li,Foutput)\t"+left_part.to_string());
		//keep right part the same

		//do the cross way merge
		std::bitset<64> merged;
		//apply the right part to the left of the merged
		for (int i = 63; i > 31; i--) {
			merged.set(i,right_part[i-32]);
		}
		//apply the left part to the left of the merged
		for (int i = 31; i >= 0; i--) {
			merged.set(i,left_part[i]);
		}
		osc.Cout("Round output\t\t"+merged.to_string());
		//set the merged as the new input for next round
		input=merged;
	}
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
	osc.Cout("Input key\t\t"+key.to_string());
	//parity drop on key input
    std::bitset<56> cipherKey=ParityDrop(key);
    //print output of parity drop
    osc.Cout("Parity drop\t\t"+cipherKey.to_string());
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
		osc.Cout("Left Part\t\t"+left_part.to_string());
		osc.Cout("Right Part\t\t"+right_part.to_string());
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
		osc.Cout("Left  Shifted Part\t"+left_part.to_string());
		osc.Cout("Right Shifted Part\t"+right_part.to_string());
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
		osc.Cout("Merged output\t"+merged.to_string());
		//and compress
		std::bitset<48> compressed= KeyCompression(merged);
		osc.Cout("Compressed merged\t"+compressed.to_string());
		//set the compressed output as the key of the round
		keys[round-1]=compressed;
		round++;
		//this will repeat for the 16 keys and the shift will be
	}while(round<=16);
	for (int i = 0; i < 16; ++i) {
		std::ostringstream i_str_stream;
		i_str_stream<< std::setw(2) << std::setfill('0') << i;
		osc.Cout("Output Key "+string(i_str_stream.str())+"\t"+keys[i].to_string());
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


std::bitset<32> DES::F(std::bitset<32> R, std::bitset<48> K) {
    //this will be E(Rn-1)ee
    std::bitset<48> E_R;
    //pos will take E value--
    int pos;
    for (int i = 47; i >= 0; i--) {
        pos = E[47 - i] - 1;
        E_R.set(i, R[31 - pos]);
    }

    //bitwise XOR of E_R + K
    std::bitset<48> extened_output = E_R ^ K;


    //now seperate the XORed bitset to 8 groups of 6-bits
    
    std::bitset<6> B1, B2, B3, B4, B5, B6, B7, B8;
    for (int i = 47; i > 41; i--) B1.set(i - 42, extened_output[i]);
    for (int i = 41; i > 35; i--) B2.set(i - 36, extened_output[i]);
    for (int i = 35; i > 29; i--) B3.set(i - 30, extened_output[i]);
    for (int i = 29; i > 23; i--) B4.set(i - 24, extened_output[i]);
    for (int i = 23; i > 17; i--) B5.set(i - 18, extened_output[i]);
    for (int i = 17; i > 11; i--) B6.set(i - 12, extened_output[i]);
    for (int i = 11; i > 5; i--) B7.set(i - 6, extened_output[i]);
    for (int i = 5; i >= 0; i--) B8.set(i, extened_output[i]);

    std::bitset<32> merged;
    std::bitset<4> S_B;

    //merging...
    S_B = S(B1, 0);
    for (int i = 3; i >= 0; i--) merged.set(28 + i, S_B[i]);
    S_B = S(B2, 1);
    for (int i = 3; i >= 0; i--) merged.set(24 + i, S_B[i]);
    S_B = S(B3, 2);
    for (int i = 3; i >= 0; i--) merged.set(20 + i, S_B[i]);
    S_B = S(B4, 3);
    for (int i = 3; i >= 0; i--) merged.set(16 + i, S_B[i]);
    S_B = S(B5, 4);
    for (int i = 3; i >= 0; i--) merged.set(12 + i, S_B[i]);
    S_B = S(B6, 5);
    for (int i = 3; i >= 0; i--) merged.set(8 + i, S_B[i]);
    S_B = S(B7, 6);
    for (int i = 3; i >= 0; i--) merged.set(4 + i, S_B[i]);
    S_B = S(B8, 7);
    for (int i = 3; i >= 0; i--) merged.set(i, S_B[i]);

    std::bitset<32> output;

    //P permutation
    output = Permutate(merged, P_permutatiom);
    return output;
}

/**
 * This is the S_BOX function. Given a 6-bit number returns the appropriate 4-bit.
 * 
 * @param input
 * @param s_box_intex
 * @return 
 */
std::bitset<4> DES::S(std::bitset<6> input, int s_box_intex) {
    int i, j;
    std::bitset<2> temp_i;
    std::bitset<4> temp_j;

    temp_i.set(0, input[0]);
    temp_i.set(1, input[5]);
    for (int k = 3; k >= 0; k--) {
        temp_j.set(k, input[k + 1]);
    }

    i = (int) temp_i.to_ulong();
    j = (int) temp_j.to_ulong();

    //get the right value from the S_BOX
    int temp = S_box[s_box_intex][i][j];

    std::bitset<4> output = std::bitset<4>(temp);
    return output;
}

std::bitset<32> DES::Permutate(std::bitset<32> input, unsigned short permutation[]) {
    std::bitset<32> output;
    int pos;
    for (int i = 31; i >= 0; i--) {
        pos = permutation[31 - i] - 1;
        output.set(i, input[31 - pos]);
    }
    return output;
}

//void DES::test() {
//    std::string s1 = "000110110000001011101111111111000111000001110010";
//    std::string s2 = "11110000101010101111000010101010";
//    std::bitset<48> k(s1);
//    std::bitset<32> r(s2);
//    cout << F(r, k) << endl;
//}
