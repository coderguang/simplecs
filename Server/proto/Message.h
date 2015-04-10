#ifndef MESSAGE_H_
#define	MESSAGE_H_
/**
 *all proto base on this class
 *only id is common
 *author:coderguang
 *date:2014/04/08
 */
#include <stdlib.h>
#include "protoID.h"

class Message{
public:
	int id;
	
	int GetID()const{
		return id;
	}
};


#endif
