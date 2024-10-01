set_languages("c++20")
target("xbin")
    set_kind("binary")
    add_files("./*.cpp", "pinyinEncoder/*.cpp")
