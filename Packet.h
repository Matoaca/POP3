#include <iostream>
#include <vector>

struct Address{
	int port;
	char host[64];
};

struct Msg{
    string command
    string message;
};

//create user struct
struct Mailbox{
	string username;
	string password;
	bool toDelete;
	vector <string> messages;
};


