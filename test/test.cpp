#include "TypeRegistry.h"
#include <iostream>

int main()
{
	stl::TypeIDAllocator all;
	stl::TypeID aaa = stl::GetTypeID<int>(all);
	std::cout << aaa << std::endl;
	aaa = stl::GetTypeID<int>(all);
	std::cout << aaa << std::endl;
	aaa = stl::GetTypeID<float>(all);
	std::cout << aaa << std::endl;
	aaa = stl::GetTypeID<int>(all);
	std::cout << aaa << std::endl;
	aaa = stl::GetTypeID<int>(all);
	std::cout << aaa << std::endl;
}
