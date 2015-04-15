#ifndef PERSONDATA_H_
#define PERSONDATA_H_

#include <string>
using namespace std;
//a user Person data in all time after it lanuch and before it exit

class PersonData{
public:
	  static int m_ID;
	  static string m_Name;
	  static string m_lastTime;
	  static string m_LastIP;
	  static int m_HP;	
	  static int m_Eat;
	  static int m_Kill;
	  static int m_Assist;
	  static int m_Harm;
	  static int m_BeHarm;
	  static int m_GunNum;	
	  static int m_NullGun;
	  static int m_KDA;

};


	int PersonData::m_ID=0;
	string PersonData::m_Name=nullptr;
	string PersonData::m_lastTime=nullptr;
	string PersonData::m_LastIP=nullptr;
	int PersonData::m_HP=0;	
	int PersonData::m_Eat=0;
	int PersonData::m_Kill=0;
	int PersonData::m_Assist=0;
	int PersonData::m_Harm=0;
	int PersonData::m_BeHarm=0;
	int PersonData::m_GunNum=0;	
	int PersonData::m_NullGun=0;
	int PersonData::m_KDA=0;



#endif
