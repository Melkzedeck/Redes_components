#include <iostream>
#include "Adress.h"
#include "socket_UDP.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

int main(int argc, char** argv){
	Adress addrServer(argv[1],argv[2]);
	char version;
	version = addrServer.family() == AF_INET ? '4':'6';
	Usock sock(version);
	string msg;
	ssize_t count;
	char data[100];

	do {
		bzero(data, 100);
		cin.getline(data, 99);
		msg = string(data);
		count = sock.send(addrServer,msg);
		cout << "UDP - Message sended: " << msg << endl;
		cout << "Total of " << count << "bytes sended" <<endl << endl;
	} while(msg != "kill" && msg.size() > 0);
	sock.Close();
}