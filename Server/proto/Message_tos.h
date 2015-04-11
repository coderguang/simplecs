#ifndef MESSAGE_TOS_H_
#define	MESSAGE_TOS_H_
/**
 *all tos proto base on this class
 *only error_code is common
 *author:coderguang
 *date:2014/04/08
 */
#include <stdlib.h>
#include "protoID.h"

class Message_tos{
public:
	int error_code;
	
	int GetError_code(){
		return error_code;
	}
};


#endif
