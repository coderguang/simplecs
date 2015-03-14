/**this is db constant by chenshiguang
include database user,passwd
*/

#ifndef DB_CONSTANT
#define DB_CONSTANT 





#include <stdlib.h>
#include <mysql.h>
#include <string>
using namespace std;

static char* server_args[] = {
	"this program",
	"--datadir=.",
	"--key_buffer_size=32M"
};
static char* server_groups[] = {
	"embedded",
	"server",
	"this_program_SERVER",
	(char*)NULL
};

//MSQL struct 
struct MMYSQL{
	MYSQL *conn;
	int flag;//flag is it free,0 is free,1 is busy 
};
//common settings
const string server="localhost";
const string database = "simplecs";

//conn sum,now all connections max sum is 15
const int REGITMAX=15;
const int LANUCHMAX = 15;
const int SECUREMAX = 15;
const int RESULTMAX = 15;
const int GETRESULTMAX = 15;



//all user and passwd
const string regitUser="regitUser";
const string regitPasswd="regiter";

const string lanuchUser = "lanuchUser";
const string lanuchPasswd = "lanucher";

const string secureUser = "secureUser";
const string securePasswd = "securer";

const string resultUser = "resultUser";
const string resultPasswd = "resulter";

const string getResultUser = "getResultUser";
const string getResultPasswd = "getResulter";




#endif
