#include <iostream>

#include "vector_impl.hpp"

int main() {
	vector v (1);
	//v.reserve(10);
	std::cout << v.size() << " -- " << v.capacity() << "\n"; // '\n';
	
	for (int i = 0; i < 20; i++) {
		v.push_back(i + 10);
	}
	std::cout << v.size() << " -- " << v.capacity() << "\n"; // '\n';
	std::cout << v << '\n';
	vector a;
	a.push_back(999);
	a.push_back(888);
//	v.insert(0, a);
	std::cout << "After adding ";
	std::cout << v.size() << " -- " << v.capacity() << "\n"; // '\n';

	std::cout << v << '\n';

	v.insert(v.size()+2, a);
	std::cout << "After adding ";
	std::cout << v.size() << " -- " << v.capacity() << "\n"; // '\n';

	std::cout << v << '\n';

	//vector b = v;
	//std::cout << b << '\n';
	//vector c = std::move(b);
	//std::cout << "c = " << c << '\n';
	//b = std::move(c);

//	std::cout << "b = " << b << '\n';
	
	std::cout << '\n';
}
