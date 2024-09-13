#include <stddef.h>
#include <unordered_map>

template<typename T>
concept ArrayType = requires(T t){
    t[0];
    t.size();
};

template<typename K, typename V>
requires ArrayType<K>
// K type require operator ==
class HashMapTree
{
private:
    K key;
    V value;
    std::unordered_map<K,HashMapTree<K,V>*> sub;
public:
    HashMapTree(K k,V v);
    ~HashMapTree();
    HashMapTree* find(K& key, int&);
    bool insert(K& key, V& value);
};


