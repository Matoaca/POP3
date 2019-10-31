#include "Socket.h"
#include <iostream>

using namespace std;

vector<char*> parseMsg(char* msg){
	vector<char*> msgParts;
	char* firstpart;
	char* rest;
	for(int i = 0; i < 4; i++){
		fisrtpart = firstpart + msg[i];
	}
	for(int i = 4; i < msg.size(); i++){
		rest = rest + msg[i];
	}
	msgParts.push_back(fistpart);
	msgParts.push_back(rest);
	
	return msgParts;
}

bool isFoundIn(char* msg, vector<char*>Mailbox){
	for(int i = 0; i < Mailbox.size(); i++){
		if(msg == Mailbox[i])
			return true;
	}
	return false;
}

void authorize(Socket socket){
	char* msg;
	//Read in the USER
	socket.readBytes(&msg, sizeof());
	vector<char*>msgParts = parseMsg(msg);
	if(msgParts[0] == "USER"){
		if(!(isFoundIn(msgParts[1], Mailbox)))
			socket.writeBytes("-ERR Invalid USER", 17);
			return;
	}else{
		socket.writeBytes("-ERR Invalid USER", 17);
		return;
	}
	socket.writeBytes("+OK USER is valid", 17);

	socket.readBytes(&msg, sizeof());
	msgParts = parseMsg(msg);
	if(msgParts[0] != "PASS"){
		if(!(isFoundIn(msgParts[1], Mailbox)))
			socket.writeBytes("-ERR Invalid PASS", 17);
			return;
	}else{
		socket.writeBytes("-ERR Invalid PASS", 17);
		return;
	}
	socket.writeBytes("+OK PASS is valid", 17);
}

void Transaction(Socket socket){
	socket.readBytes(&msg, sizeof());
	vector<char*>msgParts = parseMsg(msg);

	if(msg == "STAT"){}
	else if(msg == "LIST"){}
	else if(msg == "RETR"){}
	else if(msg == "DELE"){}
	else if(msg == "NOOP"){}
	else if(msg == "RSET"){}
	else{}
}

void server(string port){
	vector<Socket> sockets(1);
	sockets[0].listen(port);

	while(true){
		waitForEvent(sockets,-1);
		if(sockets[0].isClosed){
			return;
		}else if(sockets[0].hasData){
			sockets.push_back(sockets[0].accept());
		}

		for(int i = sockets.size()-1; i >= 1; i-=1){
			if(sockets[i].isClosed){
				cout << sockets[i].host << " has left" << endl;
				sockets.erase(sockets.begin()+i);
			}else if(sockets[i].hasData){
				//handle that data
				
				Packet p;
				sockets[i].readBytes(&p, sizeof(Packet));
			}
			sockets[i].writeBytes(&p, sizeof(Packet));
		}
	}
}


void client(string addr, string port){
	Socket s;
	s.open(addr, port);
	
	

}


int main(int argc, char** argv){
	if(argc == 2){
		//port number so this is the server
		server(argv[1]);
	}else if(argc == 3){
		//client
		client(argv[1],argv[2]);
	}
}
