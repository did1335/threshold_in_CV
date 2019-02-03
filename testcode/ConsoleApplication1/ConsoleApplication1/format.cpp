#include "function.h"

string int2String(int number) 
{	
	std::stringstream ss;
	ss << number;
	return ss.str();
}
