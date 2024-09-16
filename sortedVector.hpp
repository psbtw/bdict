#pragma once

#include <vector>
#include <algorithm>
#include <concepts>

// template<typename V>
// concept Insertable = requires(V v) {
//     v.insert();
// }

template<std::totally_ordered D, typename Comp=std::greater<D>> 
class SortedVector {

private:
    std::vector<D> vec;
public:
    void emplace_back(D d){
        vec.emplace_back(d);
    };
    void insert(D d){
        vec.emplace_back(d);
        std::sort(vec.begin(), vec.end(), Comp());
    }

};