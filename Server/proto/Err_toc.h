#ifndef ERR_TOC_H_
#define ERR_TOC_H_
#include "Message.h"
/**
 *this is all the Error_code
 *the error_code use this header to instead all proto err_code
 *it only has id and error_code
 */

//accounts errocode from DBErr.h in  simplecs/Server/MyDB/dbcpp/DBErr.h
//
//
static const int SERVER_FULL=5888; //server is full!
static const int ACCOUNT_HADREGIT=6000;//use for regit accounts
static const int ACCOUNT_ERR_IDENTITY=6100;//use for forget the passwd to reset the passwd


static const int ACCOUNT_ERR_PASSWD=6200;//use for lanuch when passwd no matching the account
static const int ACCOUNT_HAD_LANUCH=6300;//the account is lanuch and using now

static const int SERVER_IN_GAME=6600;//game is running,the game status is 2

#pragma pack(1)
//#pragma pack(PACKSIZE)
class Err_toc:public Message{
public:
		Err_toc(int errcode){
			id=3999;//this is the err_toc id
			error_code=errcode;
		}

};





#endif
