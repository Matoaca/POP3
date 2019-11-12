#include <iostream>
#include "Socket.h"

struct Address{
	int port;
	char host[64];
};

struct Msg{
    string cmd;
    string message;
};

struct Mail{
	string message;
	bool toDelete;
};

//create user struct
struct Mailbox{
	string username;
	string password;
	vector <Mail> messages;
};


