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
#include "IOcontroller.h"

void help() {
	cout << "Use the following flags for the given gools..." << endl;
	cout << "-e\tEncrypt the given message with the given key" << endl;
	cout << "-d\tDeencrypt  the given message with the given key" << endl;
	cout << "-p\tPrint log on console" << endl;
	cout << "-l\tSave to the log file \"DesEventLog.log\"" << endl;
	cout << "-m\tMessage flag, MUST BE FOLLOWED BY 64-bit MESSAGE" << endl;
	cout << "-k\tKey flag, MUST BE FOLLOWED BY 64-bit KEY" << endl;
	cout << "-b\tDeclares that what comes after is in bit format" << endl;
	cout << "-s\tDeclares that what comes after is in string format" << endl;
	cout << "-s\tDeclares that what comes after is in the file with that name"
			<< endl;
}

std::bitset<64>* convertToGroupsOf64bits(string compined_input, int *length) {
	//remove quotes
//	compined_input=compined_input.substr(1, compined_input.size()-2);
//	//remove last nextline character
	if(compined_input[compined_input.size()-1]=='\n'){
		compined_input=compined_input.substr(0, compined_input.size()-1);
	}
	//add more spaces to the string in order to be fully divided by 8
	//because 8 chars are 64 bits
	if (compined_input.size() % 8 != 0) {
		std::size_t times = compined_input.size() % 8;
		compined_input.append(8 - times, ' ');
	}
	//declare the array of the 64-bit cells so the size is
	//size/8char because each char is 8 bit so 8*8=64
	*length = compined_input.size() / 8;
	static std::bitset<64>* bits = new std::bitset<64>[*length];
	//for each cell of the bits array convert
	//the 8 next characters of the string to bitset of 8 and
	//add them to the 64bit cell
	for (int i = 0; i < *length; i++) {
		for (std::size_t j = 0; j < 8; j++) {
			std::bitset<8> temp = compined_input.c_str()[i * 8 + j];
			for (std::size_t n = 0; n < 8; n++) {
				bits[i].set(63 - (j * 8 + n), temp[7 - n]);
			}
		}
	}
	return bits;
}

std::bitset<64>* breakToGroupsOf64bits(string compined_input, int *length) {
	//remove all nextline character
	//~~this is not done because argv cuts the parts that
	//~~are separated with spaces and nextlines
	//declare the array of the 64-bit cells so the size is
	//size/8char because each char is 8 bit so 8*8=64
	*length = compined_input.size() / 64;
	static std::bitset<64>* bits = new std::bitset<64>[*length];
	//for each 64 chars of the stirng
	//create a 64bit bitset and add it
	//as a cell to the array
	for (int i = 0; i < *length; i++) {
		std::bitset<64> temp(compined_input.substr(i * 64, 64));
		bits[i] = temp;
	}
	return bits;
}

/**
 * compines a vectort with strings to a single string
 */
std::string compineStrVec(std::vector<std::string> vector) {
	string compined_str;
	std::string enter("\n");
	for (auto i = vector.begin(); i != vector.end(); ++i) {
		string tmp = *i;
//        compined_str.append(strToHex(tmp)+"0D0A");
		compined_str.append(tmp);
		compined_str.append("\n");
	}
	return compined_str;
}

