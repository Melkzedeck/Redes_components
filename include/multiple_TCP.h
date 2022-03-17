#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <set>
#include <sys/time.h> 
#include <sys/select.h>

#include "Adress.h"
#include "socket_TCP.h"


class Multiple{

	Tserver server; // Socket do servidor para receber novas conexões

	fd_set readfds; // descritor do select
	int max_sd; // maior valor de socket -> necessário no select

	std::vector<Tclient> list; // lista de clientes conectados
	int it = -1; // iterador do vector da lista de clientes


	public:
		// Construtor da classe com endereço
		Multiple(const Adress&);

		// Retorna o número total de clientes
		unsigned numClients();

		// Depois de recebimento de mensagens, 
		// limpa o readfds e depois adiciona todos
		// os sockets no readfds
		void clearAndSet(); 

		// Espera por atividade em algum socket
		void wait(); 

		// Adiciona o cliente recém conectado ao socket do servidor
		const Tclient* addClient();

		// fecha o socket do cliente corrente
		void closeSocketIt(); 

		// retorna a posição do cliente em que houve atividade
		const int& activity();

		ssize_t receiveData(const int& pos, char* data);

		ssize_t sendData(const int& pos, char* data);

		ssize_t operator>>(std::string msg);

		ssize_t operator<<(std::string msg);

		ssize_t operator>>(char* data);

		ssize_t operator<<(char* data);

		const Tclient* listening();
};