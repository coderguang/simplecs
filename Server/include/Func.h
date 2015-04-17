#ifndef M_FUNC_H_
#define M_FUNC_H_

/**
 *this is some func header
 *create by coderguagn 
 *date 2015/0304
 *
 * */

#include <sstream>
#include <iostream>
#include <ctime>
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

//get the time now
string GetTimeNow(){
		char *s;
		time_t now;
		time(&now);
		s=ctime(&now);
		string t=s;
		return t;	
}

void DelayTime(double sec){
	time_t start_time,cur_time;
	time(&start_time);
	do{
			time(&cur_time);
	}while((cur_time-start_time<sec));

}


#endif
