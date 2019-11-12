#include <sstream>
//#include "Populate.h"
#include "Packet.h"

using namespace std;

Msg parseMsg(string str);
int userFound(string msg);
bool passFound(string msg);
void Authorize(Socket socket);
void Transaction(Socket socket, int boxSpot);
void Update(Socket socket, int boxSpot);

vector <Mailbox> users;

void populateMailbox(){

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "Test";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.username = "Steven";
	tempMailbox.password = "password";
	
	users.push_back(tempMailbox);

	Mail tempMail1;
	tempMail.toDelete = false;
	tempMail.message = "Test";
	Mail tempMail2;
	tempMail2.toDelete = false;
	tempMail2.message = "testmulti";

	Mailbox tempMailbox1;
	tempMailbox1.messages.push_back(tempMail);
	tempMailbox1.messages.push_back(tempMail2);
	tempMailbox1.username = "Teagan";
	tempMailbox1.password = "diffpass";
	
	users.push_back(tempMailbox1);

	Mail tempMail3;
	tempMail3.toDelete = false;
	tempMail3.message = "Test1";
	Mail tempMail4;
	tempMail4.toDelete = false;
	tempMail4.message = "Test2";
	Mail tempMail5;
	tempMail5.toDelete = false;
	tempMail5.message = "Test3";
	Mail tempMail6;
	tempMail6.toDelete = false;
	tempMail6.message = "Test4";
	Mail tempMail7;
	tempMail7.toDelete = false;
	tempMail7.message = "Test5";

	Mailbox tempMailbox2;
	tempMailbox2.messages.push_back(tempMail3);
	tempMailbox2.messages.push_back(tempMail4);
	tempMailbox2.messages.push_back(tempMail5);
	tempMailbox2.messages.push_back(tempMail6);
	tempMailbox2.messages.push_back(tempMail7);
	tempMailbox2.username = "Masha";
	tempMailbox2.password = "Masapass";
	
	users.push_back(tempMailbox2);

	Mail tempMail8;
	tempMail8.toDelete = false;
	tempMail8.message = "";

	Mailbox tempMailbox3;
	tempMailbox3.messages.push_back(tempMail8);
	tempMailbox3.username = "Cameron";
	tempMailbox3.password = "NullPass";
	
	users.push_back(tempMailbox3);

	Mail tempMail9;
	tempMail9.toDelete = false;
	tempMail9.message = "Test longer then one word";

	Mailbox tempMailbox4;
	tempMailbox4.messages.push_back(tempMail9);
	tempMailbox4.username = "Daniel";
	tempMailbox4.password = "Danpass";
	
	users.push_back(tempMailbox4);

	Mail tempMail0;
	tempMail0.toDelete = false;
	tempMail0.message = "Test longer then one word";
	Mail tempMail01;
	tempMail01.toDelete = false;
	tempMail01.message = "Test longer then one word but with more mail this time";

	Mailbox tempMailbox5;
	tempMailbox5.messages.push_back(tempMail0);
	tempMailbox5.messages.push_back(tempMail01);
	tempMailbox5.username = "Brendan";
	tempMailbox5.password = "Banpass";
	
	users.push_back(tempMailbox5);

	Mail tempMail02;
	tempMail02.toDelete = false;

	Mailbox tempMailbox6;
	tempMailbox6.messages.push_back(tempMail02);
	tempMailbox6.username = "";
	tempMailbox6.password = "Nullmesa";
	
	users.push_back(tempMailbox6);
}

