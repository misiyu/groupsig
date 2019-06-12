#include <iostream>
#include "./m_groupsig_c.h"

using namespace std;

int main()
{
	M_Groupsig_C mgc("./keystore");
	//mgc.m_create_g("group0");
	string result="" ;
	//result = mgc.m_add_member("group0");
	cout << "===========================================================" << endl;
	cout << result << endl ;
	cout << "===========================================================" << endl;
	result = mgc.m_group_sig("group0" , "/hello/1.txt");
	cout << "===========================================================" << endl;
	cout << result << endl ;
	cout << "===========================================================" << endl;

	bool ret = mgc.m_verify("group0",result , "/hello/1.txt");

	cout << "===========================================================" << endl;
	cout << ret << endl ;
	cout << "===========================================================" << endl;

	string A = mgc.m_open_sig("group0",result,"/hello/1.txt");
	cout << "===========================================================" << endl;
	cout << A << endl ;
	cout << "===========================================================" << endl;

	return 0;
}
