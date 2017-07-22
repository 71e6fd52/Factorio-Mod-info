#ifndef FACTORIO_MOD_INFO_H
#define FACTORIO_MOD_INFO_H

#define AVHTTP_ENABLE_OPENSSL
#include <avhttp/url.hpp>
#include <boost/property_tree/ptree.hpp>
#include <unordered_set>
namespace factorio
{
namespace mod
{
class info final
{
private:
  boost::property_tree::ptree pt;

  //boost::property_tree::ptree get_json(avhttp::url url) const;
  boost::property_tree::ptree get_releases() const;
  boost::property_tree::ptree get_releases(int id) const;
  boost::property_tree::ptree get_releases(const std::string& factorio_version) const;

public:
  info() = default;
  info(const info&) = default;
  info &operator=(const info&) = default;
  info (info && r) noexcept(false) = default;
  info &operator=(info&&) noexcept(false) = default;
  ~info() = default;
  [[deprecated]] explicit info(const std::string& name);

  info read_name(const std::string& name);
  info read_name_fast(const std::string& name);
  info search(const std::string& name);
  info read_full_name(const std::string& name);
  info read_url(const avhttp::url& url);

  int id() const;

  #define a(x)\
  [[nodiscard]] std::string x() const
    a(name);
    a(title);
    a(homepage);
    a(github_path);
    a(summary);
    a(owner);
    a(description);
    a(license_name);
    a(license_url);
    a(updated_at);
  #undef a
  avhttp::url mod_page() const;

  std::unordered_set<int> id_list() const;

  #define a(x)\
    std::string x() const;\
    std::string x(int id) const;\
    std::string x(const std::string& factorio_version) const;
    a(download_url);
    a(version);
    a(factorio_version);
  #undef a

};
bool operator == (const info& lhs, const info& rhs);
} // namespace mod
} // namespace factorio

#endif /* end of include guard: FACTORIO_MOD_INFO_H */
