#include <iostream>       // std::cout
using std::cout;
using std::cin;
using std::endl;
#include <string>         // std::string
using std::string;
#include <sstream>
#include <iomanip>
#include <iterator>
using std::istream_iterator;
#include <bitset>         // std::bitset

#ifndef NULL
#define NULL   ((void *) 0)
#endif


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
		std::vector<std::string> readFromFile (std::string file_name);
		int writeToFile(std::string file_name,string cyphertext);

};

/**
 *  read from a file
 *  save its line to a vector
 * @param file_name
 * @return
 */
std::vector<std::string> IOcontroller::readFromFile(string file_name){
    std::vector<std::string> myLines;
    r_stream.open(file_name, ios::in);
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


std::string strToHex(string str){
    std::ostringstream result;
    result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
    std::copy(str.begin(), str.end(), std::ostream_iterator<unsigned int>(result, ""));
    return result.str();
}

std::string compineStrVec(std::vector<std::string> vector){
    string compined_str;
    std::string enter("\n");
    for (auto i = vector.begin(); i != vector.end(); ++i){
        string tmp= *i;
        compined_str.append(strToHex(tmp)+"0D0A");
//        compined_str.append("\n");
    }
    return compined_str;
}

/**
 * hex string (written in caps) to binary string
 */
string GetBinaryStringFromHexString (string sHex){
	string sReturn = "";
	for (int i = 0; i < sHex.length (); ++i){
		switch (sHex [i]){
			case '0': sReturn.append ("0000"); break;
			case '1': sReturn.append ("0001"); break;
			case '2': sReturn.append ("0010"); break;
			case '3': sReturn.append ("0011"); break;
			case '4': sReturn.append ("0100"); break;
			case '5': sReturn.append ("0101"); break;
			case '6': sReturn.append ("0110"); break;
			case '7': sReturn.append ("0111"); break;
			case '8': sReturn.append ("1000"); break;
			case '9': sReturn.append ("1001"); break;
			case 'A': sReturn.append ("1010"); break;
			case 'B': sReturn.append ("1011"); break;
			case 'C': sReturn.append ("1100"); break;
			case 'D': sReturn.append ("1101"); break;
			case 'E': sReturn.append ("1110"); break;
			case 'F': sReturn.append ("1111"); break;
		}
	}
	return sReturn;
}

std::vector<std::string> Split(const std::string& str, int splitLength)
{
   int NumSubstrings = str.length() / splitLength;
   std::vector<std::string> ret;
   for (auto i = 0; i < NumSubstrings; i++)
   {
        ret.push_back(str.substr(i * splitLength, splitLength));
   }
   // If there are leftover characters, create a shorter item at the end.
   if (str.length() % splitLength != 0)
   {
//	   std::string tmp=str.substr(splitLength*NumSubstrings, str.length()%splitLength);
//	   std::cout << tmp <<endl;
	   ret.push_back(str.substr(splitLength*NumSubstrings).append(str.length() % splitLength ,'0'));

   }
   return ret;
}

int main(int argc, char** argv) {
	//create an input-output controller
	IOcontroller io_ctrl;
//    std::vector<std::string> input=io_ctrl.readFromFile("message.txt");
//    std::string compined_input=compineStrVec(input);
//    cout<< compined_input;
    //read the input and compine it to a string
    std::string compined_input=compineStrVec(io_ctrl.readFromFile("message.txt"));
    //cout<< compined_input<<endl;
    //convert the string to a binary string
    std::string binaryStr=std::string(GetBinaryStringFromHexString(compined_input));

    std::vector<string> bin_str_tokens_vector = Split(binaryStr, 64);

    std::bitset<64> message[bin_str_tokens_vector.size()];
    int a=0;
    for (auto i = bin_str_tokens_vector.begin(); i != bin_str_tokens_vector.end(); ++i){
        	string tmp= *i;
			message[a] =   std::bitset<64> (std::string(tmp));;
			a++;
    }
    for (int i = 0; i < sizeof(message)/sizeof(message[0]); ++i) {
		std::cout << message[i] <<endl;
	}
//    std::bitset<64> b(bit_string);       // [0,0,1,1,0,0,1,0]
//    std::cout << b3.to_string() << std::endl ;


    //output
//    cout<< strToHex(compined_input)<<endl;
//    string cyphertext="C0999FDDE378D7ED727DA00BCA5A84EE47F269A4D64381909DD52F78F5358499828AC9B453E0E653";
//    io_ctrl.writeToFile("cyphertext.txt",cyphertext);


    //cout<<strToHex(newString)<<endl;
    return 0;
}
