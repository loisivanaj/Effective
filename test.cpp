#include <iostream>

// auto replaces in a template
template<typename T>
void function(T param) {}
// so in the below case, the ref and const both get clapped

int main()
{
	int x = 28;
	const int& rx = x;
	auto rrx = rx;
	std::cout << std::is_same_v<decltype(rrx), int> << '\n';
}
