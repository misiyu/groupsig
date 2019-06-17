#ifndef _M_GROUPSIG_S_H_
#define _M_GROUPSIG_S_H_

#include <iostream>
#include "./m_groupsig_c.h"


using std::string ;

class M_Groupsig_S
{
public:
	M_Groupsig_S();
	~M_Groupsig_S();
	string create_group(string group_name) ;
	string join(string group_name , string username);
	string get_all_g();
	string process_cmd(string cmd);

private:
	/* data */
	M_Groupsig_C *mgc;
};

#endif 
