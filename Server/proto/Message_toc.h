#ifndef MESSAGE_TOC_H_
#define	MESSAGE_TOC_H_
/**
 *all toc proto base on this class
 *only id and error_code are common
 *all const size are define in toc header,tos don't redefinition
 *author:coderguang
 *date:2014/04/08
 */
#include <stdlib.h>
#include "protoID.h"

class Message_toc{
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
