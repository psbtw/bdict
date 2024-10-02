#include "parser.hpp"

void PinyinParser::init_base_map()
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
}
