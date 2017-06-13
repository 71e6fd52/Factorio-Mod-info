#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "factorio/mod-info.hpp"
#include <DA/exception.hpp>
#include <unordered_set>
#ifdef DEBUG
	#include <iostream>
#endif
using namespace	boost::property_tree;

namespace factorio
{
namespace mod
{
	int info::id() const
	{
		return pt.get<int>("id");
	}
#define aaa(x)\
	std::string info::x() const \
	{\
		return pt.get<std::string>(#x);\
	}
	aaa(name);
	aaa(title);
	aaa(homepage);
	aaa(github_path);
	aaa(summary);
	aaa(owner);
	aaa(description);
	aaa(license_name);
	aaa(license_url);
	aaa(updated_at);
#undef aaa

#define aaa(x, y)\
	std::string info::download_url(x y) const\
	try\
	{\
		return "https://mods.factorio.com" + get_releases(y).get<std::string>("download_url");\
	}\
	DA_CATCH_EXCEPTION
	
	aaa(,);
	aaa(int, id);
	aaa(std::string, factorio_version);
#undef aaa

#define bbb(name, x, y)\
	std::string info::name(x y) const\
	try\
	{\
		return get_releases(y).get<std::string>(#name);\
	}\
	DA_CATCH_EXCEPTION
#define aaa(x)\
	bbb(x,,)\
	bbb(x,int, id)\
	bbb(x,std::string, factorio_version)\
	
	aaa(version);
	aaa(factorio_version);
#undef aaa

	avhttp::url info::mod_page() const
	{
		using avhttp::detail::escape_string;
		std::string result = "https://mods.factorio.com/mods/";
		result += escape_string(owner());
		result += "/";
		result += escape_string(name());
		return result;
	}
} /* mod */ 
} /* factorio */ 
