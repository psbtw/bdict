#include "parser.hpp"
#include <cstring>

void PinyinParser::init_base_map()
{
    _base_map = move(unordered_map<string_view, vector<PinyinAlphabet>>{
        {"a", {PinyinAlphabet::A}},
        {"o", {PinyinAlphabet::O}},
        {"e", {PinyinAlphabet::E}},
        {"i", {PinyinAlphabet::I}},
        {"u", {PinyinAlphabet::U}},
        {"v", {PinyinAlphabet::V}},
        {"uang", {PinyinAlphabet::UANG}},
    });
}

vector<vector<PinyinAlphabet>> PinyinParser::StringToAlphabet(std::string &str)
{
    vector<vector<PinyinAlphabet>> ret; //n*m fuzzy combinations

    //check from initial to initial
    


    return ret;
}

PinyinParser::PinyinParser()
{
     _base_map = move(unordered_map<string, vector<PinyinAlphabet>>{
        {"a", {PinyinAlphabet::A}},
        {"o", {PinyinAlphabet::O}},
        {"e", {PinyinAlphabet::E}},
        {"i", {PinyinAlphabet::I}},
        {"u", {PinyinAlphabet::U}},
        {"v", {PinyinAlphabet::V}},
        {"uang", {PinyinAlphabet::UANG}},
    });

    _fuzzy_set = move(unordered_map<PinyinFuzzyFlag, unordered_map<string, vector<PinyinAlphabet>>> {
        {
            PinyinFuzzyFlag::AN_ANG, 
            {
                {"an",{PinyinAlphabet::AN, PinyinAlphabet::ANG}},
                {"ang",{PinyinAlphabet::AN, PinyinAlphabet::ANG}},
            }
        },
        {
            PinyinFuzzyFlag::L_N, 
            {
                {"l",{PinyinAlphabet::L, PinyinAlphabet::N}},
                {"n",{PinyinAlphabet::L, PinyinAlphabet::N}},
            }
        },

    });
}

void PinyinParser::SetFuzzyFlags(vector<PinyinFuzzyFlag> &v) {
    for (auto flag : v) {
        if (_fuzzy_set.count(flag)) {
            for (auto s : _fuzzy_set[flag]) {
                _fuzzy_map[s.first] = s.second;
            }
        } else {
            // not pre-defined
        }

    }
}

const size_t SyllableMaxLen = 6;
vector<PinyinVec>& PinyinParser::Parse(const string &s)
{
    auto ret = vector<PinyinVec>();
    auto len = s.size();
    for (auto i=0; i<len; ++i) {
        for (auto j=i; j<i+SyllableMaxLen; ++j) {
            
        }
    }

}
