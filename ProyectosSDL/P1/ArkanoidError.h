#pragma once

#include <stdexcept>

using namespace std;

class ArkanoidError:public logic_error{
public:
	//ArkanoidError():logic_error() {};
	~ArkanoidError() {};

	//what();
};

