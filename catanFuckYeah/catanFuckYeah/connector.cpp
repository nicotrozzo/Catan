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
bool connector::sendMessage(const char * msg, size_t length_)
{
	bool ret = false;
	boost::system::error_code error;
	size_t length = 0;

	do
	{
		length = socket->write_some(boost::asio::buffer(msg, length_), error);
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
	len = 0;
	messageRead = false;
	do
	{
		len = socket->read_some(boost::asio::buffer(buf), error);
	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
	{
		ret = true;				//avisa que recibio un mensaje
	}
	return ret;
}


bool connector::messagePresent()
{
	bool ret = false;
	if (!messageRead && len != 0)
	{
		ret = true;
	}
	return ret;
}

bool connector::isConnected()
{
	return connected;
}


char * connector::getMessage()
{
	messageRead = true;
	return buf;
}

size_t connector::getMessageLenght()
{
	return len;
}

connector::~connector()
{
	socket->close();
	delete IO_handler;
	delete socket;
}
