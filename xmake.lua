set_xmakever("2.1.3")
set_languages("gnu++14")

target("factorio-mod-info")
	set_kind("shared")
	add_files("src/*.cpp") 
	add_headers("src/(factorio/*.hpp)")
	add_links("ssl", "pthread", "boost_date_time", "boost_system", "boost_filesystem")
	set_optimize("fastest")
	set_strip("all")
	set_warnings("none")
	add_defines("NDEBUG")
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

target("factorio-mod-info-dbg")
	set_kind("shared")
	add_files("src/*.cpp") 
	add_headers("src/(factorio/*.hpp)")
	add_links("ssl", "pthread", "boost_date_time", "boost_system", "boost_filesystem")
	set_symbols("debug")
	set_optimize("none")
	set_warnings("all")
	add_defines("DEBUG")
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
