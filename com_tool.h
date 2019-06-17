#ifndef _COM_TOOL_H_
#define _COM_TOOL_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <jsoncpp/json/json.h>
using std::string ;

#define SERV_PORT 9780
#define BUFF_SIZE 4000

static string file2string(string filepath){
	std::fstream fs(filepath.data());
	stringstream ss ;
	ss << fs.rdbuf();
	return ss.str();
}

static int string2file(string str , string filepath){
	std::ofstream fs(filepath.data());
	fs << str ;
	fs.close();
	return 0 ;
}

static ssize_t readn(int fd, char *buf, int n){
    size_t nleft = n; //还需要读取的字节数
    char *bufptr = buf; //指向read函数当前存放数据的位置
    ssize_t  nread;
    while(nleft > 0){
        if((nread = read(fd, bufptr, n)) < 0){
            if(errno == EINTR){ //遇到中断
                continue;
            }
            else            // 其他错误
                return -1;
        }
        else if(nread == 0){ // 遇到EOF
            break;
        }
 
        nleft -= nread;
        bufptr += nread;
    }
    return (n - nleft);
}
static ssize_t writen(int fd, const char *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = vptr;
	nleft = n;
	while (nleft > 0){
		if ( (nwritten = write(fd, ptr, nleft)) <= 0){
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0; //
			else 
				return -1; // error
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}

static string send_recv(string message){

	string gs_ip = file2string("./groupserverip.conf") ;
	if(gs_ip == ""){
		cout << "err gs_ip : " << gs_ip << endl ;
		return "" ;
	}
	int sockfd ;
	struct sockaddr_in server_addr ;
	int port = SERV_PORT ;
	bzero(&server_addr , sizeof(server_addr));
	server_addr.sin_family = AF_INET ;
	server_addr.sin_addr.s_addr = inet_addr(gs_ip.data());
	server_addr.sin_port = htons(port);

	sockfd = socket(AF_INET , SOCK_STREAM , 0 );
	connect(sockfd , (struct sockaddr *)&server_addr , sizeof(server_addr));
	char buff[BUFF_SIZE];
	memcpy(buff , message.data(), message.length());
	writen(sockfd , buff , BUFF_SIZE);
	bzero(buff , BUFF_SIZE);
	readn(sockfd , buff , BUFF_SIZE);
	close(sockfd);
	string result = buff ;
	return result ;
}

#endif 
