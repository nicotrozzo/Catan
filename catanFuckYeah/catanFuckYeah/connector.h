#pragma once
#include <iostream>
#include <boost/asio.hpp>

using namespace std;

#define PORT 13225
#define PORT_STR "13225"

//enunm Forward Declaration
//it is feasible as long as the type is defined in the code.
enum connectorType{ CLIENT, SERVER };

class connector
{
public:
	connector();							//init socket, io_handler
	virtual connectorType getType() = 0;	
	bool sendMessage(const unsigned char* msg, size_t length);			//Devuelve false si no pudo mandar el mensaje
	bool receiveMessage();					//Devuelve true si recibio un mensaje. Si recibe un mensaje, se pisa el anterior, cuidado
	bool messagePresent();					//Preguntar con este metodo si hay un mensaje presente
	unsigned char * getMessage();					//Pedir el mensaje, conviene primero preguntar si habia un mensaje
	size_t getMessageLenght();
	bool isConnected();
	~connector();

protected:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket;
	unsigned char buf[512];
	bool messageRead;
	bool connected;
	size_t len;
};

