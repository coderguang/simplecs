#include <iostream>
#include "../MyDB/dbcpp/DBInterface.h"
#include <string>
using namespace std;
int main(){
	Lanuch lan;
	string a="sg1";
	string p="pass";
	int r=LanuchAccount(a,p,lan);
	
	cout<<"lanuch "<<r<<endl;

}
