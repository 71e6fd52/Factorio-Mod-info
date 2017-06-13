#include "factorio/mod-info.hpp"
namespace factorio
{
namespace mod
{
	bool operator == (info lhs, info rhs)
	{
		return lhs.name() == rhs.name();
	}
} /* mod */ 
} /* factorio */ 
