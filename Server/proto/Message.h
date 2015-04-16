#ifndef MESSAGE_H_
#define	MESSAGE_H_
/**
 *all Message proto base on this class
 *only id and error_code are common
 *author:coderguang
 *date:2014/04/08
 */
#include <stdlib.h>
#include "protoID.h"

#pragma pack(1)
//#pragma pack(PACKSIZE)
//
class Message{
public:
	int id;
	int error_code;
	
	int GetID()const{
		return id;
	}
	int GetError_code(){
		return error_code;
	}
};


#endif
