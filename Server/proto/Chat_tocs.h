#ifndef CHAT_TOCS_H_
#define CHAT_TOCS_H_

#include "Message.h"
#include "ProtoID.h"
#include <string.h>

using namespace std;
static const int MAX_CHAT_SIZE=32;

#pragma pack(1)
class Chat_tocs:public Message{

public:
		int user_id;//who send this chat
		int type;//the party
		char msg[MAX_CHAT_SIZE];
		
		Chat_tocs(){
			id=pChatID;
			error_code=0;
		}
		
		Chat_tocs(int uid,int t,string ms){
			id=pChatID;
			error_code=0;
			user_id=uid;
			type=t;
			memcpy(msg,ms.c_str(),ms.length()+1);

		}



};


#endif
