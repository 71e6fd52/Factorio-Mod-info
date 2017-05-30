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

	std::string get_script(std::string html) const;
	avhttp::url get_url(std::string name) const;
	boost::property_tree::ptree get_json(avhttp::url url) const;
	boost::property_tree::ptree get_releases() const;
	boost::property_tree::ptree get_releases(int id) const;
	boost::property_tree::ptree get_releases(std::string factorio_version) const;

public:
	info() = default;
	info(std::string name);
	void read_name(std::string name);
	void read_full_name(std::string name);
	void read_url(std::string url);

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

	std::unordered_set<int> id_list() const;

#define aaa(x)\
	std::string x() const throw (DA::exception);\
	std::string x(int id) const throw (DA::exception);\
	std::string x(std::string factorio_version) const throw (DA::exception);
	
	aaa(download_url);
	aaa(version);
	aaa(factorio_version);
#undef aaa

};
} /* mod */ 
} /* factorio */ 
