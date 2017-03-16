/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DES.h
 * Author: Celia
 *
 * Created on 15 Μαρτίου 2017, 2:02 μμ
 */

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
	std::bitset<64> message;
    std::bitset<64> key;
    
    //functions
//    void KeyGen();
    std::bitset<56> ParityDrop();
    std::bitset<48> KeyCompression( std::bitset<56> );
public:
    DES( std::bitset<64> , std::bitset<64> );
    DES(const DES& orig);
    virtual ~DES();
    void KeyGen();//temporary public
};

#endif /* DES_H */

