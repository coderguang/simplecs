/**
 *this is some func header
 *create by coderguagn 
 *date 2015/0304
 *
 * */

#ifndef FUNC_H_
#define FUNC_H_

#include <sstream>
#include <iostream>
using namespace std;

//int to string
string IntToStr(int value){
		stringstream ss;
		ss<<value;
		return ss.str();
		}
int StrToInt(string value){
		int number;
		stringstream ss;
		ss<<value;		//string -->stringstream
		ss>>number;		//stringstream-->int
		return number;
}



#endif