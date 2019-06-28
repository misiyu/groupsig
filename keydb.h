#ifndef _KEYDB_H_
#define _KEYDB_H_

#include <iostream>
#include <sqlite3.h>

using std::string ;

class KeyDB
{
public:
	KeyDB();
	~KeyDB();
	int insert_user(string name , string A);
	string get_userbyA(string A);

private:
	sqlite3 *m_db ;

};

#endif 
