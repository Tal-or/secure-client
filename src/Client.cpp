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
#include <fstream>

#include "Client.h"
#include "Options.hpp"


namespace {
constexpr int maxBuffSz = 4096;
const std::string lo = "127.0.0.1";
constexpr int ServerPort = 25000;
const std::string credentials = "seminar:20928";
}

using json = nlohmann::json;
using namespace curlpp::options;

Client::Client(std::string ip, uint16_t port): m_serverIp(ip), m_serverPort(port)
{
	std::list<std::string> header;
	header.push_back("Content-Type: application/json");

	// HTTP options
	m_handle.setOpt<HttpHeader>(header);
	m_handle.setOpt<HttpVersion>(CURL_HTTP_VERSION_1_1);

#ifdef debug
		m_handle.setOpt(Verbose(true));
#endif

    // Network options
    std::string url("https://");
    url.append(m_serverIp);
	m_handle.setOpt<Url>(url);
	m_handle.setOpt<Port>(m_serverPort);
	m_handle.setOpt<TcpNoDelay>(true);

	// SSL options
	m_handle.setOpt<SslCertType>("PEM");
    m_handle.setOpt<CaInfo>("../secure-server/cacert.pem");
    m_handle.setOpt<SslVerifyHost>(true);
    m_handle.setOpt(new cURLpp::Options::UserPwd(credentials));

    // Protocol options.
    m_handle.setOpt<Timeout>(7);

}

void Client::Talk()
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

void Client::OldBasicImp(std::string ip, uint16_t port)
{
	int sckfd{};
	struct addrinfo ai{};
	size_t ailen = sizeof(struct sockaddr_in);
	struct sockaddr_in s{};
	char buf[maxBuffSz]{};
	int numOfBytes{};
	std::string serverAddr(lo);

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

	std::cout << "client: successfully connected to:" << serverAddr << std::endl;

	while(true){
		numOfBytes = recv(sckfd, buf, maxBuffSz, 0);
		buf[numOfBytes] = '\0';

		std::cout << "client: received'" << buf << "'" << std::endl;
	}
	close(sckfd);
}

void SendMsg(std::string msg)
{
	Client c("localhost", ServerPort);
	c.m_jMsg["cmd"] = msg;
	c.m_handle.setOpt<PostFields>(c.m_jMsg.dump());
	c.Talk();

}
