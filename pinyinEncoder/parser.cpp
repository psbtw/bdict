#include "parser.hpp"

void PinyinParser::init_base_map()
{
    unordered_map<string, vector<PinyinSyllable>> base_map = {
        {"a", {PinyinAlphabet::A}},
        {"o", {PinyinAlphabet::O}}
    };
}

std::vector<PinyinAlphabet> PinyinParser::StringToAlphabet(std::string &str)
{
    std::vector<PinyinAlphabet> ret;
    return ret;
}
