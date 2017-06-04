#include "factorio/mod-info.hpp"
#ifdef ENABLE_YAML_CPP 
	#include <yaml-cpp/yaml.h>
#endif
namespace factorio
{
namespace mod
{
#ifdef ENABLE_YAML_CPP
	YAML::Emitter& operator << (YAML::Emitter& out, const factorio::mod::info & mod)
	{
		using namespace YAML;
		out << Key << mod.name() << Value << (mod.github_path() == "" ? "file" : "git");
		return out;
	}
#endif
	bool operator == (info lhs, info rhs)
	{
		return lhs.name() == rhs.name();
	}
} /* mod */ 
} /* factorio */ 
