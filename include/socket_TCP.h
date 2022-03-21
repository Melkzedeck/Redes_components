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

std::string getAddr(int sock);


class Tclient {
	int socket_;
	static unsigned int tamMaxMsg; // tamanho máximo de recebimento de uma mensagem
	static unsigned int tamHead_; // tamanho do cabeçalho  da mensage (se tiver cabeçalho)
	static unsigned int posSize_, tamSize_; // posição e tamanho do campo Size(tamanho) do cabeçalho (se tiver cabeçalho)
public:
	//Construtor do socket com endereco
	Tclient(const Adress&);

	//Construtor copia
	Tclient(const Tclient&);

	//construtor a partir de um int
	Tclient(const int&);

	/* define um tamanho maximo de mensagem
	Tamanho default: 1024*/
	static void setTamMax(const unsigned int&);

	// Estabelece os parametros do cabeçalho se a mensagem tiver
	static void setParamHead(const unsigned int& tamHead, const unsigned int& posSize, const unsigned int& tamSize);

	//Get socket
	const int& sock() const;

	/* fluxo de saída de string:
	envia para o socket a string
	e retorna a qntd de bits enviadas*/
	ssize_t operator<<(const std::string&) const;

	/* fluxo de entrada de string:
	recebe do socket uma string
	e retorna a qntd de bits recebidas*/
	ssize_t operator>>(std::string&) const;

	// Fluxo de saída de dados codificados em string C
	// Se o tamanho do cabeçalho for zero, será enviado os dados até o caracter '\0'(que em bytes é 0)
	// Caso contrário, será enviado o cabeçalho e os dados conforme o cabeçalho
	ssize_t operator<<(const char*) const;

	// Fluxo de entrada de dados codificados em string C 
	// Se o tamanho do cabeçalho for zero, será recebido os dados do buffer
	// Caso contrário, será recebido o cabeçalho e os dados conforme o cabeçalho
	ssize_t operator>>(char*) const;

	//compara o numero do socket
	bool operator>(const Tclient&) const;

	//operador igual
	Tclient& operator=(const Tclient&);

	//retorna o endereço em string	
	std::string addr() const;

	//fecha a conexão do soquete
	void Close();
};



class Tserver {
	int socketS;
public:
	//Construtor do socket com endereco
	Tserver(const Adress&);

	//Construtor copia
	Tserver(const Tserver&);

	//Get socket do Server
	const int& sock() const;

	// Espera conexao e retorna o cliente conectado
	Tclient waitConection();

	~Tserver();
};
