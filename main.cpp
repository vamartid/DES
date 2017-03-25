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
#include<cstring>
#include "DES.h"
#include "OutputStreamController.h"

void help() {
	cout << "Use the following flags for the given gools..." << endl;
	cout << "-e\tEncrypt the given message with the given key" << endl;
	cout << "-d\tDeencrypt  the given message with the given key" << endl;
	cout << "-p\tPrint log on console" << endl;
	cout << "-l\tSave to the log file \"DesEventLog.log\"" << endl;
	cout << "-m\tMessage flag, MUST BE FOLLOWED BY 64-bit MESSAGE" << endl;
	cout << "-m\tKey flag, MUST BE FOLLOWED BY 64-bit KEY" << endl;
}

int main(int argc, const char** argv) {

	string t_message;
	string t_key;

	int i = 1;
	bool flags_ok = true;
	bool log = false;
	bool print = false;
	bool enc = true;
	bool skip=false;
	if (strcmp(argv[1], "-help")==0) {
		help();
		skip=true;
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
	//create the object which will do the encryption
	DES *des = new DES(enc);//true-false encryptor-decryptor
	//set key
	std::bitset<64> key(t_key);
	//set message
	std::bitset<64> message(t_message);
	if(!skip){
		//print the output
		std::cout << des->Cipher(message,key)<<std::endl;
		//if he typed -p print messages
		if(print){
			des->osc.CoutAll();
		}
		//if he typed -l log messages
		if(log){
			des->osc.LogSaved("DesEventLog");
		}
	}
	return 0;
}

