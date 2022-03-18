#include <iostream>
#include <Adress.h>
#include "socket_TCP.h"
#include "multiple_TCP.h"


using std::string;
using std::cout;
using std::endl;


int main(int argc, char** argv){
	Adress addrServer(argv[1][1],argv[2]);
	cout << "Nova conexão estabelecida no endereço " << addrServer.str() <<endl << endl;
	Multiple server(addrServer);
	string msg;
	ssize_t count = -1;
	const Tclient* newCli = nullptr;
	const Tclient* client = nullptr;
	int posEvento;// posicao do sockete em que aconteceu o evento
	while(msg != "kill"){
		server.clearAndSet();
		server.wait();
		newCli = server.addClient();
		if(newCli != nullptr){
			cout << "New connection: " << (newCli -> addr()) << endl << endl;
		}
		posEvento = server.activity();
		while(posEvento >= 0){
			count = server >> msg;
			client = server.listening();
			if(client != nullptr && count > 0){
				cout << "Msg from " << (client -> addr()) << ": " << msg << endl;
				cout << "Total of received bytes: " << count << endl << endl;
			}
			else if(count == 0){
				cout << "Client disconnected: " << (client -> addr()) << endl;
				cout << "Removig of client list"  << endl << endl;
				server.closeSocketIt();
			}
			posEvento = server.activity();
		}
	}
}
