#include <iostream>
#include "./algorithm/GroupSig.h"

using namespace std;
using namespace GroupSigApi;

int main()
{
	string result ;
	string algorithm_method = "bbs04" ;
	create_group_default(result , algorithm_method);
	cout << result << endl ;
	cout <<"Hello world!" << endl;

	return 0;
}
