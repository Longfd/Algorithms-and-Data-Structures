#pragma once

#include <iostream>
#include <string>

class illegalParameterValue
{
public:
	illegalParameterValue() :
		_message("Illegal parameter value"){}

	illegalParameterValue(const char* message):
		_message(message) {}
	illegalParameterValue(const std::string& message) :
		_message(message) {}

	void outputMessage() { std::cout << _message << std::endl; }

	const std::string& what() { return _message; }

private:
	std::string _message;
};
