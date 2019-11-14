Teagan Stephenson && Steven Crawford
POP3 server/client
Lab 4
CMSC 360
11/13/19

To compile:
	make
To run:
	server:
		./POP <port number>
	client:
		./POP <server host name> <server port number>

We have implemented all of the required POP3 protocol things, along with USER and PASS to "sign in" to an account.
STAT displays the number of messages and the total size of all the messages.
LIST w/o a given number lists the total number of messages, the total size, and then the size of each message.
LIST with a given number lists just the message number asked for and that messages number.
RETR takes the given message number and shows its size, then displays the message (on separate lines), 
and then sends a .\r\n line to say the message is over.
DELE takes in a message number and marks it to be deleted. Anything marked does not show up in list, stat, or retr.
NOOP prints +OK message and then does nothing.
RSET resets all messages to not be deleted.
QUIT breaks the transaction loop and calls update, which deletes any messages marked
to be deleted and then closes the socket.
USER is used to give username when first logged on.
PASS is used right after USER to complete authorization process.

NOTES:
commands are case insensitive.
when entering message number, start at 1.
If message is just a '.', it will not end input for RETR.
