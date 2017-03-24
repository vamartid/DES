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
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include<cstring>
#include "DES.h"
#include "OutputStreamController.h"

void help() {
	cout << "help is comming..." << endl;
	cout << "Use the foloing flags for the given gools..." << endl;
	cout << "-e\tencrypt the given message with the given key" << endl;
	cout << "-d\tdeencrypt  the given message with the given key" << endl;
	cout << "-p\tprint log on console" << endl;
	cout << "-l\tsave log into a file" << endl;
	cout << "-m\tmessage flag, MUST BE FOLLOWED BY 64-bit MESSAGE" << endl;
	cout << "-m\tkey flag, MUST BE FOLLOWED BY 64-bit KEY" << endl;

}

//use this pls nullptr
//#ifndef NULL
//#define NULL   ((void *) 0)
//#endif

int main(int argc, const char** argv) {
//	clock_t t = clock();

	string t_message;
	string t_key;

	int i = 1;
	bool flags_ok = true;
	bool log = false;
	bool print = false;
	bool enc = true;

	if (strcmp(argv[1], "-help")==0) {
		help();
	}
	else {
		for (;i < argc && flags_ok;i++) {
			if (strcmp(argv[i], "-m") == 0) {
				t_message = argv[++i];
				if (t_message.size() != 64) {
					cout << "message length MUST be 64-bits" << endl;
					flags_ok = false;
				}
			}
			else if (strcmp(argv[i], "-k") == 0)
			{
				t_key = argv[++i];
				if (t_key.size() != 64) {
					cout << "key length MUST be 64-bits" << endl;
					flags_ok = false;
				}
			}
			else if (strcmp(argv[i], "-p") == 0)// print log
			{
				print = true;
			}
			else if (strcmp(argv[i], "-l") == 0)//save log
			{
				log = true;
			}
			else if (strcmp(argv[i], "-e") == 0)//encript
			{
				enc=true;
			}
			else if (strcmp(argv[i], "-d") == 0)//decript
			{
				enc=false;
			}
			else
			{
				std::cout << "unknowed flag " << argv[i] << endl << "pass -help for help" << endl;
				flags_ok = false;
			}
		}
	}
	//0000000100100011010001010110011110001001101010111100110111101111
	//1000110010100110010011011110100111000001101100010010001110100111
	DES *des = new DES(enc);//true-false encryptor-decryptor

	//key
	std::bitset<64> key(t_key);
	//message
	std::bitset<64> message(t_message);
    //DES *des = new DES(message);
	//DES *des = new DES(false);//true-false encryptor-decryptor
	std::cout << des->Cipher(message,key)<<std::endl;
	if(print){
		des->osc.CoutAll();
	}
	if(log){
		des->osc.LogSaved("DesEventLog");
	}
	//t = clock() - t;
	//std::cout << "Execution time " << t << " clicks " << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;
	
	/*if (flags_ok) {

	}*/

	return 0;
}
