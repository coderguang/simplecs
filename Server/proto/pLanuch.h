#ifndef pLanuch_h_
#define pLanuch_h_
#include "Message.h"

//the accounts and passwd length ,decide on database
static const int ACCOUNTSIZE=8;
static const int PASSWDSIZE=10;
class pLanuch:public Message
{
	public:
		char account[ACCOUNTSIZE];
		char passwd[PASSWDSIZE];

		pLanuch(){
			id=pLanuchID;
		}

};


#endif
