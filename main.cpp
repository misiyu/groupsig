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
		cout << "Usag : generate a group : ./gsc -g <group_name> \n" ;
		cout << "Usag : get a member key : ./gsc -a <group_name> \n" ;
		cout << "Usag : sign a message : ./gsc -s <group_name> messsage\n" ;
		cout << "Usag : verify a signatrue : ./gsc -v <group_name> messsage\
			sig\n" ;
		cout << "Usag : join a group : ./gsc -j <group_name> <username>\n" ;
		cout << "Usag : open a signatrue : ./gsc -o <group_name> messsage\
			sig\n" ;

		exit(1);
	}
	cmd = args[1];
	group_name = args[2];
	if(cmd == "-j" && argc < 4){
		cout << "Usag : join a group : ./gsc -j <group_name> <username>\n" ;
	}else if(cmd == "-s" && argc < 4){
		cout << "Usag : sign a message : ./gsc -s <group_name> messsage\n" ;
	}
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
		bool ret = mgc.m_verify( group_name,sig , msg);
		cout << "=======================================================" << endl;
		cout << "verify ret = " << ret << endl ;
		cout << "=======================================================" << endl;
		string2file(to_string(ret),"./pipefile");
	}else if(cmd == "-o"){
		//string A = mgc.m_open_sig(group_name,sig,msg);
		string username = mgc.m_opensig_request(group_name , sig , msg);
		cout << username << endl ;
		string2file(username,"./pipefile");
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


	
	cout << argc << endl ;

	return 0;
}
