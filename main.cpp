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


void help() {
	cout << "help is comming..." << endl;
	cout << "Use the foloing flags for the given gools..." << endl;
	cout << "-e\tencrypt the given message with the given key" << endl;
	cout << "-d\tdeencrypt  the given message with the given key" << endl;
	cout << "-pl\tprint log on console" << endl;
	cout << "-sl\tsave log into a file" << endl;
	cout << "-m\tmessage flag, MUST BE FOLLOWED BY 64-bit MESSAGE" << endl;
	cout << "-m\tkey flag, MUST BE FOLLOWED BY 64-bit KEY" << endl;

}

void encrip(string s) {

}

//use this pls nullptr
//#ifndef NULL
//#define NULL   ((void *) 0)
//#endif

int main(int argc, const char** argv) {
	clock_t t = clock();

	string t_message;
	string t_key;

	int i = 1;
	bool flags_ok = true;
	if (strcmp(argv[1], "-help")==0) {
		help();
	}
	else {
		for (;i < argc && flags_ok;i++) {
			if (strcmp(argv[1], "-m") == 0) {
				t_message = argv[++i];
				if (t_message.size() != 64) {
					cout << "message length MUST be 64-bits" << endl;
					flags_ok = false;
				}
			}
			else if (strcmp(argv[1], "-k") == 0)
			{
				t_key = argv[++i];
				if (t_key.size() != 64) {
					cout << "key length MUST be 64-bits" << endl;
					flags_ok = false;
				}
			}
			else if (strcmp(argv[1], "-pl") == 0)// print log
			{

			}
			else if (strcmp(argv[1], "-sl") == 0)//save log
			{

			}
			else if (strcmp(argv[1], "-e") == 0)//encript
			{

			}
			else if (strcmp(argv[1], "-d") == 0)//decript
			{

			}
			else
			{
				std::cout << "unknowed flag " << argv[i] << endl << "pass -help for help" << endl;
				flags_ok = false;
			}
		}
	}

	//key
	std::bitset<64> key(t_key);
	//message
	std::bitset<64> message(t_message);
    //DES *des = new DES(message);
	//DES *des = new DES(false);//true-false encryptor-decryptor
	//std::cout<<(des->Cipher(message,key))<<endl;
	//t = clock() - t;
	//std::cout << "Execution time " << t << " clicks " << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;
	
	/*if (flags_ok) {

	}*/
	
	system("pause");
	return 0;
}