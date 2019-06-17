#ifndef _M_GROUPSIG_C_H_
#define _M_GROUPSIG_C_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "./algorithm/GroupSig.h"
//#include "GroupSig.h"
#include "com_tool.h"

using std::string ;
using std::cout ;
using std::endl ;

class M_Groupsig_C
{
public:
	M_Groupsig_C(string key_dir);
	~M_Groupsig_C();
	void load_key(string group_name);
	string load_key(string group_name , string file_name);
	void store_key(string group_name);
	void store_key(string group_name , string file_name, string str);

	void m_create_g(string group_name);
	string m_add_member(string group_name);
	string m_join_request(string group_name , string id_m);
	string m_group_sig(string group_name , string msg);
	bool m_verify(string group_name ,string sig , string msg);
	string m_open_sig(string group_name ,string sig , string msg);

private:
	string m_key_dir ;
	const string algorithm_method = "bbs04" ;
	const string pbc_param_str = "{\"linear_type\":\"f\", \"bit_len\": 128}" ;

	string m_gpk;
	string m_gsk;
	string m_gmsk ;
	string m_gamma ;
	string m_pbc_param ;
};

#endif 
