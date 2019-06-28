#include "keydb.h"
#include <cstdlib>
#include <cstring>

using namespace std;

KeyDB::KeyDB(){
	int rc = sqlite3_open("./keystore.db", &m_db);
	if(rc != SQLITE_OK){
		cout << "open sqlite3 fail" << endl ;
		exit(1);
	}
}
KeyDB::~KeyDB(){
	sqlite3_close(m_db);
}

	
static int queryCB(void *data,int args_num,char **argv,char **argc){
	//cout << args_num << endl ;
   memcpy(data , argv[0] , strlen(argv[0]));
   return 0;
}

int KeyDB::insert_user(string name , string A){
	string sql = "insert into user (name,A) values (\""+name+"\",\""+A+"\")";
	cout << "insert  :" << sql << endl ;
	char *errMsg ;
	int rs = sqlite3_exec(m_db , sql.data() , 0 , 0 , &errMsg) ;
	if(rs != SQLITE_OK){
		cout << "insert fail " << endl ;
		return 1 ;
	}else{
		cout << "insert ok " << endl ;
	}
	return 0;
}

string KeyDB::get_userbyA(string A) {
	string sql = "select name from user where A=\""+A+"\"";
	char buff[100];
	char *errMsg ;
	sqlite3_exec(m_db , sql.data() , queryCB , (void*)buff , &errMsg );
	string result = buff ;
	return result ;
}
