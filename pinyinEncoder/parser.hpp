#include "consts.hpp"
#include <unordered_map>


class PinyinParser {

private:
    unordered_map<string, vector<PinyinAlphabet>> _base_map; //always there
    unordered_map<string, vector<PinyinAlphabet>> _fuzzy_map; //added optionally
    unordered_map<PinyinFuzzyFlag, vector<PinyinAlphabet>> _fuzzy_set; //predefined

    void init_base_map();

public:
    vector<vector<PinyinAlphabet>> StringToAlphabet(std::string& str);
    PinyinParser();

};

