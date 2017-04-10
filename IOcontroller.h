/*
 * IOcontroller.h
 *
 *  Created on: Mar 27, 2017
 *      Author: vamartid
 */

#ifndef IOCONTROLLER_H_
#define IOCONTROLLER_H_



#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::streampos;
using std::ios;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iterator>
using std::istream_iterator;

class IOcontroller {
	private:
		ofstream w_stream;//Stream class to write on files
		ifstream r_stream;//Stream class to read from files
	public:
		IOcontroller();
		virtual ~IOcontroller();
		std::vector<std::string> readFromFile (std::string file_name);
		int writeToFile(std::string file_name,string cyphertext);

};

#endif /* IOCONTROLLER_H_ */




