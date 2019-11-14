#include <sstream>
#include "Packet.h"

using namespace std;

Msg parseMsg(string str);
int userFound(string msg);
bool passFound(string msg);
int Authorize(Socket socket);
void Transaction(Socket socket, int boxSpot);
void Update(Socket socket, int boxSpot);

vector <Mailbox> users;

#include "Populate.h"


Msg parseMsg(string str){
	string firstpart;
	string rest;
	for(int i = 0; i < 4; i++){
		firstpart = firstpart + (char)toupper((int)str[i]);
	}
	if(str.size() > 5){
		for(int i = 5; i < str.size(); i++){
			rest = rest + str[i]; 
		}
	}else{
		rest = "";
	}
	Msg msg;
	msg.cmd = firstpart;
	msg.message = rest;

	return msg;
}

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

int Authorize(Socket socket){
	//Read in the USER
	cout << "authenticating user" << endl;
	string msg = socket.readString();
	Msg msgParts = parseMsg(msg);
	int person;

	if(msgParts.cmd == "QUIT"){
		socket.writeString("+OK POP3 server signing off");
		cout << "exiting" << endl;
		return -1;
	}else if(msgParts.cmd == "USER"){
		person = userFound(msgParts.message);//find username
		if(person == -1){
			socket.writeString("-ERR Invalid USER");
			cout << "exiting" << endl;
			return -1;
		}
	}else{
		socket.writeString("-ERR Invalid command");
		cout << "exiting" << endl;
		return -1;
	}
	socket.writeString("+OK USER is valid");

	msg = socket.readString();
	msgParts = parseMsg(msg);
	if(msgParts.cmd == "QUIT"){
		socket.writeString("+OK POP3 server signing off");
		cout << "exiting" << endl;
		return -1;
	}else if(msgParts.cmd == "PASS"){
		if(!(passFound(msgParts.message, person))){
			socket.writeString("-ERR Invalid PASS");
			cout << "exiting" << endl;
			return -1;
		}
	}else{
		socket.writeString("-ERR Invalid command");
		cout << "exiting" << endl;
		return -1;
	}
	socket.writeString("+OK PASS is valid");
	cout << "user authenticated" << endl;
	//Transaction(socket, person);
	return person;
}

//use readString and writeString everywhere
void Transaction(Socket socket, int boxSpot){
	cout << "in transaction state" << endl;
	while(1){
		string str = socket.readString();
		Msg msg = parseMsg(str);
		stringstream rv;

		cout << msg.cmd << endl;

		if(msg.cmd == "STAT"){
			int octets = 0;
			int size = 0;
			rv << "+OK ";
			for(int i = 0; i < users[boxSpot].messages.size(); i++){
				if(!(users[boxSpot].messages[i].toDelete)){
					octets = octets + users[boxSpot].messages[i].message.size();
					++size;
				}
			}
			cout << size << endl;
			rv << size << " " << octets;
			socket.writeString(rv.str());
		}
		else if(msg.cmd == "LIST"){
			int num = 0;
			if(msg.message == ""){
				num = -1;
			}else{
				num = stoi(msg.message);
			}
			if(num == -1){
				int octets = 0;
				rv << "+OK ";
				int size = 0;
				for(int i = 0; i < users[boxSpot].messages.size(); i++){
					if(!(users[boxSpot].messages[i].toDelete)){
						octets = octets + users[boxSpot].messages[i].message.size();
						++size;
					}
				}
				rv << size << " messages (" << octets << " octets)";
				socket.writeString(rv.str());


				for(int i = 0; i < users[boxSpot].messages.size(); i++){
					if(!(users[boxSpot].messages[i].toDelete)){
						stringstream strstr;
						strstr << (i+1) << " " << users[boxSpot].messages[i].message.size();
						socket.writeString(strstr.str());
					}
				}
				socket.writeString(".");
			}else if((num <= users[boxSpot].messages.size()) && (num >= 1) && (!(users[boxSpot].messages[num-1].toDelete))){
				rv << "+OK " << msg.message << " " << users[boxSpot].messages[num-1].message.size();
				socket.writeString(rv.str());
			}else{
				rv << "-ERR no such message, only " << users[boxSpot].messages.size() << " messages in maildrop";
				socket.writeString(rv.str());
			}
		}
		else if(msg.cmd == "RETR"){
			int num = 0;
			if(msg.message == ""){
				socket.writeString("-ERR no message number");
				socket.writeString(".");
				continue;
			}else{
				num = stoi(msg.message);
			}
			if(num <= users[boxSpot].messages.size() && num >= 1 && !(users[boxSpot].messages[num-1].toDelete)){
				rv << "+OK " << users[boxSpot].messages[num-1].message.size() << " octets";
				socket.writeString(rv.str());
				
				if(users[boxSpot].messages[num-1].message == "."){
					string str = "..";
					socket.writeString(str);
				}
				else{
					socket.writeString(users[boxSpot].messages[num-1].message);
				}
				socket.writeString(".");
			}else{
				rv << "-ERR no such message";
				socket.writeString(rv.str());
				socket.writeString(".");
			}
		}
		else if(msg.cmd == "DELE"){
			//Find the message to be deleted
			int num = 0;
			if(msg.message == ""){
				socket.writeString("-ERR no message number");
				continue;
			}else{
				num = stoi(msg.message);
			}
			if(num <= users[boxSpot].messages.size() && num >= 0){
				if(!users[boxSpot].messages[num-1].toDelete){
					rv << "+OK message " << msg.message << " deleted";
					socket.writeString(rv.str());
					//Set the message to be deleted
					users[boxSpot].messages[num-1].toDelete = true;
				}else{
					rv << "-ERR message " << msg.message << " already deleted";
					socket.writeString(rv.str());
				}
			}else{
				rv << "-ERR message " << msg.message << " not found";
				socket.writeString(rv.str());
			}
		}
		else if(msg.cmd == "NOOP"){
			socket.writeString("+OK");
		}
		else if(msg.cmd == "RSET"){
			//loop the Messages in teh mailbox and reset the toDelete bool to false
			int amount;
			int octets = 0;
			for(int i = 0; i < users[boxSpot].messages.size(); i++){
				users[boxSpot].messages[i].toDelete = false;
				octets += users[boxSpot].messages[i].message.size();
				amount = i;
			}
			rv << "+OK maildrop has " << amount+1 << " messages (" << octets << " octets)";
			socket.writeString(rv.str());
		}
		else if(msg.cmd == "QUIT"){
			//socket.writeString("+OK"); //dont need, has +OK when in update
			break;
		}else{
			socket.writeString("-ERR command not valid");
		}	
	}
	Update(socket,boxSpot);
}

