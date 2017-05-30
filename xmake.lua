set_xmakever("2.1.3")
set_languages("gnu++14")

if is_mode("debug") then
	set_symbols("debug")
	set_optimize("none")
	set_warnings("all", "error")
	add_defines("DEBUG")
	add_undefines("NDEBUG")
end

if is_mode("release") then
	set_optimize("fastest")
	set_strip("all")
	set_warnings("none")
	add_defines("NDEBUG")
	add_undefines("DEBUG")
end

target("factorio-mod-info")
	set_kind("shared")
	add_files("src/*.cpp") 
	add_headers("src/**.hpp")
	add_links("ssl", "pthread", "boost_date_time", "boost_system", "boost_filesystem")
	before_build(function (target)
		if not os.exists("/usr/include/boost") then
			if io.stderr == nil then
				io.stderr = io.open("/dev/stderr", "a")
			end
			io.stderr:print("Need boost");
			io.stderr:print("Install it with package manager")
			io.stderr:print("Or http://www.boost.org/")
			os.exit(1);
		end
		if not (os.exists("/usr/include/avhttp") and os.exists("/usr/include/avhttp.hpp")) then
			if io.stderr == nil then
				io.stderr = io.open("/dev/stderr", "a")
			end
			io.stderr:print("Need avhttp");
			io.stderr:print("Install it with package manager")
			io.stderr:print("Or https://avplayer.org/avhttp.html")
			os.exit(1);
		end
		if not os.exists("/usr/include/DA/exception.hpp") then
			os.exec("sh -c \'cd $(scriptdir)/DA-exception && sudo ./install\'")
		end
	end)

