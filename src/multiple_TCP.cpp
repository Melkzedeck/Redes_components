#include "multiple_TCP.h"

using std::make_pair;
using std::set;
using std::string;


Multiple::Multiple(const Adress& add): server(add), list() {
	max_sd = 0;
}


unsigned Multiple::numClients(){
	return list.size();
}

void Multiple::clearAndSet(){
	max_sd = 0;
	//clear the socket set 
	FD_ZERO(&readfds);  
	
	//add master socket to set 
	FD_SET(server.sock(), &readfds);  
	max_sd = server.sock();  
			
	//add child sockets to set 
	int sd = 0;
	for (unsigned i = 0 ; i < list.size() ; i++)  
	{  
		//socket descriptor 
		sd = list[i].sock();  

		FD_SET(sd,&readfds);  
				
		//highest file descriptor number, need it for the select function 
		if(sd > max_sd)  
			max_sd = sd;  
	}
}

void Multiple::wait(){  // se for 1 -> servidor, se for 0 -> cliente 

	int activity;  
	activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
	if ((activity < 0) && (errno!=EINTR))  
	{  
		printf("error select: %s\n", strerror(errno));
    	throw std::runtime_error("select");
	}  
} 

const Tclient* Multiple::addClient(){
	// se a atividade for no cliente
	
	if(FD_ISSET(server.sock(), &readfds) > 0){
		Tclient newCli = server.waitConection();
		list.push_back(newCli);
		newCli = Tclient(0);
		return &list[list.size()-1];
	}
	return nullptr;
}  

const int& Multiple::activity(){
	it++;
	while (it < (int)list.size()){
		if (FD_ISSET( list[it].sock() , &readfds)){
			return it;
		}
		it++;
	}
	it = -1;
	return it;
}

void Multiple::closeSocketIt(){
	list.erase(list.begin()+it);
	it--;
}


ssize_t Multiple::receiveData(const int& pos, char* data){
	return list[pos] >> data;
}

ssize_t Multiple::sendData(const int& pos, char* data){
	return list[pos] << data;
}

ssize_t Multiple::operator>>(std::string msg){
	return list[it] >> msg;
}

ssize_t Multiple::operator<<(std::string msg){
	return list[it] << msg;
}

ssize_t Multiple::operator>>(char* data){
	return list[it] >> data;
}

ssize_t Multiple::operator<<(char* data){
	return list[it] << data;
}


const Tclient* Multiple::listening(){
	return &list[it];
}

