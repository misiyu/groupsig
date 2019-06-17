#include <iostream>
#include "./m_groupsig_c.h"

using namespace std;

void parse_arg(int argc,char **args , string &cmd , string &group_name , 
		string &msg , string &sig){
	//cout << args[0] << endl ;
	//cout << args[1] << endl ;
	//cout << args[2] << endl ;
	//cout << args[3] << endl ;
	//cout << args[4] << endl ;
	if(argc < 3 ){
		cout << "Usag : ./gsc -(g|a|s|v|o|j) <group_name> <msg> <sig>\n" ;
		exit(1);
	}
	cmd = args[1];
	group_name = args[2];
	if(argc >= 4) msg = args[3];
	if(argc >= 5) sig = args[4];
}
int main(int argc , char ** args)
{
	M_Groupsig_C mgc("./keystore");
	string cmd ;
	string group_name ;
	string sig ;
	string msg ;
	parse_arg(argc , args , cmd , group_name , msg , sig);
	string result="" ;
	if(cmd == "-g"){
		mgc.m_create_g(group_name);
	}else if(cmd == "-a"){
		result = mgc.m_add_member(group_name);
		string2file(result , "./pipefile");
	}else if(cmd == "-s"){
		result = mgc.m_group_sig(group_name,msg);
		//result = mgc.m_group_sig("group0" , "/hello/1.txt");
		string2file(result,"./pipefile");
		cout << "=======================================================" << endl;
		cout << group_name << endl ;
		cout << msg << endl ;
		cout << result << endl ;
		cout << "sig " << endl ;
		cout << "=======================================================" << endl;
	}else if(cmd == "-v"){
		bool ret = mgc.m_verify( group_name,result , msg);
	}else if(cmd == "-o"){
		string A = mgc.m_open_sig(group_name,result,msg);
	}else if(cmd =="-j"){
		string gsk = mgc.m_join_request(group_name , msg);
		if(gsk != ""){
			cout << "ok" << endl ;
		}else{
			cout << "err" << endl;
		}
		//cout << "get gsk = \n" << gsk << endl ;
	}else {
		cout << "Usag : ./gsc -(g|a|s|v|o) <group_name> <sig> <msg>\n" ;
		exit(1);
	}

	//mgc.m_create_g("group0");
	//result = mgc.m_add_member("group0");
	//cout << "=========================================================" << endl;
	//cout << result << endl ;
	//cout << "=========================================================" << endl;
	//result = mgc.m_group_sig("group0" , "/hello/1.txt");
	//cout << "=========================================================" << endl;
	//cout << result << endl ;
	//cout << "=========================================================" << endl;

	//bool ret = mgc.m_verify("group0",result , "/hello/1.txt");

	//cout << "=========================================================" << endl;
	//cout << ret << endl ;
	//cout << "=========================================================" << endl;

	//string A = mgc.m_open_sig("group0",result,"/hello/1.txt");
	//cout << "=========================================================" << endl;
	//cout << A << endl ;
	//cout << "=========================================================" << endl;
	
	cout << argc << endl ;

	return 0;
}
