#include "../common/common.hpp"
#include <vector>

template<typename N>
class Graph
{
    using Node = N;
private:
    /* data */
    Node* _root;
public:
    Graph(/* args */);
    ~Graph();

    vector<Node*> DFS(){

    }
    vector<Node*> BFS(){
        return vector<Node*>();
    }

    vector<vector<Node*>>& DFS_ALL(){
        vector<vector<Node*>> ret;
        vector<Node*> curSeq, nextTry; 
        nextTry.emplace_back(root);
        while (!nextTry.empty()) {
            Node* curNode = nextTry.back();
            nextTry.pop_back();
            curSeq.emplace_back(cur_node);
            if (curNode->links.size() > 0) {
                nextTry.insert(nextTry.end(), curNode->links.rbegin(), curNode->links.rend());
            } else { //leaf node, output and revert 1 step
                ret.push_back(curSeq); //need to make sure here uses copy construction
                curSeq.pop_back();
            }
        }
        return ret;
    }
};


template<typename D>
struct GraphNode
{
    /* data */
    D data;
    vector<GraphNode*> links;
public:
    GraphNode(D&& d){
        data = move(d);
    }
    ~GraphNode();

    void AddLink(const L& new_link){
        links.emplace_back(new_link);
    }
};

