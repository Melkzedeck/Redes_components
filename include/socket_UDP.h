#pragma once
/*----------- Bliblioteca sockets POSIX -----------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
//-------------------------------------------------//
#include <stdexcept>
#include "Adress.h"


class Usock {
	int socket_;
	static unsigned int tam_max;
public:
	//Construtor default
	Usock(const char&);
	//Construtor copia
	Usock(const Usock&);
	//construtor a partir de um int
	Usock(const int&);
	//Liga o servidor no endereco
	void bind_s(const Adress&);
	/* define um tamanho maximo de mensagem
	Tamanho default: 1024*/
	static void setTAM(const int&);
	//Get socket
	int sock() const;
	/* fluxo de saída de string:
	envia para o socket a string
	e retorna a qntd de bits enviadas*/
	ssize_t send(const Adress&, const std::string&);
	/* fluxo de entrada de string:
	recebe do socket uma string
	e retorna a qntd de bits recebidas*/
	ssize_t recv(Adress&, std::string&);
	//compara o numero do socket
	bool operator>(const Usock&) const;
	//operador igual
	Usock& operator=(const Usock&);
	//destrutor
	~Usock();
};