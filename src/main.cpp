/*
 * main.cpp
 *
 *  Created on: Dec 5, 2020
 *      Author: titzhak
 */

#include "Client.h"

int main(int argc, char *argv[])
{
	Client client("172.27.16.243", 1234);
	client.Connect();
	return 0;
}
