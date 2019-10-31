#include "Range.h"
#include <iostream>

enum MsgType{
	Joinrequest,
	Joinresponse,
	PEEP_UPDATE
};

struct Address{
	int port;
	char host[64];
};

struct Packet{
    MsgType type;
	Address src;
	Address dest;
    unsigned char payload[60];
};

struct Msg{
    int size;
    char buffer[56];
};

struct JoinRequest{
	Point dest;
};

struct JoinResponse{
	Range range;
};

struct NeighborUpdate{
	
};

