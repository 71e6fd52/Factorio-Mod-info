set_xmakever("2.1.3")

set_languages("gnuxx14")
set_kind("shared")

add_files("src/*.cpp")
add_links("ssl", "pthread", "boost_date_time", "boost_system", "boost_filesystem")
add_includedirs("$(projectdir)/include")

before_build(function (target)
  --assert(os.host() == "linux", "Maybe you can help me to support other system")
  if (os.exists("/usr/bin/pacaur")) then
    cprint("${bright}Why not use `pacaur -S factorio-mod-info`")
    cprint("${bright}If you still want to build, you can run `pacaur -S boost avhttp-git da-exception-git` to install depends")
  end
  assert(os.isdir("/usr/include/boost"), "Need boost\nInstall it with package manager\nOr visit http://www.boost.org/")
  assert(os.isdir("/usr/include/avhttp") and os.exists("/usr/include/avhttp.hpp"), "Need avhttp\nVisit https://avplayer.org/avhttp.html")
  assert(os.exists("/usr/include/DA/exception.hpp"), "Need DA-exception\nVisit https://github.com/DATechnologyStudio/DA-exception")
end)

target("factorio-mod-info")
  set_optimize("fastest")
  set_strip("all")
  set_warnings("none")
  add_defines("NDEBUG")
  add_headers("include/(factorio/*.hpp)")
target_end()

target("factorio-mod-info-dbg")
  set_symbols("debug")
  set_optimize("none")
  set_warnings("all")
  add_defines("DEBUG")
target_end()
