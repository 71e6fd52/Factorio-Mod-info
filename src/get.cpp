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
	int info::id()
	{
		return pt.get<int>("id");
	}
#define aaa(x)\
	std::string info::x() \
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
	std::string info::download_url(x y) throw(DA::exception)\
	try\
	{\
		return "https://mods.factorio.com" + get_releases(y).get<std::string>("download_url");\
	}\
	DA_CATCH_EXCEPTION
	
	aaa(,);
	aaa(int, id);
	aaa(std::string, factorio_version);
#undef aaa

#define aaa(x)\
	std::string info::x() throw (DA::exception)\
	try\
	{\
		return get_releases().get<std::string>(#x);\
	}\
	DA_CATCH_EXCEPTION\
	std::string info::x(int id) throw (DA::exception)\
	try\
	{\
		return get_releases(id).get<std::string>(#x);\
	}\
	DA_CATCH_EXCEPTION\
	std::string info::x(std::string factorio_version) throw (DA::exception)\
	try\
	{\
		return get_releases(factorio_version).get<std::string>(#x);\
	}\
	DA_CATCH_EXCEPTION
	
	aaa(version);
	aaa(factorio_version);
#undef aaa
} /* mod */ 
} /* factorio */ 
