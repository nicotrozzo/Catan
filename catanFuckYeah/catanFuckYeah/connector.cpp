#include "connector.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

connector::connector()
{
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	connected = false;
}

/*Devuelve false si intento mandar el mensaje y no pudo*/
bool connector::sendMessage(string msg)
{
	bool ret = false;
	boost::system::error_code error;
	size_t len = 0;

	do
	{
		len = socket->write_some(boost::asio::buffer(msg, msg.size()), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	
	if (!error)
	{
		ret = true;
	}
	return ret;
}

/*Devuelve true si recibio un mensaje*/
bool connector::receiveMessage()
{
	bool ret = false;
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;

	do
	{
		len = socket->read_some(boost::asio::buffer(buf), error);
	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
	{
		buf[len] = '\0';
		ret = true;				//avisa que recibio un mensaje
		messageReceived = buf;	//guarda el mensaje recibido
	}
	return ret;
}


bool connector::messagePresent()
{
	return (messageReceived.size() != 0) ? true : false;
}

bool connector::isConnected()
{
	return connected;
}


string connector::getMessage()
{
	string temp = messageReceived;
	messageReceived.clear();
	return temp;
}

connector::~connector()
{
	socket->close();
	delete IO_handler;
	delete socket;
}
