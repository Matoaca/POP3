 #include "Socket.h"

void waitForEvent(vector<Socket>& sockets,int timeout){
	struct pollfd fds[255];
	int numFDs = 1;

	for(Socket& s: sockets){
		s.hasData = false;
		fds[numFDs-1].fd = s.fd;
		fds[numFDs-1].events = POLLIN | POLLRDHUP | POLLHUP;
		numFDs += 1;
	}
	poll(fds,numFDs,timeout);

	for(int i =0; i < numFDs; ++i){
		if(fds[i].revents &  POLLRDHUP || fds[i].revents & POLLHUP){
			sockets[i].close();
		}else if(fds[i].revents & POLLIN){
            sockets[i].hasData = true;
        }
	}
}

void Socket::readBytes(void* bytes, int len){
	read(fd, bytes, sizeof(char) * len);
}

void Socket::writeBytes(void* bytes, int len){
	write(fd, bytes, sizeof(char) * len);
}

void Socket::writeString(string str){
	str += '\0';
	write(fd,str.c_str(),sizeof(char)*str.size());
}

string Socket::readString(){
	string rv = "";
	char token;
	int count = 0;
	do{
		read(fd,&token,sizeof(char));
		rv += token;
		count += 1;
	}while(token != 0 && count < 256);
	return rv;
}


void Socket::open(string hosto,string porto){
	struct addrinfo hints;
    struct addrinfo *info;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

	//ip4 only
    getaddrinfo(hosto.c_str(), porto.c_str(), &hints,  &info);
    fd = socket(info->ai_family, info->ai_socktype, 0);
    int result = connect(fd, info->ai_addr, info->ai_addrlen);

    host = hosto;
    port = porto;

    freeaddrinfo(info);
}

void Socket::listen(string porto){

    struct addrinfo hints;
    struct addrinfo *info;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // or use AF_UNSPEC
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, porto.c_str(), &hints, &info);

    port = porto;

    //This is the socket that will listen for connections
    fd = socket(info->ai_family, info->ai_socktype, 0);

    int error = ::bind(fd, info->ai_addr, info->ai_addrlen);

    freeaddrinfo(info);

    error = ::listen(fd,4);
	isClosed = error < 0;
}

Socket Socket::accept(){
    Socket sock;

    struct sockaddr_storage address;
    socklen_t size = sizeof(address);
    bzero(&address, sizeof(address));

    sock.fd = ::accept(fd, (struct sockaddr *)&address, &size);

    char ip[NI_MAXHOST];
    char srv[NI_MAXSERV];

    getnameinfo(((sockaddr *)&address), size, ip, sizeof(ip),srv, sizeof(srv), NI_NUMERICHOST | NI_NUMERICSERV);

    sock.host = ip;
    sock.port = srv;
    sock.isClosed = false;
    return sock;
}

void Socket::close(){
    isClosed = true;
    ::close(fd);
}
