#pragma once
#include <iostream>

using namespace std;

#define PORT 13225
#define PORT_STR "13225"

//enunm Forward Declaration
//it is feasible as long as the type is defined in the code.
typedef enum connectorType{ CLIENT, SERVER };

class connector
{
public:
	connector();							//init socket, io_handler, etc, ver tp6
	virtual connectorType getType() = 0;	
	bool sendMessage(string msg);			//Devuelve false si no pudo mandar el mensaje
	bool receiveMessage();					//Devuelve true si recibio un mensaje. Si recibe un mensaje, se pisa el anterior, cuidado
	bool messagePresent();					//Preguntar con este metodo si hay un mensaje presente
	string getMessage();					//Pedir el mensaje, conviene primero preguntar si habia un mensaje
	bool isConnected();
	~connector();

protected:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket;
	string messageReceived;
	bool connected;
};

