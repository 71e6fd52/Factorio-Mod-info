#include "factorio/mod-info.hpp"

#include <DA/exception.hpp>
#include <avhttp/logging.hpp>
#include <boost/date_time.hpp>
#include <boost/property_tree/ptree.hpp>

#include <map>
#include <regex>
#include <unordered_set>

#ifdef DEBUG
  #include <iostream>
  #include <sstream>
#endif

using ::boost::property_tree::ptree;
namespace pt = ::boost::posix_time;
using pt::time_from_string;

namespace factorio
{
namespace mod
{
boost::property_tree::ptree info::get_releases() const
try
{
  auto releases = pt.get_child("releases");
  return releases.begin()->second;
}
DA_CATCH
boost::property_tree::ptree info::get_releases(int id) const
try
{
  auto releases = pt.get_child("releases");
  for (const auto & i : releases) {
    if(i.second.get<int>("id") == id) return i.second;
  }
  DA_THROW_1("can't found releases");
}
DA_CATCH
boost::property_tree::ptree info::get_releases(const std::string &factorio_version) const
try
{
  auto releases = pt.get_child("releases");
  std::regex reg(R"((2\d{3}(-\d{2}){2})T((\d{2}:){2}\d{2}.\d+)Z)");
  std::unordered_set<int> list;
  for (const auto & i : releases) {
    if(i.second.get<std::string>("factorio_version") == factorio_version) {
      return i.second;
    }
  }
  DA_THROW_1("can't found releases");
}
DA_CATCH

std::unordered_set<int> info::id_list() const
try
{
  auto releases = pt.get_child("releases");
  std::unordered_set<int> list;
  for (const auto & i : releases)
  {
    list.insert(i.second.get<int>("id"));
  }
  #ifdef DEBUG
  {
    std::stringstream a;
    for (const auto & i : list) a << i << " ";
    AVHTTP_LOG_DBG << "id list:" << a.str();
  }
  #endif
  return list;
}
DA_CATCH

} // namespace mod
} // namespace factorio
