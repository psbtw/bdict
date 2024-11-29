#pragma once

#include "types.hpp"
#include <unordered_map>
#include "../../bcommon/container/graph.hpp"
#include <string>
#include <string_view>

namespace Pinyin {

class PinyinParser {

private:
    PinyinMap _all_map, _base_map, _fuzzy_map;
    AlphabetMap _alphabet_map;
    ParseRef _parse_ref;
    

public:
    vector<vector<Alphabet>> StringToAlphabet(string& str);
    PinyinParser();
    void SetFuzzyFlags(vector<FuzzyFlag> &v);
    vector<PinyinVec> Parse(const string& s);

    Alphabet ParseAlphabet(string_view& s){
        auto ret = Alphabet::FinalEnd;
        // if (_base_map.count(s)) {
        //     ret = _base_map[s];
        // }
        return ret;
    }
    void ParseToGraph(Graph<AlphaMark, MarkKey>& g, const string& src,  size_t start_pos = 0, GraphNode<AlphaMark>* cur = nullptr);

private:
    void splitBaseMap();
    const PinyinMap& getAllMap();
    const PinyinMap& getBaseMap();
    void init_base_map();
    void initAlphabetMap();
    void init_parse_map(){
        _parse_ref = move(ParseRef{
            {"b", {{"b"}}},
            {"p", {{"p"}}},
            {"m", {{"m"}}},
            {"f", {{"f"}}},
            {"d", {{"d"}}},
            {"t", {{"t"}}},
            {"n", {{"n"}}},
            {"l", {{"l"}}},
            {"g", {{"g"}}},
            {"k", {{"k"}}},
            {"h", {{"h"}}},
            {"j", {{"j"}}},
            {"q", {{"q"}}},
            {"x", {{"x"}}},
            {"zh", {{"zh"}}},
            {"ch", {{"ch"}}},
            {"sh", {{"sh"}}},
            {"r", {{"r"}}},
            {"z", {{"z"}}},
            {"c", {{"c"}}},
            {"s", {{"s"}}},
            {"y", {{"y"}}},
            {"w", {{"w"}}},
            {"a", {{"a"}}},
            {"o", {{"o"}}},
            {"e", {{"e"}}},
            {"i", {{"i"}}},
            {"u", {{"u"}}},
            {"v", {{"v"}}},
            {"ai", {{"ai"}}},
            {"ei", {{"ei"}}},
            {"ui", {{"ui"}}},
            {"ao", {{"ao"}}},
            {"ou", {{"ou"}}},
            {"iu", {{"iu"}}},
            {"ie", {{"ie"}}},
            {"ve", {{"ve"}}},
            {"er", {{"er"}}},
            {"an", {{"an"}}},
            {"en", {{"en"}}},
            {"in", {{"in"}}},
            {"un", {{"un"}}},
            {"vn", {{"vn"}}},
            {"ang", {{"ang"}}},
            {"eng", {{"eng"}}},
            {"ing", {{"ing"}}},
            {"ong", {{"ong"}}},
        });
    }


};

}
