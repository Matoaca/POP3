#include "Populate.h"


void populateMailbox(){

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "Test";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.username = "Steven";
	tempMailbox.password = "password";
	
	users.push_back(tempMailbox);

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "Test";
	Mail tempMail2;
	tempMail2.toDelete = false;
	tempMail2.message = "testmulti";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.messages.push_back(tempMail2);
	tempMailbox.username = "Teagan";
	tempMailbox.password = "diffpass";
	
	users.push_back(tempMailbox);

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "Test1";
	Mail tempMail2;
	tempMail2.toDelete = false;
	tempMail2.message = "Test2";
	Mail tempMail3;
	tempMail3.toDelete = false;
	tempMail3.message = "Test3";
	Mail tempMail4;
	tempMail4.toDelete = false;
	tempMail4.message = "Test4";
	Mail tempMail5;
	tempMail5.toDelete = false;
	tempMail5.message = "Test5";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.messages.push_back(tempMail2);
	tempMailbox.messages.push_back(tempMail3);
	tempMailbox.messages.push_back(tempMail4);
	tempMailbox.messages.push_back(tempMail5);
	tempMailbox.username = "Masha";
	tempMailbox.password = "Masapass";
	
	users.push_back(tempMailbox);

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.username = "Cameron";
	tempMailbox.password = "NullPass";
	
	users.push_back(tempMailbox);

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "Test longer then one word";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.username = "Daniel";
	tempMailbox.password = "Danpass";
	
	users.push_back(tempMailbox);

	Mail tempMail;
	tempMail.toDelete = false;
	tempMail.message = "Test longer then one word";
	Mail tempMail2;
	tempMail2.toDelete = false;
	tempMail2.message = "Test longer then one word but with more mail this time";

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.messages.push_back(tempMail2);
	tempMailbox.username = "Brendan";
	tempMailbox.password = "Banpass";
	
	users.push_back(tempMailbox);

	Mail tempMail;
	tempMail.toDelete = false;

	Mailbox tempMailbox;
	tempMailbox.messages.push_back(tempMail);
	tempMailbox.username = "";
	tempMailbox.password = "Nullmesa";
	
	users.push_back(tempMailbox);
}
