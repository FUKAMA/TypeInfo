#include "TypeID/Allocator/TypeIDAllocator.h"

namespace stl
{
	void TypeIDAllocator::Allocate(std::string_view a_keyName)
	{
		TypeID nID = ++m_counter;
		m_umNameToTypeID[a_keyName.data()] = nID;
	}
}