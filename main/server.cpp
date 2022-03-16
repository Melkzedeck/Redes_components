#include <iostream>
#include <Adress.h>
#include <socket_TCP.h>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

int main(int argc, char** argv){
	Adress addrServer(argv[1][1],argv[2]);
	Tserver sock(addrServer);
	Tclient sockCli = sock.waitConection();
	string msg;
	ssize_t count;
	char data[100];

	msg = sockCli.addr();
	cout << "Connected to client in: " << msg << endl;
	count = sockCli >> msg;
	cout << "Message received: " << msg << endl;
	cout << "Total of " << count << "bytes received" <<endl;

	cin.getline(data, 99);
	msg = string(data);
	count = sockCli << msg;
	cout << "Message sended: " << msg << endl;
	cout << "Total of " << count << "bytes sended" <<endl;
}