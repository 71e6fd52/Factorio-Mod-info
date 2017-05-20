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

	std::string get_script(std::string html);
	avhttp::url get_url(std::string name);
	boost::property_tree::ptree get_json(avhttp::url url);
	boost::property_tree::ptree get_releases();
	boost::property_tree::ptree get_releases(int id);
	boost::property_tree::ptree get_releases(std::string factorio_version);

public:
	info() = default;
	info(std::string name);
	void read_name(std::string name);
	void read_full_name(std::string name);
	void read_url(std::string url);

	int id();
	std::string name();
	std::string title();
	std::string homepage();
	std::string github_path();
	std::string summary();
	std::string owner();
	std::string description();
	std::string license_name();
	std::string license_url();
	std::string updated_at();

	std::unordered_set<int> id_list();

#define aaa(x)\
	std::string x() throw (DA::exception);\
	std::string x(int id) throw (DA::exception);
	
	aaa(download_url);
	std::string download_url(std::string factorio_version) ;//throw (DA::exception);
	aaa(version);
	aaa(factorio_version);
#undef aaa

};
} /* mod */ 
} /* factorio */ 
