/**********************************************************************
 *
 * Filename:    useful.cpp
 * 
 * Description: Implementations of useful functions
 *
 * Notes:
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include "useful.h"

unsigned long long useful::factorial(int n){
	unsigned long total = 1;
	for(int i = 1; i <= n; i++){
		total *= i;
	}

	return total;
}

//n choose r
unsigned long useful::combination(int n,int k){
	return factorial(n) / (factorial(k) * factorial(n-k));
}

std::vector<std::string> useful::split(std::string &str,char dil){
	std::vector<std::string> split;
	std::string buff = "";

	int begining = 0;
	for(int i = 0; i < str.length(); i++){
		if(str[i] == dil){
			split.push_back(buff);
			buff = "";
		}else{
			buff += str[i];
		}
	}
	split.push_back(buff);

	return split;
}

//FIXME: figure out how to change colors...
void logger::LOG_I(std::string tag,std::string message,bool log){
	if(log){
		std::cout << "\033[1;32m" << tag << ": " << "\033[0m" << message << std::endl;
	}
}

void logger::LOG_W(std::string tag,std::string message,bool log){
	if(log){
		std::cout << "\033[1;33m" << tag << ": " << "\033[0m" << message << std::endl;
	}
}

void logger::LOG_E(std::string tag,std::string message,bool log){
	if(log){
		std::cerr << "\033[0;31m" << tag << ": " << "\033[0m" << message << std::endl;
	}
}
