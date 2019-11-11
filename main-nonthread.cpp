#include "Socket.h"
#include <iostream>

using namespace std;

vector <Mailbox> users;

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
/*
int userNo(string name){
	for(int i = 0; i < users.size(); ++i){
		if(name == users[i].username){
			return i;
		}
	}
	return -1; //error
}*/

int userFound(string msg){ //??
	for(int i = 0; i < users.size(); i++){
		if(msg == users[i].username)
			return i;
	}
	return -1;
}

bool passFound(string msg, int spot){ //??
	if(msg == users[spot].password){
			return true;
	}
	return false;
}

//need to fix
void Authorize(Socket socket){
	//Read in the USER
	string msg = socket.readString();
	Msg msgParts = parseMsg(msg);
	int person;
	if(msgParts.command == "USER"){
		person = userFound(msgParts.message);//find username
		if(person == -1){
			socket.writeString("-ERR Invalid USER", 17);
			return;
		}
	}else{
		socket.writeString("-ERR Invalid USER", 17);
		return;
	}
	socket.writeString("+OK USER is valid", 17);
	
	msg = socket.readString();
	msgParts = parseMsg(msg);
	if(msgParts.command == "PASS"){
		if(!(passFound(msgParts.message, person))){
			socket.writeString("-ERR Invalid PASS", 17);
			return;
		}
	}else{
		socket.writeString("-ERR Invalid PASS", 17);
		return;
	}
	socket.writeString("+OK PASS is valid", 17);
	Transaction(socket, person);
}

//use readString and writeString everywhere
void Transaction(Socket socket, int boxSpot){
	while(1){
		string str = socket.readString();
		Msg msg = parseMsg(str);

		if(msg.command == "STAT"){
			
		}
		else if(msg.command == "LIST"){
			
		}
		else if(msg.command == "RETR"){
		}
		else if(msg.command == "DELE"){
			//Find the message to be deleted
			int num = stoi(msg.messege);
			if(num <= users[boxSpot].messages.size()-1 && num >= 0){
				if(!users[boxSpot].messages[msg.message].toDelete){
					string rv = "+OK message " + msg.message + " deleted";
					socket.writeString(rv);
					//Set the message to be deleted
					users[boxSpot].messages[msg.message].toDelete = true;
				}else{
					string rv = "-ERR message " + msg.message + " already deleted";
					socket.writeString(rv);
				}
			}else{
				string rv = "-ERR message " + msg.message + " not found";
				socket.writeString(rv);
			}
		}
		else if(msg.command == "NOOP"){
			socket.writeString("+OK");
		}
		else if(msg.command == "RSET"){
			//loop the Messages in teh mailbox and reset the toDelete bool to false
			int i;
			int octets = 0;
			for(i = 0; i < users[boxSpot].messages.size(); i++){
				users[boxSpot].messages[i].toDelete = false;
				octets += users[boxSpot].messages[i].message.size();
			}
			string rv = "+OK maildrop has " + i + " messages (" + octets + " octets)";
			socket.writeString(rv);
		}
		else if(msg.command == "QUIT"){
			socket.writeString("+OK");
			break;
		}else{
			
		}
	}
	Update(socket,boxSpot);
}

void Update(Socket socket, int boxSpot){
	//Loop through the Mailbox's messages
	for(int i = users[boxSpot].messages.size()-1; i >= 0; --i){
		//If the message in teh mailbox is to be deleted
		if(users[boxSpot].messages[i].toDelete){
			//Delete it
			users[boxSpot].messages.erase(users[boxSpot].messages.begin()+i);
		}
	}
	string rv;
	if(users[boxSpot].messages.size() > 0){
		rv = "+OK " + users[boxSpot].username + "POP3 server signing off (" users[boxSpot].messages.size() +
		" message(s) left)";
	}else{
		rv = "+OK " + users[boxSpot].username + "POP3 server signing off (maildrop empty)";
	}
	socket.writeString(rv);
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
				Authorize(sockets[i]);
				sockets[i].writeString("pop3 server signing off");
				//string str = sockets[i].readString();
				//do something with it
			}
			//sockets[i].writeString("tell them stuff");
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
