#pragma once

#include "connector.h"

using namespace std;

class server : public connector
{
public:
	server();
	bool startConnection();
	virtual connectorType getType() { return SERVER; }
	~server();

private:
	boost::asio::ip::tcp::acceptor* server_acceptor;
};
