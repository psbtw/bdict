set_languages("c++20")
add_rules("mode.debug")
set_config("mode", "debug")
--add_cxxflags("--verbose")
target("a.out")
    set_kind("binary")
    add_files( "pinyinEncoder/*.cpp", "./*.cpp")
