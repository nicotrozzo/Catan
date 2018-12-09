#include "Server.h"


server::server()
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), PORT);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler, ep);
}

void server::startConnection()
{
	//Uncomment if non-blocking mode is desired
	//
	//When non-blocking mode is chosen accept operation
	//will fail with boost::asio::error::would_block
	//if there's no client inmediatelly connected when accept operation is performed.
	//Must comment blocking mode.
	//
	if (!connected)
	{
		server_acceptor->non_blocking(true);
		boost::system::error_code error;
		server_acceptor->accept(*socket, error);
		if (!error)
		{
			connected = true;
			socket->non_blocking(true);
		}
	}
}


server::~server()
{
	server_acceptor->close();
	delete server_acceptor;
}
