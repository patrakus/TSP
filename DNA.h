#pragma once
#include <forward_list>

template<typename type>
struct DNA
{
	std::vector<type> genom;
	unsigned long long int mark;

	DNA(): mark(), genom() {}
};