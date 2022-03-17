/*#include "../include/socket_UDP.h"

#include "../include/socket_TCP.h"

using std::runtime_error;

unsigned int Usock::tam_max=1024;

void Usock::setTAM(const int& t){tam_max=t;}

Usock::Usock(const char& c){
    int family;
    if(c==4)
        family = AF_INET;
    else if(c==6)
        family = AF_INET6;
    else
        throw(std::invalid_argument("familia desconhecida"));
	socket_ = socket(family, SOCK_DGRAM, 0);
	if (socket_ == -1) {
		throw runtime_error("socket");
	}
}

Usock::Usock(const Usock& c){this->socket_ = c.socket_;}

Usock::Usock(const int& s){socket_ = s;}

int Usock::sock() const {return socket_;}

void Usock::bind_s(const Adress& add){
     if ( bind(socket_, add.addr(), 
            *(add.addrlen())) < 0 )
    {
        throw(runtime_error("socket bind failed"));
    }
}

ssize_t Usock::send(const Adress& add, const std::string& str){
		return sendto(socket_, str.c_str(), str.length(), 0,add.addr(), *(add.addrlen()));
}

ssize_t Usock::recv(Adress& add, std::string& str){
    char *msg;
    msg = new char[tam_max];
    struct sockaddr* aux;
    socklen_t* len_aux;
    ssize_t cnt = recvfrom(socket_, msg, tam_max, 0, aux, len_aux);
    add = Adress(aux);
    str = std::string(msg, cnt);
    delete msg;
    return cnt;
}
	
bool Usock::operator>(const Usock& comp) const {return this->socket_ > comp.socket_;}

Usock& Usock::operator=(const Usock& cli){
    this->socket_ = cli.socket_;
    return *this;
}

Usock::~Usock(){
	close(socket_);
}
*/