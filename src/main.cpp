/*
 * main.cpp
 *
 *  Created on: Dec 5, 2020
 *      Author: titzhak
 */

#include "Client.h"
#include <stdio.h>
#include <iostream>
#include <string>

void getUsrInput()
{
	std::string input;
	std::cout << "\nPlease enter your input or 'q' for quit" << std::endl;
	std::getline(std::cin >> std::ws, input);

	if(input.compare("q") == 0)
		exit(0);

	SendMsg(input);


}
int main(int argc, char *argv[])
{
	while(true)
		getUsrInput();
	return 0;
}
