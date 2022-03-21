#include <iostream>
#include "Adress.h"
#include "socket_TCP.h"
#include "socket_UDP.h"

using std::string;
using std::cout;
using std::endl;

// Comunicação TCP com um único cliente
void TCPComunication(Tclient& sockcli);

// Comunicação UDP
void UDPComunication(Usock& sockCli);

int main(int argc, char** argv){
	int portUDP = std::stoi(argv[2]) + 1;
	Adress addrServerTCP(argv[1][1],argv[2]);
	Adress addrServerUDP(argv[1][1], std::to_string(portUDP));

	Usock usock(argv[1][1]);
	usock.Bind(addrServerUDP);
	Tserver sock(addrServerTCP);
	Tclient TsockCli = sock.waitConection();

	cout << "Connected to client in: " << TsockCli.addr() << endl;
	cout << "Starting TCP communications..." << endl << endl;
	TCPComunication(TsockCli);
	cout << "Starting UDP communications..." << endl << endl;
	UDPComunication(usock);
	
	TsockCli.Close();
	usock.Close();
}

void TCPComunication(Tclient& sockCli){
	string msg;
	ssize_t count;
	while(msg != "kill"){
		count = sockCli >> msg;
		if(count == 0){
			cout << "client disconected" << endl;
			break;
		}
		cout << "TCP - Message received: " << msg << endl;
		cout << "Total of " << count << " bytes received" <<endl << endl;
	}
}

void UDPComunication(Usock& sockCli){
	Adress Client;
	string msg;
	ssize_t count;
	while(msg != "kill"){
		count = sockCli.recv(Client, msg);
		cout << "UDP - Message received: " << msg << endl;
		cout << "Total of " << count << " bytes received from" << 
		Client.str() <<endl << endl;
	}
}