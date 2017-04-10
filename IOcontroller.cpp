/*
 * IOcontroller.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: vamartid
 */

#include "IOcontroller.h"

IOcontroller::IOcontroller() {
	// TODO Auto-generated constructor stub

}

IOcontroller::~IOcontroller() {
	// TODO Auto-generated destructor stub
}

/**
 *  read from a file
 *  save its line to a vector
 * @param file_name
 * @return
 */
std::vector<std::string> IOcontroller::readFromFile(string file_name){
    std::vector<std::string> myLines;
    r_stream.open(file_name, ios::in);
    //if file exist and is open
    if(!r_stream){
    	std::cout<<"File "<<file_name<<" not found"<<endl;
    	return myLines;
    }
    std::string line;
    //push each line as an element of the vector
    while(!r_stream.eof()){
        if (getline(r_stream,line)) {
            myLines.push_back(line);
        }
    };
    //std::copy(std::istream_iterator<std::string>(r_stream),std::istream_iterator<std::string>(),std::back_inserter(myLines));
    //close the ifstream
    r_stream.close();
    //print what u got for each element of the vector
//    for (auto i = myLines.begin(); i != myLines.end(); ++i){
//        std::cout << *i << '\n'<<endl;
//    }
//    std::cout <<"End of vector"<<endl;
    return myLines;
}

/**
 * write a string to the file.
 * if there is no file create it
 * if the job is not done
 * close the file return 1
 * else close the file and return 0
 *
 * @param file_name
 * @param cyphertext
 * @return
 */
int IOcontroller::writeToFile(std::string file_name,std::string cyphertext){
    ofstream w_stream(file_name);
    if (w_stream << cyphertext) {
        w_stream.close();
        return 0;
    }else{
        w_stream.close();
        return 1;
    }
}

