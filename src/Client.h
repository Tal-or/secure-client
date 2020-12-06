/*
 * Client.h
 *
 *  Created on: Sep 29, 2020
 *      Author: titzhak
 */

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <stdio.h>

#include "cURLpp.hpp"
#include "Easy.hpp"

class Client {
public:
	Client(std::string ip, uint16_t port);
	void Connect();
	void OldBasicImp(std::string ip, uint16_t port);

private:
	// call cURLpp::initialize in c-tor and cURLpp::terminate in d-tor
	static cURLpp::Cleanup cleanup;

	std::string m_serverIp;
	uint16_t m_serverPort;
	cURLpp::Easy m_handle;
};

#endif /* SRC_CLIENT_H_ */
