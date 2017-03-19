#ifndef OUTPUTSTREAMCONTROLLER_H_
#define OUTPUTSTREAMCONTROLLER_H_

#include <iostream>
using std::cout;
using std::cerr;

using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iterator>
using std::istream_iterator;
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <fstream>
using std::ofstream;

class OutputStreamController {
	clock_t time;
	bool active;
	bool save;
	vector<string> output;
public:
	OutputStreamController();
	OutputStreamController(bool,bool);
	virtual ~OutputStreamController();
	void Cout(string);
	void CoutAll();
	void LogSaved(string);
};

#endif /* OUTPUTSTREAMCONTROLLER_H_ */
