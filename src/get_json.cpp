#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>
#include "factorio/mod-info.hpp"
#include <DA/exception.hpp>
#include <sstream>
#define AVHTTP_ENABLE_OPENSSL
#include <avhttp.hpp>
#ifdef DEBUG
	#include <iostream>
#endif
using namespace	boost::property_tree;

namespace factorio
{
namespace mod
{
	std::string info::get_script(std::string html) const
	try
	{
		ptree pt;
		std::stringstream ss(html);
		std::string json;
		while(std::getline(ss, json))
			if(json.find("window.__INITIAL_STATE__") != std::string::npos)
				break;
		json = json.substr(json.find('{'));
		json = json.substr(0, json.rfind('}') + 1);
		return json;
	}
	DA_CATCH_EXCEPTION
	avhttp::url info::get_url(std::string name) const
	try
	{
		using namespace std;
		stringstream ss;
		{
			std::string url = "https://mods.factorio.com/?q=";
			url += name;
	
			boost::asio::io_service io;
			avhttp::http_stream h(io);
			h.open(url);
	
			ss << &h;
		}
	
		stringstream json(get_script(ss.str()));
		#ifdef DEBUG
			AVHTTP_LOG_DBG << "search json:\n" << json.str();
		#endif
		ptree pt;
		read_json(json, pt);
	
		auto child = pt.get_child("mods.modsPages");
		for (const auto & i : child)
		{
			for (const auto & j : i.second)
			{
				if(j.second.get<string>("name") == name)
				{
					string result = "https://mods.factorio.com/mods/";
					result += j.second.get<string>("owner");
					result += "/";
					result += name;
					#ifdef DEBUG
						AVHTTP_LOG_DBG << "mod url:" << result;
					#endif
					return result;
				}
			}
		}
		DA_THROW_EXCEPTION_1("Can't found mod");
	}
	DA_CATCH_EXCEPTION
	ptree info::get_json(avhttp::url url) const
	try
	{
		using namespace std;
		boost::asio::io_service io;
		avhttp::http_stream h(io);
		h.open(url);

		stringstream ss;
		ss << &h;
		#ifdef DEBUG
			AVHTTP_LOG_DBG << "mod page:\n" << ss.str();
		#endif

		stringstream json(get_script(ss.str()));
		#ifdef DEBUG
			AVHTTP_LOG_DBG << "mod json:\n" << json.str();
		#endif
		ptree pt;
		read_json(json, pt);
		return pt;
	}
	DA_CATCH_EXCEPTION
	info::info(std::string name)
	try
	{
		pt = get_json(get_url(name)).get_child("mod.mod");
	}
	DA_CATCH_EXCEPTION
	void info::read_name(std::string name)
	try
	{
		pt = get_json(get_url(name)).get_child("mod.mod");
	}
	DA_CATCH_EXCEPTION
	void info::read_full_name(std::string name)
	try
	{
		pt = get_json("https://mods.factorio.com/mods/" + name).get_child("mod.mod");
	}
	DA_CATCH_EXCEPTION
	void info::read_url(std::string url)
	try
	{
		pt = get_json(url).get_child("mod.mod");
	}
	DA_CATCH_EXCEPTION
} /* mod */ 
} /* factorio */ 
