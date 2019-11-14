
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
	tempMail.message = ".";
	Mail tempMail2;
	tempMail2.toDelete = false;
	tempMail2.message = "test\n.\nmulti";

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
