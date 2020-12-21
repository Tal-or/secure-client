/*
 * Client.h
 *
 *  Created on: Sep 29, 2020
 *      Author: titzhak
 */

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <stdio.h>

#include "../curlpp/include/curlpp/cURLpp.hpp"
#include "../curlpp/include/curlpp/Easy.hpp"
#include "json.hpp"

using json = nlohmann::json;

class Client {
public:
	Client(std::string ip, uint16_t port);
	void Talk();
	void OldBasicImp(std::string ip, uint16_t port);
	friend void SendMsg(std::string);

private:
	// call cURLpp::initialize in c-tor and cURLpp::terminate in d-tor
	static cURLpp::Cleanup cleanup;

	std::string m_serverIp;
	uint16_t m_serverPort;
	cURLpp::Easy m_handle;
	json m_jMsg;
};

void SendMsg(std::string);

#endif /* SRC_CLIENT_H_ */
