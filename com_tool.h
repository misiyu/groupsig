#ifndef _COM_TOOL_H_
#define _COM_TOOL_H_

#include <iostream>
#include <fstream>
#include <sstream>
using std::string ;

static string file2string(string filepath){
	std::fstream fs(filepath.data());
	stringstream ss ;
	ss << fs.rdbuf();
	return ss.str();
}

static int string2file(string str , string filepath){
	std::ofstream fs(filepath.data());
	fs << str ;
	fs.close();
	return 0 ;
}

#endif 
