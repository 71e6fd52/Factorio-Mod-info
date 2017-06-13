#include <boost/property_tree/ptree.hpp>
#include <unordered_set>
#include <avhttp/url.hpp>
#include <DA/exception.hpp>
namespace factorio
{
namespace mod
{
class info final
{
private:
	boost::property_tree::ptree pt;

	boost::property_tree::ptree get_json(avhttp::url url) const;
	boost::property_tree::ptree get_releases() const;
	boost::property_tree::ptree get_releases(int id) const;
	boost::property_tree::ptree get_releases(std::string factorio_version) const;

public:
	info() = default;
	info(info const &) = default;

	info(std::string name);
	info read_name(std::string name);
	info read_name_fast(std::string name);
	info read_full_name(std::string name);
	info read_url(avhttp::url url);

	int id() const;
	std::string name() const;
	std::string title() const;
	std::string homepage() const;
	std::string github_path() const;
	std::string summary() const;
	std::string owner() const;
	std::string description() const;
	std::string license_name() const;
	std::string license_url() const;
	std::string updated_at() const;

	avhttp::url mod_page() const;

	std::unordered_set<int> id_list() const;

#define aaa(x)\
	std::string x() const;\
	std::string x(int id) const;\
	std::string x(std::string factorio_version) const;
	
	aaa(download_url);
	aaa(version);
	aaa(factorio_version);
#undef aaa

};
bool operator == (info lhs, info rhs);
} /* mod */ 
} /* factorio */ 
