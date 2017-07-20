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
  using pt::ptime;
  auto releases = pt.get_child("releases");
  std::regex reg(R"((2\d{3}(-\d{2}){2})T((\d{2}:){2}\d{2}.\d+)Z)");
  auto last_time = time_from_string(updated_at());
  struct
  {
    pt::time_duration time = pt::hours(24);
    ptree tree;
    void update(const pt::time_duration &t, const ptree &i)
    {
      if(t < time) {
        time = t;
        tree = i;
      }
    }
  }best;
  for (const auto & i : releases) {
    auto this_time = time_from_string(
        std::regex_replace(i.second.get<std::string>("released_at"),
          reg, R"($1 $3)"));
    auto dd = last_time - this_time;
    if(dd.is_negative()) dd = dd.invert_sign();
    best.update(dd, i.second);
  }
  return best.tree;
}
DA_CATCH
boost::property_tree::ptree info::get_releases(int id) const
try
{
  auto releases = pt.get_child("releases");
  for (const auto & i : releases) if(i.second.get<int>("id") == id) return i.second;
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
    if(i.second.get<std::string>("factorio_version") == factorio_version) list.insert(i.second.get<int>("id"));
  }
  #ifdef DEBUG
  {
    std::stringstream a;
    for (const auto & i : list) a << i << " ";
    AVHTTP_LOG_DBG << "id list:" << a.str();
  }
  #endif
  int latest = *list.begin();
  auto latest_time = time_from_string(
      std::regex_replace(get_releases(latest).get<std::string>("released_at"),
        reg, R"($1 $3)"));
  for (auto i : list)
  {
    decltype(time_from_string("")) tmp;
    if((tmp = time_from_string(
            std::regex_replace(get_releases(i).get<std::string>("released_at"),
              reg, R"($1 $3)")))
        > latest_time) {
      latest = i;
      latest_time = tmp;
    }
  }
  return get_releases(latest);
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
