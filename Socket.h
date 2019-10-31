#ifndef SOCKET__H
#define SOCKET__H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/poll.h>
#include <netdb.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
//#include "Packet.h"

using namespace std;

struct Socket{
	int fd;
	string host;
	string port;
	bool isClosed = false;
	bool hasData = false;

	void open(string host,string porto);
	void close();

	Socket accept();
	void listen(string porto);
	string toString();

	string readString();
	void writeString(string str);

	void readBytes(void* bytes, int len);
	void writeBytes(void* bytes, int len);

};

void waitForEvent(vector<Socket>& sockets,int timeout);



#endif
