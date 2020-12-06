/*
 * Client.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: titzhak
 */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>

#include "Client.h"
#include "Options.hpp"

namespace {
constexpr int max_buf_sz = 4096;
const std::string lo = "127.0.0.1";
}

using namespace std;

int writeDebug(curl_infotype, char *data, size_t size)
{
	fprintf(stderr, "Debug: ");
	fwrite(data, size, 1, stderr);
	return size;
}

Client::Client(std::string ip, uint16_t port): m_serverIp(ip), m_serverPort(port)
{
	using namespace curlpp::options;
	m_handle.setOpt<Url>("172.27.16.243");
	m_handle.setOpt<Port>(1234);
}

void Client::Connect()
{

	try
	{
		m_handle.perform();
	}
	catch(curlpp::RuntimeError & e)
	{
		std::cout << e.what() << std::endl;
	}

	catch(curlpp::LogicError & e)
	{
		std::cout << e.what() << std::endl;
	}
}


void Client::OldBasicImp(string ip, uint16_t port)
{
	int sckfd {};
	struct addrinfo ai {};
	size_t ailen = sizeof(struct sockaddr_in);
	struct sockaddr_in s {};
	char buf[max_buf_sz] {};
	int numOfBytes {};
	string serverAddr(lo);

	if (ip.size())
		serverAddr.assign(ip);

	s.sin_family = AF_INET;
	s.sin_port = htons(port);

	inet_pton(s.sin_family, serverAddr.c_str(), &s.sin_addr);
	ai.ai_addr = reinterpret_cast<struct sockaddr*>(&s);

	if ((sckfd = socket(s.sin_family, SOCK_STREAM, 0)) == -1)
		perror("client: socket");

	if (connect(sckfd, ai.ai_addr, ailen) == -1) {
		close(sckfd);
		perror("client: connect");
	}

	cout << "client: successfully connected to:" << serverAddr << endl;

	while(true){
		numOfBytes = recv(sckfd, buf, max_buf_sz, 0);
		buf[numOfBytes] = '\0';

		cout << "client: received'" << buf << "'" << endl;
	}
	close(sckfd);
}
