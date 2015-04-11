#ifndef Lanuch_TOC_h
#define Lanuch_TOC_h_
#include "Message_toc.h"

//the accounts and passwd length ,decide on database
static const int ACCOUNTSIZE=8;
static const int PASSWDSIZE=16;
class Lanuch_toc:public Message_toc
{
	public:
		char account[ACCOUNTSIZE];
		char passwd[PASSWDSIZE];

		Lanuch_toc(){
		}

};


#endif
