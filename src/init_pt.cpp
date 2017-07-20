#include "factorio/mod-info.hpp"

#include <DA/exception.hpp>
#include <avhttp.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>
#include <sstream>
#include <utility>

#ifdef DEBUG
  #include <iostream>
#endif

using boost::property_tree::ptree;
using avhttp::detail::escape_string;

namespace factorio
{
namespace mod
{
namespace
{
std::string get_script(const std::string &html)
try
{
  ptree pt;
  std::stringstream ss(html);
  std::string json;
  while(std::getline(ss, json)) {
    if(json.find("window.__INITIAL_STATE__") != std::string::npos) break;
  }
  json = json.substr(json.find('{'));
  json = json.substr(0, json.rfind('}') + 1);
  return json;
}
DA_CATCH_EXCEPTION

ptree search(const std::string &name)
try
{
  std::stringstream ss;
  {
    std::string url = "https://mods.factorio.com/?q=";
    url += escape_string(name);

    boost::asio::io_service io;
    avhttp::http_stream h(io);
    h.open(url);

    ss << &h;
  }

  std::stringstream json(get_script(ss.str()));
  AVHTTP_LOG_DBG << "search json:\n" << json.str();
  ptree pt;
  read_json(json, pt);

  auto child = pt.get_child("mods.modsPages");
  for (const auto & i : child) {
    for (const auto & j : i.second) {
      if(j.second.get<std::string>("name") == name) {
        return j.second;
      }
    }
  }
  DA_THROW_EXCEPTION_1("Can't found mod");
}
DA_CATCH_EXCEPTION

ptree search_blurry(const std::string &name)
try
{
  std::stringstream ss;
  {
    std::string url = "https://mods.factorio.com/?q=";
    url += escape_string(name);

    boost::asio::io_service io;
    avhttp::http_stream h(io);
    h.open(url);

    ss << &h;
  }

  std::stringstream json(get_script(ss.str()));
  AVHTTP_LOG_DBG << "search json:\n" << json.str();
  ptree pt;
  read_json(json, pt);

  auto child = pt.get_child("mods.modsPages");
  return child.begin()->second.begin()->second;
}
DA_CATCH_EXCEPTION

ptree get_json(const avhttp::url &url)
try
{
  boost::asio::io_service io;
  avhttp::http_stream h(io);
  h.open(url);

  std::stringstream ss;
  ss << &h;
  AVHTTP_LOG_DBG << "mod page:\n" << ss.str();

  std::stringstream json(get_script(ss.str()));
  AVHTTP_LOG_DBG << "mod json:\n" << json.str();
  ptree pt;
  read_json(json, pt);
  return pt;
}
DA_CATCH_EXCEPTION
} // namespace


info::info(const std::string& name)
try
{
  read_name(name);
}
DA_CATCH_EXCEPTION
info info::read_name(const std::string& name)
try
{
  read_name_fast(name);
  read_url(mod_page());
  return *this;
}
DA_CATCH_EXCEPTION
info info::read_name_fast(const std::string& name)
try
{
  pt = mod::search(name);
  return *this;
}
DA_CATCH_EXCEPTION
info info::search(const std::string& name)
try
{
  pt = search_blurry(name);
  return *this;
}
DA_CATCH_EXCEPTION
info info::read_full_name(const std::string& name)
try
{
  pt = get_json("https://mods.factorio.com/mods/" + name).get_child("mod.mod");
  return *this;
}
DA_CATCH_EXCEPTION
info info::read_url(const avhttp::url& url)
try
{
  pt = get_json(url).get_child("mod.mod");
  return *this;
}
DA_CATCH_EXCEPTION
} // namespace mod
} // namespace factorio
