#pragma once
#include <forward_list>

template<typename type>
struct DNA
{
	std::forward_list<type> genom;
	int mark;

	DNA(): mark(), genom() {}
};