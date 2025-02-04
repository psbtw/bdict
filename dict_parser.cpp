#include "dict_parser.hpp"

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

unordered_map<string, string>* parseFreqDict(const string& src){
    std::ifstream file(src);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return nullptr; // Return empty vector on error
    }

    auto ret = new unordered_map<string, int>();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        string id;
        std::string word;
        std::string freqPart;

        lineStream >> id;
        // Read the word
        lineStream >> word;
        lineStream >> freqPart;
        ret[word] = freqPart;
    }
    return ret;
}

void mergeDict(const string& src, const string& ref, const string& dst) {
    auto refMap = parseFreqDict(ref);

    std::ofstream ret(dst);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << dst << std::endl;
    }

    std::ifstream file(src);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << src << std::endl;
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
        if (!refMap.count(entry.word)) {
            continue;
        }
        ret << entry.word << "\t";

        // Read the pinyin (until the last part which is the frequency)
        while (lineStream >> pinyinPart) {
            if (std::isdigit(pinyinPart[0])) {
                freqPart = pinyinPart; // Last part is frequency
                string c;
                ret >> c; // tail " "
                break;
            }
            //entry.pinyin.emplace_back(pinyinPart);
            ret << pinyinPart << " ";
        }
        ret << "\t" << refMap[entry.word] << endl;
    }
}

int testDictParser() {

    auto parsedEntries = parseInput("./resources/dict.yml");

    // Output the parsed entries
    for (const auto& entry : *parsedEntries) {
        std::cout << "Word: " << entry.word << ", Pinyin: ";
        for (const auto& p : entry.pinyin) {
            std::cout << p << " ";
        }
        std::cout << ", Frequency: " << entry.freq << std::endl;
    }
    delete parsedEntries;
    return 0;
}
