#include "hashMapDict.hpp"
#include "dict_parser.hpp"

void testBinSearch(int k) {
    vector<int> v{1,2,3,4,5,6};
    auto p = bin_search<int>(&v[0], k, &v[5]);
    if (p != nullptr) {
        cout << *p<<endl;
    } else {
        cout << k << " not in vec\n";
    }
    
}

int main(int argc, char* argv[]) {
    mergeDict("resources/dict.yml", "resources/sgDict.txt", "resources/new_dict.yml");
    //testHashMapDict(argc, argv);
    return 0;
}
