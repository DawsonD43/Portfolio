/*
Dawson Dauphinais
CS228 
Date Last Modified: 02/06/2020
*/

#include <iostream>		
#include <stdio.h>	
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <algorithm>
using namespace std;

const int BUFSIZE=102400;

void ErrorCheck(bool condition, const char *msg)
{
	if (condition)
	{
		perror(msg);
		exit(1);
	}
}

int MakeSocket(const char *host, const char *port) {
	int s; 			
	int len;	
	struct sockaddr_in sa; 
	struct hostent *hp;
	struct servent *sp;
	int portnum;	
	int ret;

	hp = gethostbyname(host);
	ErrorCheck(hp==0, "Gethostbyname");
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sscanf(port, "%d", &portnum);
	if (portnum > 0) {
		sa.sin_port = htons(portnum);
	}
	else {
		sp=getservbyname(port, "tcp");
		portnum = sp->s_port;
		sa.sin_port = sp->s_port;
	}
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	ErrorCheck(s == -1, "Could not make socket");
	ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
	ErrorCheck(ret == -1, "Could not connect");
	return s;
}

void recAndSend(int sock, char buf[], string data){

	int r = read(sock, buf, BUFSIZE - 1);
	if(r == -1 || r == 0){
		perror("Error Reading!");
		exit(1);
	}
	buf[r] = 0;
	cout << buf << endl;
	int x = buf[0];
	if(x!='2'){
		perror("Error");
		exit(1);
	}else{
		int w = write(sock, data.c_str(), data.length());
		if(w<=0){
			perror("Error Writing");
			exit(1);
		}
	}
}

main(int argc, char *argv[]) {

	char buf[BUFSIZE];
	
    string sender;
	string id;
	string recip;
	string message;
	string junk = " ";

	char serv[BUFSIZE];

	cout << "Who are you?" << endl;
	cin >> id;

    cout << "Send to Whom? " << endl;
    cin >> recip;

    cout << "At what SMTP Server?" << endl;
    cin >> serv;

    cout << "From what person?" << endl;
	cin >> sender;

    cout << "Enter the message. End that message with a '.' on a line by itself." << endl;
	while(junk != "."){
		cin >> junk;
		message = message + junk + "\r\n";
	}

	int sock = MakeSocket(serv, "25");
	recAndSend(sock, buf, ("HELO " + id + "\r\n"));
	recAndSend(sock, buf, ("MAIL FROM: " + sender + "\r\n"));
	recAndSend(sock, buf, ("RCPT TO: " + recip + "\r\n"));
	recAndSend(sock, buf, ("DATA \r\n" + message + "\r\n"));
	//recAndSend(sock, buf, ("\n.\n"));
    
    return 0;
}