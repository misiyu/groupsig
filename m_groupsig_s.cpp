#include <iostream>
#include "m_groupsig_s.h"

using namespace std;

M_Groupsig_S::~M_Groupsig_S(){
	delete(this->mgc);
}

M_Groupsig_S::M_Groupsig_S(){
	this->mgc = new M_Groupsig_C("./keystore");
	int server_sockfd ;
	socklen_t client_sock_len ;
	struct sockaddr_in cli_addr , serv_addr ;
	int port ;

	port = SERV_PORT ;

	server_sockfd = socket(AF_INET, SOCK_STREAM , 0);
	bzero((char*)&serv_addr , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET ;
	//serv_addr.sin_addr.s_addr = inet_addr(BIND_IP);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	while(bind(server_sockfd, (struct sockaddr *)&serv_addr 
				, sizeof(serv_addr)) == -1) ;
	cout << "bind port " << port << " success" << endl ;

	listen(server_sockfd , 10) ;

	while(1){
		client_sock_len = sizeof(cli_addr);		
		int new_sockfd = accept(server_sockfd,(struct sockaddr *)&cli_addr , 
				&client_sock_len);
		cout << " new socket accept " << new_sockfd <<  endl ;
		cout << "client ip : " << inet_ntoa(cli_addr.sin_addr) << endl ;
		cout << "client port : " << ntohs(cli_addr.sin_port) << endl ;
		char buff[BUFF_SIZE];
		bzero(buff , BUFF_SIZE);
		int len = readn(new_sockfd , buff , BUFF_SIZE);
		string cmd = buff ;
		string result = this->process_cmd(cmd);
		memcpy(buff , result.data() , result.length());
		writen(new_sockfd , buff , BUFF_SIZE);
		close(new_sockfd);
	}
}

string M_Groupsig_S::create_group(string group_name) {
	mgc->m_create_g(group_name);
	return "";
}
string M_Groupsig_S::join(string group_name , string username){
	cout << "username = " << username << endl ;
	cout << "groupname = " << group_name << endl ;
	string result = mgc->m_add_member(group_name);
	cout << "=============================================" << endl ;
	cout << result << endl ;
	cout << "=============================================" << endl ;
	return result;
}
string M_Groupsig_S::get_all_g(){

}

string M_Groupsig_S::process_cmd(string cmd){
	Json::Reader reader ;
	Json::Value root ;
	reader.parse(cmd.data() , root);
	cout<<"cmd = \n" << cmd << endl ;
	cout << "recv \n" << root.toStyledString() << endl ;
	string op = root["data"]["command"].asString();
	cout << "op = " << op << endl ;
	//return "";
	if(op == "GenGroup") 
		return this->create_group(root["data"]["groupname"].asString());
	else if(op == "Join") 
		return this->join(root["data"]["groupname"].asString() ,
			root["data"]["real_msg"].asString());
	return "";
}

int main()
{
	M_Groupsig_S mgs ;

	return 0;
}
