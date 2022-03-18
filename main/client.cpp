#include <iostream>
#include <Adress.h>
#include <socket_TCP.h>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

int main(int argc, char** argv){
	Adress addrServer(argv[1],argv[2]);
	Tclient sock(addrServer);
	string msg;
	ssize_t count;
	char data[100];

	do {
		bzero(data, 100);
		cin.getline(data, 99);
		msg = string(data);
		count = sock << msg;
		cout << "Message sended: " << msg << endl;
		cout << "Total of " << count << "bytes sended" <<endl << endl;
	} while(msg != "kill" && msg.size() > 0);
	sock.shut();
}