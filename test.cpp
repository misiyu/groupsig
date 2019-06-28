#include <iostream>
#include "keydb.h"

using namespace std;

int main()
{
	KeyDB keydb ;
	keydb.insert_user("hell" , "dafkjdksajfkdjsakfjdksajfkd");

	cout << keydb.get_userbyA( "dafkjdksajfkdjsakfjdksajfkd") << endl ;
	return 0;
}
