#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

void print(std::list<std::unordered_map<int, char>>& LRU){
    for (auto um : LRU)
        {
            for (auto pair : um)
            std::cout<<pair.first<<" "<<pair.second<<std::endl;
        }
    std::cout<<std::endl;
}

void put(int key, char value, std::list<std::unordered_map<int, char>>& LRU, int max)
{   
    std::unordered_map<int, char> um;
    um[key] = value;
    LRU.push_front(um);
    if(LRU.size() > max)
        LRU.pop_back();
}

char get(int key, std::list<std::unordered_map<int, char>>& LRU)
{   
    for (auto it = LRU.begin(); it != LRU.end(); it++){
        if (it->count(key))
            {
                LRU.splice(LRU.begin(), LRU, it);
                return it->at(key);
            }
    }
    return -1;
}

int main(){
    int max {3};
    std::list<std::unordered_map<int, char>> LRU;
    put(1, 'A', LRU, max);
    put(2, 'B', LRU, max);
    put(3, 'C', LRU, max); 
    print(LRU);

    std::cout<<get(2, LRU)<<std::endl;
    print(LRU);

    std::cout<<get(4, LRU)<<std::endl;
    print(LRU);
    
    put(4, 'D', LRU, max);
    print(LRU);

    put(3, 'E', LRU, max);
    print(LRU);

    std::cout<<get(4, LRU)<<std::endl;
    print(LRU);

    put(1, 'A', LRU, max);
    print(LRU);

    return 0;
}