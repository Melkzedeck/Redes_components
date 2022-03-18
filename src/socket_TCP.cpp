#include "../include/socket_TCP.h"

/*std::string getAddr(int sock){
	// Get my ip address and port
	sockaddr_in addr4;
	sockaddr_in6 addr6;
	sockaddr *myAddr, addr;
    socklen_t lenMy = sizeof(addr);
	myAddr = (sockaddr *)&addr6;
	const char *ed;
	int ad;
	bool v4 = true;
	char myIP[20];

    bzero(&addr4, sizeof(addr4));
    bzero(&addr6, sizeof(addr6));
    bzero(&addr, sizeof(addr));
	bzero(&myIP,20);

	ad = getpeername(sock, myAddr, &lenMy);
	if(lenMy == sizeof(addr4)){
		memcpy(&addr4,myAddr,lenMy);
		ed = inet_ntop(AF_INET, (sockaddr *)&addr4.sin_addr, myIP, lenMy);
	}
	else if(lenMy == sizeof(addr6)){
		ed = inet_ntop(AF_INET6, (sockaddr *)&addr6.sin6_addr, myIP, lenMy);
	}
		

	/*//* Get my ip address and port
	sockaddr my_addr;
	sockaddr_in addr4;
	sockaddr_in6 addr6;
	const char *ed;
	bool v4 = true;
	char myIP[20];

    bzero(&addr4, sizeof(addr4));
    bzero(&addr6, sizeof(addr6));
	bzero(&myIP,20);

    socklen_t len = sizeof(addr4);
	int ad = getsockname(sock, &my_addr, &len);
	ed = inet_ntop(AF_INET, &my_addr, myIP, len);
	ed = inet_ntop(AF_INET6, &my_addr, myIP, len);

    
	return(std::string(myIP));
}
*/

/*-------------------- Comeco da classe Tclient --------------------*/

using std::runtime_error;

unsigned int Tclient::tamMaxMsg = 1024;

unsigned int Tclient::tamHead_ = 0;
unsigned int Tclient::posSize_ = 0;
unsigned int Tclient::tamSize_ = 0;

void Tclient::setTamMax(const unsigned int& t){tamMaxMsg = t;}

Tclient::Tclient(const Adress& addr){
	socket_ = socket(addr.family(), SOCK_STREAM, 0);
	if (socket_ == -1) {
		throw runtime_error("erro ao criar socket");
	}
	if (0 != connect(socket_, addr.addr(), *(addr.addrlen()))) {
		throw runtime_error("erro connect");
	}

}

Tclient::Tclient(const Tclient& c){this->socket_ = c.socket_;}

Tclient::Tclient(const int& s){socket_ = s;}

const int& Tclient::sock() const {return socket_;}

ssize_t Tclient::operator<<(const std::string& str) const{
		return send(socket_, str.c_str(), str.length(), 0);
}

ssize_t Tclient::operator>>(std::string& str) const{
    char msg[tamMaxMsg];
    ssize_t cnt = recv(socket_, msg, tamMaxMsg, 0);
    str = std::string(msg, cnt);
    return cnt;
}
	
bool Tclient::operator>(const Tclient& comp) const {return this->socket_ > comp.socket_;}

Tclient& Tclient::operator=(const Tclient& cli){
    this->socket_ = cli.socket_;
    return *this;
}


//retorna o endereço em string	
std::string Tclient::addr() const{
	// Get my ip address and port
	sockaddr_in *addr4;
	sockaddr_in6 *addr6;
	struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
	socklen_t caddrlen = sizeof(struct sockaddr_storage);
	char myIP[80];
	std::string addrStr = "IP ";
	const char *debug;

    bzero(&addr4, sizeof(addr4));
    bzero(&addr6, sizeof(addr6));
	bzero(&myIP,20);

	getpeername(socket_, caddr, &caddrlen);
	if(caddr->sa_family == AF_INET){
		addr4 = (sockaddr_in *) caddr;
		debug = inet_ntop(AF_INET, &(addr4->sin_addr), myIP, caddrlen);
		addrStr += myIP;
		addrStr += ", port ";
		addrStr += std::to_string((int)ntohs(addr4->sin_port));
	}
	else if(caddr->sa_family == AF_INET6){
		addr6 = (sockaddr_in6 *) caddr;
		debug = inet_ntop(AF_INET6, &(addr6->sin6_addr), myIP, caddrlen);
		addrStr += myIP;
		addrStr += ", port ";
		addrStr += std::to_string((int)ntohs(addr6->sin6_port));
	}
	return addrStr;
}



