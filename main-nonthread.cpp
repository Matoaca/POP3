#include "Socket.h"
#include <iostream>

using namespace std;

//put into struct instead of vector
Msg parseMsg(string msg){
	string firstpart;
	string rest;
	for(int i = 0; i < 4; i++){
		fisrtpart = firstpart + msg[i];
	}
	for(int i = 5; i < msg.size(); i++){
		rest = rest + msg[i]; 
	}
	Msg msg;
	msg.command = fistpart;
	msg.message = rest;
	
	return msg;
}

bool isFoundIn(char* msg, vector<char*>Mailbox){
	for(int i = 0; i < Mailbox.size(); i++){
		if(msg == Mailbox[i])
			return true;
	}
	return false;
}

//need to fix
void authorize(Socket socket){
	//Read in the USER
	string msg = socket.readString();//read until \r\n, change in readBytes
	Msg msgParts = parseMsg(msg);
	if(msgParts.command == "USER"){
		if(!(isFoundIn(msgParts.message, Mailbox)))
			socket.writeString("-ERR Invalid USER", 17);
			return;
	}else{
		socket.writeString("-ERR Invalid USER", 17);
		return;
	}
	socket.writeString("+OK USER is valid", 17);

	msg = socket.readString();
	msgParts = parseMsg(msg);
	if(msgParts.command == "PASS"){
		if(!(isFoundIn(msgParts.message, Mailbox)))
			socket.writeString("-ERR Invalid PASS", 17);
			return;
	}else{
		socket.writeString("-ERR Invalid PASS", 17);
		return;
	}
	socket.writeString("+OK PASS is valid", 17);
}

//use readString and writeString everywhere
void Transaction(Socket socket){
	string str = socket.readString();
	Msg msg = parseMsg(str);

	if(msg.command == "STAT"){}
	else if(msg.command == "LIST"){}
	else if(msg.command == "RETR"){}
	else if(msg.command == "DELE"){}
	else if(msg.command == "NOOP"){}
	else if(msg.command == "RSET"){}
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
				
				string str = sockets[i].readString();
				//do something with it
			}
			sockets[i].writeString("tell them stuff");
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
