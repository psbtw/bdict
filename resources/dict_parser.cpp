#include <iostream>
#include <sstream>
#include <ifstream>
#include <vector>
#include <string>

#include "../bcommon/common/debug.hpp"
#include "hashMapDict.hpp"

struct WordEntry {
    std::string word;
    std::vector<std::string> pinyin;

    size_t freq;
};

// Function to parse the input text
std::vector<WordEntry> parseInput(const std::string& filePath) {
    std::vector<WordEntry> entries;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return entries; // Return empty vector on error
    }

    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        WordEntry entry;
        std::string pinyinPart;
        std::string freqPart;

        // Read the word
        lineStream >> entry.word;
        if (entry.word[0] == '#') {
            spdlog::trace("meet comment: {}", entry.word);
            continue;
        }

        // Read the pinyin (until the last part which is the frequency)
        while (lineStream >> pinyinPart) {
            if (std::isdigit(pinyinPart[0])) {
                freqPart = pinyinPart; // Last part is frequency
                break;
            }
            entry.pinyin.push_back(pinyinPart);
        }

        // Convert frequency to size_t
        entry.freq = std::stoul(freqPart);
        entries.push_back(entry);
    }

    return entries;
}

int main() {
//     std::string input = R"(
// 盛弘股份	sheng hong gu fen	185
// 胜红清热胶囊	sheng hong qing re jiao nang	6
// 圣湖	sheng hu	400
// 圣胡安	sheng hu an	910
// 圣湖社区	sheng hu she qu	4
// 生化	sheng hua	11414
// 0
// 升华	sheng hua	101545
// )";

    std::vector<WordEntry> parsedEntries = parseInput("./resources/dict.yml");

    // Output the parsed entries
    for (const auto& entry : parsedEntries) {
        std::cout << "Word: " << entry.word << ", Pinyin: ";
        for (const auto& p : entry.pinyin) {
            std::cout << p << " ";
        }
        std::cout << ", Frequency: " << entry.freq << std::endl;
    }

    return 0;
}
