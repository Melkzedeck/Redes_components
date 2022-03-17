#include <iostream>
#include <Adress.h>
#include "socket_TCP.h"
#include "multiple_TCP.h"


using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

int main(int argc, char** argv){
	Adress addrServer(argv[1][1],argv[2]);
	Multiple server(addrServer);
	string msg;
	ssize_t count;
	Tclient* newCli = nullptr;

	while(true){
		server.clearAndSet();
		server.wait();
		newCLi = server.addClient();
		if(newClir != nullptr){
			cout << "New connection: " << (newCli -> addr()) << endl;
		}
	}

	msg = sockCli.addr();
	cout << "Connected to client in: " << msg << endl;
	count = sockCli >> msg;
	cout << "Message received: " << msg << endl;
	cout << "Total of " << count << "bytes received" <<endl;

}