Msg parseMsg(string str){
	string firstpart;
	string rest;
	for(int i = 0; i < 4; i++){
		firstpart = firstpart + str[i];
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

void Authorize(Socket socket){
	//Read in the USER
	string msg = socket.readString();
	Msg msgParts = parseMsg(msg);
	int person;
	
	if(msgParts.cmd == "QUIT"){
		socket.writeString("+OK POP3 server signing off");
		return;
	}else if(msgParts.cmd == "USER"){
		person = userFound(msgParts.message);//find username
		if(person == -1){
			socket.writeString("-ERR Invalid USER");
			return;
		}
	}else{
		socket.writeString("-ERR Invalid USER");
		return;
	}
	socket.writeString("+OK USER is valid");
	
	msg = socket.readString();
	msgParts = parseMsg(msg);
	if(msgParts.cmd == "QUIT"){
		socket.writeString("+OK POP3 server signing off");
		return;
	}else if(msgParts.cmd == "PASS"){
		if(!(passFound(msgParts.message, person))){
			socket.writeString("-ERR Invalid PASS");
			return;
		}
	}else{
		socket.writeString("-ERR Invalid PASS");
		return;
	}
	socket.writeString("+OK PASS is valid");
	Transaction(socket, person);
}

//use readString and writeString everywhere
void Transaction(Socket socket, int boxSpot){
	while(1){
		string str = socket.readString();
		Msg msg = parseMsg(str);
		stringstream rv;

		if(msg.cmd == "STAT"){
			int octets = 0;
			rv << "+OK ";
			rv << users[boxSpot].messages.size();
			for(int i = 0; i < users[boxSpot].messages.size(); i++){
				octets = octets + users[boxSpot].messages[i].message.size();
			}
			rv << " " << octets;
			socket.writeString(rv.str());
		}
		else if(msg.cmd == "LIST"){
			int num = stoi(msg.message);
			if(msg.message == ""){
				int octets = 0;
				rv << "+OK " << users[boxSpot].messages.size() << "messages (";
				for(int i = 0; i < users[boxSpot].messages.size(); i++){
					octets = octets + users[boxSpot].messages[i].message.size();
				}
				rv << octets << " octets)";
				socket.writeString(rv.str());
				
				
				for(int i = 0; i < users[boxSpot].messages.size(); i++){
					stringstream strstr;
					strstr << (i+1) << " " << users[boxSpot].messages[i].message.size();
					socket.writeString(strstr.str());
				}
				socket.writeString(".");
			}else if(num <= users[boxSpot].messages.size()-1 && num >= 1 && !(users[boxSpot].messages[num-1].toDelete)){
				rv << "+OK " << msg.message << " " << users[boxSpot].messages[num].message.size();
				socket.writeString(rv.str());
			}else{
				rv << "-ERR no such message, only " << users[boxSpot].messages.size() << " messages in maildrop";
				socket.writeString(rv.str());
			}
		}
		else if(msg.cmd == "RETR"){
			int num = stoi(msg.message);
			if(num <= users[boxSpot].messages.size()-1 && num >= 1 && !(users[boxSpot].messages[num-1].toDelete)){
				rv << "+OK " << users[boxSpot].messages[num-1].message.size() << " octets";
				socket.writeString(rv.str());
				socket.writeString(users[boxSpot].messages[num-1].message);
				socket.writeString(".");
				users[boxSpot].messages[num-1].toDelete = true;
			}else{
				rv << "-ERR no such message";
				socket.writeString(rv.str());
			}
		}
		else if(msg.cmd == "DELE"){
			//Find the message to be deleted
			int num = stoi(msg.message);
			if(num <= users[boxSpot].messages.size()-1 && num >= 0){
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
			rv << "+OK maildrop has " << amount << " messages (" << octets << " octets)";
			socket.writeString(rv.str());
		}
		else if(msg.cmd == "QUIT"){
			//socket.writeString("+OK"); //dont need, has +OK when in update
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
	stringstream rv;
	if(users[boxSpot].messages.size() > 0){
		rv << "+OK " << users[boxSpot].username << "POP3 server signing off (" << users[boxSpot].messages.size() << " message(s) left)";
	}else{
		rv << "+OK " << users[boxSpot].username << "POP3 server signing off (maildrop empty)";
	}
	socket.writeString(rv.str());
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
				sockets[i].close();
			}
		}
	}
}


void client(string addr, string port){
	Socket s;
	s.open(addr, port);
	
	while(1){
		string input = "";
		string output = "";
		getline(cin, input);
		s.writeString(input);
		output = s.readString();
		cout << input << endl;
		cout << output << endl;
		if(input == "QUIT")
			break;
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
