/*
	Dawson Dauphinais
	CS228 Network Programming
	Date Last Modified: 03/21/2020

	This program is a basic web server
*/

#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <netinet/in.h> // struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <arpa/inet.h>

using namespace std;

const int BUFSIZE = 10240;
string current_date();
string current_time();
string zone_offset();

int MakeServerSocket(const char *port)
{
	const int MAXNAMELEN = 255;
	const int BACKLOG = 3;
	char localhostname[MAXNAMELEN]; // local host name
	int s;
	int len;
	struct sockaddr_in sa;
	struct hostent *hp;
	struct servent *sp;
	int portnum;
	int ret;
	hp = gethostbyname("198.110.204.9");
	sscanf(port, "%d", &portnum);
	if (portnum == 0)
	{
		sp = getservbyname(port, "tcp");
		portnum = ntohs(sp->s_port);
	}
	sa.sin_port = htons(portnum);

	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);

	ret = bind(s, (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0)
		perror("Bad");
	listen(s, BACKLOG);
	cout << "Waiting for connection on port " << port << endl;
	return s;
}
/*returns a string containing the day, mon, and year -> 01/MON/2020 */
string current_date()
{
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d/%b/%Y", &tstruct);
	return buf;
}
/*returns a string containing the correct hours, minutes, and seconds*/
string current_time()
{
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), ":%H:%M:%S", &tstruct);
	return buf;
}
/*returns a string containing the timezone offset*/
string zone_offset()
{
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), " %z ", &tstruct);
	return buf;
}
/*generates a log file using the correct IP address, request from the browser, the status code, and the number of bytes requested*/
void generateLog(char add[], string request, string statusCode, int numBytes)
{
	string timeInfo = current_date() + current_time() + zone_offset(); // create a string containing the exact time
	fstream out;
	string client(add);
	string log = client + " - -" + timeInfo + request + statusCode + to_string(numBytes) + "\n";
	out.open("access_logs.txt", ios::app);
	out << log;
	out.close(); //close file when done
}
/*assigns the proper file type for use by the header*/
string getFileType(string s)
{
	string ext = s.substr(s.find('.'));
	if (ext == ".jpg")
	{
		return "image/jpeg";
	}
	else if (ext == ".gif")
	{
		return "image/gif";
	}
	else if (ext == ".html")
	{
		return "text/html";
	}
	else if (ext == ".txt")
	{
		return "text/plain";
	}
	else
	{
		return "application/binary-data";
	}
}
/*pulls the name of the file from the buffer*/
string getFileName(char s[])
{
	string file = "";
	int count = 5;
	do
	{
		file += s[count];
		count++;
	} while (!isspace(s[count]));
	return file;
}
/*generates a header using the filename and the status code*/
string generateHeader(string filename, string statusCode)
{
	string ver = "HTTP/1.0 "; // version will be corrected in the log file, just a placeholder
	string contentType = getFileType(filename);
	string header = ver + statusCode + "Content-type: " + contentType + "\n\n";
	return header;
}
/*returns a string containing the request from the browser. takes in the buffer containing what was received*/
string getRequest(char s[])
{
	string req = "";
	int count = 0;
	while (s[count] != 10 && s[count] != 13)
	{
		req += s[count];
		if (count == 2 && req != "GET")
		{ // verifies that the first three characters of the request are "GET"
			cout << "INVALID REQUEST" << endl;
			exit(0);
		}
		count++;
	}
	return req;
}
main(int argc, char *argv[])
{

	string statusCode = "";
	int s = MakeServerSocket(argv[1]);
	struct sockaddr_in sa;
	int sa_len = sizeof(sa);

	while (true)
	{

		char buf[10240];
		int rlen;
		int fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len);
		int r = read(fd, buf, BUFSIZE); // read in the request
		buf[r] = 0;
		int numBytes = 0;

		/*referenced stack overflow for the following four lines of code*/
		struct sockaddr_in *pV4Addr = (struct sockaddr_in *)&sa;
		struct in_addr ipAddr = pV4Addr->sin_addr;
		char clientAdd[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &ipAddr, clientAdd, INET_ADDRSTRLEN);

		string filename = getFileName(buf);
		assert(fd != -1);
		int file = open(filename.c_str(), O_RDONLY);
		statusCode = " 200 ";

		/*Ben Basten helped me with the following four lines of code*/
		if (file < 0)
		{
			statusCode = " 404 ";
			filename = "errorPage.html";
			file = open(filename.c_str(), O_RDONLY);
		}

		assert(file >= 0);
		string request = getRequest(buf);
		string header = generateHeader(filename, statusCode);
		int wlen = write(fd, header.c_str(), header.length());
		do
		{
			rlen = read(file, buf, 23);
			numBytes += rlen;
			buf[rlen] = 0;
			assert(rlen >= 0);
			wlen = write(fd, buf, rlen);
			assert(wlen == rlen);
			if (rlen == 0)
				break;
		} while (rlen != 0);
		generateLog(clientAdd, request, statusCode, numBytes); // create and document a log file
		close(fd);
		close(file);
	}
}