void Update(Socket socket, int boxSpot){
	cout << "updating" << endl;
	//Loop through the Mailbox's messages
	for(int i = users[boxSpot].messages.size()-1; i >= 0; --i){
		//If the message in teh mailbox is to be deleted
		if(users[boxSpot].messages[i].toDelete){
			//Delete it
			users[boxSpot].messages.erase(users[boxSpot].messages.begin()+i);
		}
	}
	stringstream rv;
	if(users[boxSpot].messages.size() > 0){
		rv << "+OK " << users[boxSpot].username << " POP3 server signing off (" << users[boxSpot].messages.size() << " message(s) left)";
	}else{
		rv << "+OK " << users[boxSpot].username << " POP3 server signing off (maildrop empty)";
	}
	socket.writeString(rv.str());
	cout << "exiting" << endl;
	socket.close();
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
			sockets[sockets.size()-1].writeString("+OK POP3 server ready");
			cout << "connection received" << endl;
		}

		for(int i = sockets.size()-1; i >= 1; i-=1){
			if(sockets[i].isClosed){
				cout << sockets[i].host << " has left" << endl;
				sockets.erase(sockets.begin()+i);
			}else if(sockets[i].hasData){
				//handle that data

				if(sockets[i].auth == -1){
					sockets[i].auth = Authorize(sockets[i]);
				}else{
					Transaction(sockets[i], sockets[i].auth);
				}
			}
		}
	}
}


void client(string addr, string port){
	Socket s;
	s.open(addr, port);
	string str = s.readString();
	cout << str << endl;

	while(1){
		string input = "";
		string output = "";
		getline(cin, input);
		s.writeString(input);
		for(int i = 0; i < 4; ++i){
			char c = toupper((int)input[i]);
			input[i] = c;
		}
		if((input == "LIST") || input.substr(0,4) == "RETR"){
			do{
				output = s.readString();
				if((output.size() > 1) && (output[0] == '.')){
					output.erase(output.begin());
					cout << output << endl;
					output.push_back('.');
				}else{
					cout << output << endl;
				}
			}while(output != ".");
		}else{
			output = s.readString();
			cout << output << endl;
		}
		/*if(s.isClosed){
			cout << "connection closed" << endl;
			s.close();
			break;
		}*/
		if(input == "QUIT"){
			s.close();
			break;
		}
	}

}


int main(int argc, char** argv){
	populateMailbox();
	if(argc == 2){
		//port number so this is the server
		server(argv[1]);
	}else if(argc == 3){
		//client
		client(argv[1],argv[2]);
	}
}
