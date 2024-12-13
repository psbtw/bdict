#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "../bcommon/common/debug.hpp"
#include "hashMapDict.hpp"

// Function to parse the input text
std::vector<WordEntry>* parseInput(const std::string& filePath) {
    auto entries = new std::vector<WordEntry>();
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return entries; // Return empty vector on error
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        WordEntry entry;
        std::string pinyinPart;
        std::string freqPart;

        // Read the word
        lineStream >> entry.word;
        if (entry.word[0] == '#') {
            //spdlog::trace("meet comment: {}", entry.word);
            continue;
        }

        // Read the pinyin (until the last part which is the frequency)
        while (lineStream >> pinyinPart) {
            if (std::isdigit(pinyinPart[0])) {
                freqPart = pinyinPart; // Last part is frequency
                break;
            }
            entry.pinyin.emplace_back(pinyinPart);
        }

        // Convert frequency to size_t
        entry.freq = std::stoul(freqPart);
        entries->emplace_back(entry);
    }

    return entries;
}

// int main() {

//     auto parsedEntries = parseInput("./resources/dict.yml");

//     // Output the parsed entries
//     for (const auto& entry : *parsedEntries) {
//         std::cout << "Word: " << entry.word << ", Pinyin: ";
//         for (const auto& p : entry.pinyin) {
//             std::cout << p << " ";
//         }
//         std::cout << ", Frequency: " << entry.freq << std::endl;
//     }
//     delete parsedEntries;
//     return 0;
// }
