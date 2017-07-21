set_xmakever("2.1.3")

set_languages("gnuxx14")
set_kind("shared")

add_files("src/*.cpp")
add_links("ssl", "pthread", "boost_date_time", "boost_system", "boost_filesystem")
add_includedirs("$(projectdir)/include")

before_build(function (target)
  assert(os.isdir("/usr/include/boost"), "Need boost\nInstall it with package manager\nOr visit http://www.boost.org/")
  assert(os.isdir("/usr/include/avhttp") and os.exists("/usr/include/avhttp.hpp"), "Need avhttp\nOr visit https://avplayer.org/avhttp.html")
  if not os.exists("/usr/include/DA/exception.hpp") then
    os.exec("sh -c \'cd $(scriptdir)/DA-exception && sudo ./install\'")
  end
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