int main(int argc, const char** argv) {

	string t_message;
	string t_key;

	int i = 1;
	bool flags_ok = true;
	bool log = false;
	bool print = false;
	bool enc = true;
	bool skip = false;
	std::bitset<64>* key;
	int key_size = 0;
	std::bitset<64>* bits_message = nullptr;
	IOcontroller* io_ctrl = nullptr;
	int bits_message_size = 0;
	if (strcmp(argv[1], "-help") == 0) {
		help();
		skip = true;
	} else {

		for (; i < argc && flags_ok; i++) {
			if (strcmp(argv[i], "-m") == 0) {
				//now we check the type of message
				t_message = argv[++i];
				if (t_message == "-s") {
					//now we set the message
					t_message = argv[++i];
					//set message
					bits_message = convertToGroupsOf64bits(t_message,
							&bits_message_size);
				} else if (t_message == "-b") {
					//now we set the message
					t_message = argv[++i];
					if ((t_message.size()) % 64 == 0) {
						//set message
						bits_message = breakToGroupsOf64bits(t_message,
								&bits_message_size);
					} else {
						cout << "Message as bits MUST be multiple of 64"
								<< endl;
						flags_ok = false;
					}
				} else if (t_message == "-f") {
					//now we set the message
					t_message = argv[++i];
					//create an input-output controller
					io_ctrl = new IOcontroller();
					//read the input and compine it to a string
					std::string compined_input = compineStrVec(
							io_ctrl->readFromFile(t_message));
					//set message
					bits_message = convertToGroupsOf64bits(compined_input,
							&bits_message_size);
				} else {
					cout
							<< "You need to declare the format of your message, type \"-help\" argument for more"
							<< endl;
					flags_ok = false;
				}
			} else if (strcmp(argv[i], "-k") == 0) {
				//now we check the type of key
				t_key = argv[++i];
				if (t_key == "-s") {
					//now we set the key
					t_key = argv[++i];
					if (t_key.size() != 8) {
						cout << "Key length MUST be 8-chars" << endl;
						flags_ok = false;
					}else{
						key=convertToGroupsOf64bits(t_key,&key_size);
					}
				} else if (t_key == "-b") {
					//now we set the key
					t_key = argv[++i];
					if (t_key.size() != 64) {
						cout << "Key length MUST be 64-bits" << endl;
						flags_ok = false;
					}else{
						key=new std::bitset<64>(t_key);
					}
				} else if (t_key == "-f") {
					//now we set the key
					t_key = argv[++i];
					//create an input-output controller
					io_ctrl = new IOcontroller();
					//read the input and compine it to a string
					std::string compined_input = compineStrVec(
							io_ctrl->readFromFile(t_key));
					//set message
					key = convertToGroupsOf64bits(compined_input,
							&key_size);
					if(key_size!=1){
						cout << "Key length MUST be 8-chars" << endl;
						flags_ok = false;
					}
				} else {
					cout
							<< "You need to declare format of your key, type \"-help\" argument for more"
							<< endl;
					flags_ok = false;
				}
			} else if (strcmp(argv[i], "-p") == 0)	// print log
					{
				print = true;
			} else if (strcmp(argv[i], "-l") == 0)	//save log
					{
				log = true;
			} else if (strcmp(argv[i], "-e") == 0)	//encript
					{
				enc = true;
			} else if (strcmp(argv[i], "-d") == 0)	//decript
					{
				enc = false;
			} else {
				std::cout << "Unknown flag " << argv[i] << endl
						<< "pass -help for help" << endl;
				flags_ok = false;
			}
		}
	}

	//create the object which will do the encryption
	DES *des = new DES(enc);	//true-false encryptor-decryptor

	if (!skip) {
		if (bits_message != nullptr) {
			if (enc) {
				//encrypt or decrypt each 64bitset with the same key (not so secure method)
				for (int i = 0; i < bits_message_size; i++) {
					//encrypt
					bits_message[i] = des->Cipher(bits_message[i], *key);
					//print the output
					std::cout << bits_message[i];
				}
			} else {
				//convert back to the right form and output them to the cyphetext
				std::string output;
				for (int i = 0; i < bits_message_size; i++) {
					bits_message[i] = des->Cipher(bits_message[i], *key);
					for (std::size_t j = 0; j < 8; j++) {
						std::bitset<8> temp;
						for (std::size_t n = 0; n < 8; n++) {
							temp.set(7 - n, bits_message[i][63 - (j * 8 + n)]);
						}
						output.append(1,
								static_cast<char>(std::bitset<8>(temp).to_ulong()));
					}
				}
				//print the output
				std::cout << output << std::endl;
			}
			//if he typed -p print messages
			if (print) {
				des->osc.CoutAll();
			}
			//if he typed -l log messages
			if (log) {
				des->osc.LogSaved("DesEventLog");
			}
		} else {
			std::cout << "You need to enter a key/message correctly" << std::endl;
		}
	}
	return 0;
}

