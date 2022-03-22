# Documentação das classes e dos arquivos relacionados
Melkzedeck Miranda
## Introdução

Esse repositório consiste num compilado de Classes criadas e usadas por mim (com algumas coisas a mais) na disciplina Rede de Computadores - DCC023. Esse não é um código avançado em programação em socket C/C++, ou seja, é apenas introdutório. O objetivo desse repositório é para ajudar a compreender como a comunicação de socket C funciona e serve também para dar uma ideia de como o usar os conceitos de POO para ajudar na abstração da comunicação em sockets.  Planejo colocar links de outros repositórios que serão específicos aos programas feitos especificamente para aqueles TPs. Qualquer contribuição e feedback é muito bem-vindo, pois esse está sendo ser meu primeiro repositório público.

## Implementação

Esse repositório tem como objetivo desenvolver as classes, mas foram feitos tambem alguns programas testes que foram usados para verificar o funcionamento destas. As classes feitas foram: Adress, Tclient, Tserver, Multiple e Usock, usando a interface POSIX e soquetes de rede na linguagem C. 

### Adress
A classe *Adress* serve para tratamento de endereços IP (IPv4 e IPv6) e portas usadas na comunicação na rede.  
```C++
    /*Construtor da classe Adress usando a versão ('4'-(IPv4) ou '6'-(IPv6))
     e a porta(string) como argumento - lado do servidor*/
    Adress::Adress(char v, std::string port_s);

    /*Construtor usando o endereco(string) e porta(string) - lado cliente*/
    Adress::Adress(std::string addrstr, std::string port_s);
```

### Tclient
A classe *Tclient* serve para inicialização, conexão e encerramento no final do programado soquete, e envio e recebimento de mensagens visando a comunicação do lado do Cliente.
```C++
    //Construtor do socket com endereco
    Tclient::Tclient(const Adress&);

    /* define um tamanho maximo de fluxo de mensagem da classe
    Tamanho default: 1024*/
    static void Tclient::setTAM(const int& t);

    /* fluxo de saída de string:
    envia para o socket a string
    e retorna a qntd de bits enviadas*/
    ssize_t Tclient::operator<<(const std::string&);

    /* fluxo de entrada de string: recebe uma msg do socket, 
    coloca em uma string e retorna a qntd de bytes recebidas*/
    ssize_t Tclient::operator>>(std::string&);
```

### Tserver
A classe *Tserver* serve para inicializar, ligar (bind) a um endereço e deixar o soquete na escuta (listen) para novas conexões, visando a comunicação no lado do servidor e, no término de sua utilização, o fechamento do descritor do soquete. Quando um objeto da classe Tserver identifica uma nova conexão, ele retorna um objeto da classe Tclient para que a comunicação seja estabelecida. 

```C++

    //Construtor do socket com endereco
    Tserver::Tserver(Adress&);

    // Espera conexao e retorna o cliente conectado
    Tclient Tserver::waitConection();
```
### Multiple
A classe *Multiple* serve para a comunicação do servidor com múltiplos cliente conectados via protocolo TCP. Nele temos uma classe composta com objetos do tipo Tclient (usadas na comunicação com os clientes) e do tipo Tserver (usado para estabelecer novas conexões). 

### Makefile


