#include "OutputStreamController.h"

/**
 * constructor for OutputStreamController object
 */
OutputStreamController::OutputStreamController(bool state,bool keep) {
	time = clock();
	active=state;
	save=keep;
}

/**
 * constructor for OutputStreamController object
 */
OutputStreamController::OutputStreamController() {
	time = clock();
	active=true;
	save=true;
}

/**
 * copy constructor for OutputStreamController object
 */
OutputStreamController::OutputStreamController(const OutputStreamController& obj) {
	time=obj.time;
	active=obj.active;
	save=obj.save;
}

/**
 * destructor for OutputStreamController object
 */
OutputStreamController::~OutputStreamController() {

}

void OutputStreamController::Cout(string str){
	string tmp=std::to_string(((float) (clock() - time)) / CLOCKS_PER_SEC)+":: "+str;
	if(active){
		std::cout<<tmp<<std::endl;
	}
	if(save){
		output.push_back(tmp);
	}
}

void OutputStreamController::CoutAll(){
//	std::cout<<(((float) (clock() - time)) / CLOCKS_PER_SEC)<<":: "<<"Started printing events"<<std::endl;
	Cout("Started printing events");
	for (auto i = output.begin(); i != output.end(); ++i){
    	string tmp= *i;
		std::cout<<tmp<<std::endl;
	}
	Cout("Finished printing events");
	std::cout<<output[output.size()-1]<<std::endl;
}

void OutputStreamController::LogSaved(string log_file_name){
	ofstream log_file;
	log_file.open(log_file_name+".log");
	Cout("Started writing events to the log File");
//	log_file<<(((float) (clock() - time)) / CLOCKS_PER_SEC)<<":: "<<"Started writing events to the log File"<<std::endl;

	for (auto i = output.begin(); i != output.end(); ++i){
    	string tmp= *i;
    	log_file<<tmp<<std::endl;
	}
	Cout("Finished writing events to the log File");
	log_file<<(((float) (clock() - time)) / CLOCKS_PER_SEC)<<":: "<<"Finished writing events to the log File"<<std::endl;
	log_file.close();
}