ssize_t Tclient::operator<<(const char* data) const{
	char head[tamHead_];
	bzero(head, tamHead_);
	int tam  = 0;
	strncpy(head,data,tamHead_);
	for(unsigned int i = 0; i < tamHead_-posSize_ && i < tamSize_ - posSize_; i++){
		tam += ((int)(head[i+posSize_]) << 8*i)&(0xff << 8*i);
	}
	return send(socket_, data, tam + tamHead_, 0);
}


ssize_t Tclient::operator>>(char* data) const{
	char head[tamHead_];
	int tam  = 0;
	ssize_t cnt;
	bzero(head, tamHead_);
	cnt = recv(socket_, head, tamHead_, 0);
	for(unsigned int i = 0; i < tamHead_-posSize_ && i < tamSize_ - posSize_; i++){
		tam += ((int)(head[i+posSize_]) << 8*i)&(0xff << 8*i);
	}
	strncpy(data, head, tamHead_);
	cnt += recv(socket_, data + tamHead_, tam, 0);
	return cnt;
}


Tclient::~Tclient(){
	close(socket_);
}

/*-------------------- Termino da classe Tclient --------------------*/


/*-------------------- Comeco da classe Tserver --------------------*/

Tserver::Tserver(const Adress& addr){
	socketS = socket(addr.family(), SOCK_STREAM, 0);
	if (socketS == -1) {
        throw runtime_error("erro ao criar socket");
    }

    int enable = 1;
    if (0 != setsockopt(socketS, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        throw runtime_error("erro no setsockopt");
    }

    if (0 != bind(socketS, addr.addr(), *(addr.addrlen()))) {
        throw runtime_error("erro bind");
    }

    if (0 != listen(socketS, 10)) {
        throw runtime_error("erro listen");
    }
}

Tserver::Tserver(const Tserver& copia){this->socketS = copia.socketS;}

const int& Tserver::sock() const {return socketS;}


Tclient Tserver::waitConection(){
    int socketC;
	struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
	struct sockaddr_in *addr4 = nullptr;
	struct sockaddr_in6 *addr6 = nullptr;
	char bufAddr[80];
	bzero(bufAddr,80);
    socklen_t caddrlen = sizeof(struct sockaddr_storage);
	socketC = accept(socketS, caddr, &caddrlen);
	if(caddr->sa_family == AF_INET){
		addr4 = (sockaddr_in *)caddr;
		inet_ntop(AF_INET, &(addr4->sin_addr), bufAddr, sizeof(sockaddr_in));
		printf("New connection , socket fd is %d , ip is : %s , port : %d \n", 
		socketC , inet_ntoa(addr4->sin_addr) , ntohs(addr4->sin_port)); 
	}
	else if(caddr->sa_family == AF_INET6){
		addr6 = (sockaddr_in6 *)caddr;
		printf("New connection , socket fd is %d , ip is : %s , port : %d \n", 
		socketC , inet_ntop(AF_INET6,&(addr6->sin6_addr), bufAddr, sizeof(sockaddr_in6)) , ntohs
				(addr6->sin6_port)); 
	}
	
	if (socketC == -1) {
            throw runtime_error("erro accept");
        }
	return Tclient(socketC);
}


Tserver::~Tserver(){
	close(socketS);
}

/*-------------------- Termino da classe Tserver --------------------*/

