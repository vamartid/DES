#include "DES.h"

DES::DES(std::bitset<64> m, std::bitset<64> k) {
    message = m;
    key = k;
}

DES::DES(const DES& orig) {
}

DES::~DES() {
}

void DES::KeyGen(){
    //std::bitset<56> cyferKey = ParityDrop();
    std::cout<< key<<endl;
    key.set(12, true);
    cout<< key<<endl;
}

std::bitset<56> DES::ParityDrop(){
    std::bitset<56> output;
    return output;
}