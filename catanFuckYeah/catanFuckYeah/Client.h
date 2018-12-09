#pragma once

#include "connector.h"

#define SERVER_IP "localhost"

using namespace std;

class client : public connector
{
public:
	client();
	void startConnection(const char* host);
	virtual connectorType getType() { return CLIENT; };

private:
	boost::asio::deadline_timer deadline;
	boost::system::error_code error;
	bool hasToAsyncConnect;
};
