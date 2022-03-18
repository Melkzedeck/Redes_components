#include <iostream>
#include <Adress.h>
#include <socket_TCP.h>

using std::string;
using std::cout;
using std::endl;


int main(int argc, char** argv){
	Adress addrServer(argv[1][1],argv[2]);
	Tserver sock(addrServer);
	Tclient sockCli = sock.waitConection();
	string msg;
	ssize_t count;

	msg = sockCli.addr();
	cout << "Connected to client in: " << msg << endl;
	while(msg != "kill"){
		count = sockCli >> msg;
		if(count == 0){
			cout << "client disconected" << endl;
			break;
		}
		cout << "Message received: " << msg << endl;
		cout << "Total of " << count << " bytes received" <<endl << endl;
	}
	sockCli.shut();	
}