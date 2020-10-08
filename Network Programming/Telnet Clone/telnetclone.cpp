/*

Dawson Dauphinais
CS228, Network Programming 
Date Last Modified: 03/31/2020

The purpose of this program is to create a telnet clone that implements poll()

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
#include <poll.h>
#include <algorithm>

using namespace std;

const int BUFSIZE = 102400;

/*checks for connection errors, prints the error.*/
void ErrorCheck(bool condition, const char *msg)
{
    if (condition)
    {
        perror(msg);
        exit(1);
    }
}

/*create a socket to the server*/
int MakeSocket(char *host, char *port)
{
    int s;
    int len;
    struct sockaddr_in sa;
    struct hostent *hp;
    struct servent *sp;
    int portnum;
    int ret;

    hp = gethostbyname(host);
    ErrorCheck(hp == 0, "Gethostbyname");
    bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
    sa.sin_family = hp->h_addrtype;
    sscanf(port, "%d", &portnum);
    if (portnum > 0)
    {
        sa.sin_port = htons(portnum);
    }
    else
    {
        sp = getservbyname(port, "tcp");
        portnum = sp->s_port;
        sa.sin_port = sp->s_port;
    }
    s = socket(hp->h_addrtype, SOCK_STREAM, 0);
    ErrorCheck(s == -1, "Could not make socket");
    ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
    ErrorCheck(ret == -1, "Could not connect");
    return s;
}

main(int argc, char *argv[])
{
    char buf[BUFSIZE];
    int sock = MakeSocket(argv[1], argv[2]);
    if (sock < 0)
    {
        cout << "Error opening socket! Disconnecting..." << endl;
        exit(0);
    }
    struct pollfd fds[2];
    int timeout = -1;
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[1].fd = sock;
    fds[1].events = POLLIN;
    int r;
    while (1)
    {
        string s = "";
        int result = poll(fds, 2, timeout);
        if (result == -1)
        {
            perror("poll");
            exit(1);
        }
        if (!result)
        {
            printf("Timeout.\n");
            exit(1);
        }
        if (fds[0].revents & POLLIN)
        {
            // read from keyboard (getline);
            // send it to server
            getline(cin, s);
            int w = write(sock, s.c_str(), s.length() + 2);
            if (w <= 0)
            {
                cout << "Error Writing! Exiting." << endl;
                exit(0);
            }
        }
        if (fds[1].revents & POLLIN)
        {
            // read from server
            // print it
            r = read(sock, buf, BUFSIZE - 1);
            if (r <= 0)
            {
                perror("error reading.");
                exit(0);
            }
            buf[r] = 0;
            cout << buf << endl;
        }
    }
    return 0;
}